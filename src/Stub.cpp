#include "Imagine_Rpc/Stub.h"

#include "Imagine_Rpc/RpcUtil.h"
#include "Imagine_Rpc/log_macro.h"
#include "Imagine_Rpc/Context.pb.h"
#include "Imagine_Rpc/common_definition.h"
#include "Imagine_Rpc/InternalMessage.pb.h"

namespace Imagine_Rpc
{

Stub::Stub()
{
}

Stub::Stub(const std::string& profile_name)
{
    Init(profile_name);
}

Stub::Stub(const YAML::Node& config)
{
    Init(config);
}

Stub::Stub(const Stub& stub)
{
    zookeeper_ip_ = stub.zookeeper_ip_;
    zookeeper_port_ = stub.zookeeper_port_;
    service_name_ = stub.service_name_;
    method_name_ = stub.method_name_;
    singleton_log_mode_ = stub.singleton_log_mode_;
    logger_ = stub.logger_;
}

Stub::~Stub()
{
}

void Stub::Init(const std::string& profile_name)
{
    if (profile_name == "") {
        throw std::exception();
    }

    YAML::Node config = YAML::LoadFile(profile_name);
    Init(config);
}

void Stub::Init(const YAML::Node& config)
{
    zookeeper_ip_ = config["zookeeper_ip"].as<std::string>();
    zookeeper_port_ = config["zookeeper_port"].as<std::string>();
    // service_name_ = config["service_name"].as<std::string>();
    // method_name_ = config["method_name"].as<std::string>();
    singleton_log_mode_ = config["singleton_log_mode"].as<bool>();

    if (singleton_log_mode_) {
        logger_ = SingletonLogger::GetInstance();
    } else {
        logger_ = new NonSingletonLogger();
        Logger::SetInstance(logger_);
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

const Stub* Stub::CloseConnection() const
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

Status Stub::CallConnectServer(RpcMessage* request_msg, RpcMessage* response_msg) const
{
    if (!server_ip_.size() || !server_port_.size()) {
        throw std::exception();
    }

    Context request_context;
    Context response_context;
    IMAGINE_RPC_LOG("Call Connect Server, service name is %s, server ip is %s, server port is %s\n", service_name_.c_str(), server_ip_.c_str(), server_port_.c_str());
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

std::string Stub::GetServerIp() const
{
    return server_ip_;
}

std::string Stub::GetServerPort() const
{
    return server_port_;
}

int Stub::GetSockfd() const
{
    return sockfd_;
}

} // namespace Imagine_Rpc