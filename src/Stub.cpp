#include "Imagine_Rpc/Stub.h"

#include "Imagine_Rpc/RpcUtil.h"
#include "Imagine_Log/SingletonLogger.h"
#include "Imagine_Log/NonSingletonLogger.h"
#include "Imagine_Rpc/Context.pb.h"
#include "Imagine_Rpc/InternalMessage.pb.h"

namespace Imagine_Rpc
{

Stub::Stub()
{
}

Stub::Stub(std::string profile_name)
{
    Init(profile_name);
}

Stub::Stub(YAML::Node config)
{
    Init(config);
}

Stub::Stub(const Stub& stub)
{
    zookeeper_ip_ = stub.zookeeper_ip_;
    zookeeper_port_ = stub.zookeeper_port_;
    service_name_ = stub.service_name_;
    method_name_ = stub.method_name_;
    log_name_ = stub.log_name_;
    log_path_ = stub.log_path_;
    max_log_file_size_ = stub.max_log_file_size_;
    async_log_ = stub.async_log_;
    singleton_log_mode_ = stub.singleton_log_mode_;
    log_title_ = stub.log_title_;
    log_with_timestamp_ = stub.log_with_timestamp_;

    if (singleton_log_mode_) {
        logger_ = Imagine_Tool::SingletonLogger::GetInstance();
    } else {
        // 暂无non-singleton-Log的非yaml类型Init方法
        throw std::exception();
        logger_ = new Imagine_Tool::NonSingletonLogger();
        Imagine_Tool::Logger::SetInstance(logger_);
    }

    // logger_->Init(config);
}

Stub::~Stub()
{
}

void Stub::Init(std::string profile_name)
{
    if (profile_name == "") {
        throw std::exception();
    }

    YAML::Node config = YAML::LoadFile(profile_name);
    Init(config);
}

void Stub::Init(YAML::Node config)
{
    zookeeper_ip_ = config["zookeeper_ip"].as<std::string>();
    zookeeper_port_ = config["zookeeper_port"].as<std::string>();
    // service_name_ = config["service_name"].as<std::string>();
    // method_name_ = config["method_name"].as<std::string>();
    log_name_ = config["log_name"].as<std::string>();
    log_path_ = config["log_path"].as<std::string>();
    max_log_file_size_ = config["max_log_file_size"].as<size_t>();
    async_log_ = config["async_log"].as<bool>();
    singleton_log_mode_ = config["singleton_log_mode"].as<bool>();
    log_title_ = config["log_title"].as<std::string>();
    log_with_timestamp_ = config["log_with_timestamp"].as<bool>();

    if (singleton_log_mode_) {
        logger_ = Imagine_Tool::SingletonLogger::GetInstance();
    } else {
        logger_ = new Imagine_Tool::NonSingletonLogger();
        Imagine_Tool::Logger::SetInstance(logger_);
    }

    logger_->Init(config);
}

Stub* Stub::SearchNewServer()
{
    Context request_context;
    Context response_context;
    Internal::InternalMessage request_msg;
    Internal::InternalMessage response_msg;
    RpcUtil::GenerateCallZooKeeperMessage(&request_context, &request_msg, service_name_, method_name_, zookeeper_ip_, zookeeper_port_);
    RpcUtil::SendMessage(&request_context, &request_msg, &response_context, &response_msg);
    server_ip_ = response_msg.server_ip_();
    server_port_ = response_msg.server_port_();

    return this;
}

Stub* Stub::ConnectServer()
{
    if (!server_ip_.size() || !server_port_.size()) {
        SearchNewServer();
    }
    printf("server ip is %s, server port is %s\n", server_ip_.c_str(), server_port_.c_str());
    RpcUtil::Connect(server_ip_, server_port_, &sockfd_);

    return this;
}

Stub* Stub::CloseConnection()
{
    close(sockfd_);

    return this;
}

Status Stub::Call(RpcMessage* request_msg, RpcMessage* response_msg)
{
    if (!server_ip_.size() || !server_port_.size()) {
        SearchNewServer();
    }
    Context request_context;
    Context response_context;
    printf("server ip is %s, server port is %s\n", server_ip_.c_str(), server_port_.c_str());
    RpcUtil::GenerateCallServerContext(&request_context, request_msg, service_name_, method_name_, server_ip_, server_port_);
    RpcUtil::SendMessage(&request_context, request_msg, &response_context, response_msg);
    
    return Status::OK;
}

Status Stub::CallConnectServer(RpcMessage* request_msg, RpcMessage* response_msg)
{
    if (!server_ip_.size() || !server_port_.size()) {
        throw std::exception();
    }

    Context request_context;
    Context response_context;
    printf("server ip is %s, server port is %s\n", server_ip_.c_str(), server_port_.c_str());
    RpcUtil::GenerateCallServerContext(&request_context, request_msg, service_name_, method_name_, server_ip_, server_port_);
    RpcUtil::SendMessage(&request_context, request_msg, &response_context, response_msg, sockfd_);

    return Status::OK;
}

Stub* Stub::SetServerIp(const std::string& server_ip)
{
    server_ip_ = server_ip;

    return this;
}

Stub* Stub::SetServerPort(const std::string& server_port)
{
    server_port_ = server_port;

    return this;
}

Stub* Stub::SetServiceName(const std::string& service_name)
{
    service_name_ = service_name;

    return this;
}

Stub* Stub::SetMethodName(const std::string& method_name)
{
    method_name_ = method_name;

    return this;
}

Stub* Stub::SetSockfd(int sockfd)
{
    sockfd_ = sockfd;

    return this;
}

int Stub::GetSockfd() const
{
    return sockfd_;
}

} // namespace Imagine_Rpc