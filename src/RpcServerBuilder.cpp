#include "Imagine_Rpc/RpcServerBuilder.h"

#include "Imagine_Rpc/RpcUtil.h"
#include "Imagine_Rpc/Service.h"
#include "Imagine_Rpc/log_macro.h"
#include "Imagine_Rpc/Context.pb.h"
#include "Imagine_Rpc/common_macro.h"
#include "Imagine_Rpc/ServiceDescriptor.h"
#include "Imagine_Rpc/InternalMessage.pb.h"
#include "Imagine_Rpc/RpcServerConnection.h"

namespace Imagine_Rpc
{

RpcServerBuilder::RpcServerBuilder() : time_out_(CLIENT_HEARTBEAT_EXPIRE_TIME)
{
}

RpcServerBuilder::RpcServerBuilder(const std::string& profile_name) : Builder(), Imagine_Muduo::TcpServer(profile_name, new RpcServerConnection()), time_out_(CLIENT_HEARTBEAT_EXPIRE_TIME)
{
    Init(profile_name);
}

RpcServerBuilder::RpcServerBuilder(const YAML::Node& config) : Builder(), Imagine_Muduo::TcpServer(config, new RpcServerConnection()), time_out_(CLIENT_HEARTBEAT_EXPIRE_TIME)
{
    Init(config);
}

RpcServerBuilder::~RpcServerBuilder()
{
}

void RpcServerBuilder::Init(const std::string& profile_name)
{
    if (profile_name == "") {
        throw std::exception();
    }

    if (pthread_mutex_init(&heart_map_lock_, nullptr) != 0) {
        throw std::exception();
    }

    YAML::Node config = YAML::LoadFile(profile_name);
    Init(config);
}

void RpcServerBuilder::Init(const YAML::Node& config)
{
    ip_ = config["ip"].as<std::string>();
    port_ = config["port"].as<std::string>();
    zookeeper_ip_ = config["zookeeper_ip"].as<std::string>();
    zookeeper_port_ = config["zookeeper_port"].as<std::string>();
    singleton_log_mode_ = config["singleton_log_mode"].as<bool>();

    if (singleton_log_mode_) {
        logger_ = SingletonLogger::GetInstance();
    } else {
        logger_ = new NonSingletonLogger();
        Logger::SetInstance(logger_);
    }
    SetDefaultTimerCallback();

    logger_->Init(config);
}

RpcServerBuilder* RpcServerBuilder::RegisterService(const Service* service)
{
    Builder::RegisterService(service);
    if (zookeeper_ip_.size() && zookeeper_port_.size()) {
        // 发送逻辑
        std::string service_name = service->GetServiceDescriptor()->GetServiceName();
        for(auto it = service->GetServiceDescriptor()->GetMethodHandlers().begin(); it != service->GetServiceDescriptor()->GetMethodHandlers().end(); it++) {
            Context request_context;
            Internal::InternalMessage request_msg;
            Context response_context;
            Internal::InternalMessage response_msg;
            int sockfd;
            RpcUtil::GenerateRegisterMessage(&request_context, &request_msg, service_name, it->first, zookeeper_ip_, zookeeper_port_, ip_, port_);
            RpcUtil::Connect(&request_context, &sockfd);
            RpcUtil::SendMessage(&request_context, &request_msg, &response_context, &response_msg, sockfd);
            SetTimer(std::bind(&RpcServerBuilder::HeartBeatPacketSender, this, sockfd), HEARTBEAT_INTERVAL_TIME);
        }
    }

    return this;
}

RpcServerBuilder* RpcServerBuilder::DeregisterService(const Service* service)
{
    Builder::DeregisterService(service->GetServiceDescriptor()->GetServiceName());
    if (zookeeper_ip_.size() && zookeeper_port_.size()) {
        // 发送逻辑
        std::string service_name = service->GetServiceDescriptor()->GetServiceName();
        for(auto it = service->GetServiceDescriptor()->GetMethodHandlers().begin(); it != service->GetServiceDescriptor()->GetMethodHandlers().end(); it++) {
            Context context;
            Internal::InternalMessage content_msg;
            std::string send_content;
            RpcUtil::GenerateDeregisterMessage(&context, &content_msg, service_name, it->first, ip_, port_);
            context.AppendToString(&send_content);
            content_msg.AppendToString(&send_content);
            std::string recv_content = RpcUtil::Communicate(send_content, zookeeper_ip_, zookeeper_port_);
        }
    }

    return this;
}

void RpcServerBuilder::SetDefaultTimerCallback()
{
    timer_callback_ = [this](const RpcServerConnection* conn, double time_out)
    {
        IMAGINE_RPC_LOG("this is RpcServer TimerCallback!");

        long long last_request_time;
        if (!GetHeartNodeInfo(conn, last_request_time)) {
            return;
        }

        if (TimeUtil::GetNow() > TimeUtil::MicroSecondsAddSeconds(last_request_time, time_out)) {
            // 已过期
            IMAGINE_RPC_LOG("RpcServer Timer Set offline!");
            CloseConnection(conn->GetIp(), conn->GetPort());
            this->DeleteUser(conn);
            return;
        } else {
            // 未过期,忽略
        }
    };
}

RpcServerBuilder* RpcServerBuilder::UpdatetUser(const RpcServerConnection* conn)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<const RpcServerConnection*, RpcSHeart *>::iterator it = heart_map_.find(conn);
    if (it == heart_map_.end()) {
        RpcSHeart *new_heart = new RpcSHeart(SetTimer(std::bind(timer_callback_, conn, time_out_), 1.0, 0.0));
        heart_map_.insert(std::make_pair(conn, new_heart));
    } else {
        it->second->ReSetLastRequestTime();
    }
    pthread_mutex_unlock(&heart_map_lock_);

    return this;
}

RpcServerBuilder* RpcServerBuilder::DeleteUser(const RpcServerConnection* conn)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<const RpcServerConnection*, RpcSHeart *>::iterator it = heart_map_.find(conn);
    if (it == heart_map_.end()) {
        return this; // 已删除
        throw std::exception();
    }
    RpcSHeart *heart_node = it->second;
    heart_map_.erase(it);
    RemoveTimer(heart_node->GetTimerfd());
    delete heart_node;
    pthread_mutex_unlock(&heart_map_lock_);

    return this;
}

bool RpcServerBuilder::GetHeartNodeInfo(const RpcServerConnection* conn, long long &last_request_time)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<const RpcServerConnection*, RpcSHeart *>::iterator it = heart_map_.find(conn);
    if (it == heart_map_.end()) {
        // 已删除
        pthread_mutex_unlock(&heart_map_lock_);
        return false;
    }
    last_request_time = it->second->GetLastRequestTime();
    pthread_mutex_unlock(&heart_map_lock_);

    return true;
}

long long RpcServerBuilder::GetHeartNodeLastRequestTime(const RpcServerConnection* conn)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<const RpcServerConnection*, RpcSHeart *>::iterator it = heart_map_.find(conn);
    if (it == heart_map_.end()) {
        // 已删除
        pthread_mutex_unlock(&heart_map_lock_);
        return -1;
    }
    long long last_request_time = it->second->GetLastRequestTime();
    pthread_mutex_unlock(&heart_map_lock_);

    return last_request_time;
}

void RpcServerBuilder::HeartBeatPacketSender(int sockfd)
{
    IMAGINE_RPC_LOG("Send HeartBeat Packet!");
    Context request_context;
    Internal::InternalMessage request_msg;
    Context response_context;
    Internal::InternalMessage response_msg;
    RpcUtil::GenerateHeartBeatPacketMessage(&request_context, &request_msg);
    RpcUtil::SendMessage(&request_context, &request_msg, &response_context, &response_msg, sockfd);
    // 重新连接的逻辑暂无
}

} // namespace Imagine_Rpc