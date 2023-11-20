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
    service_name_ = config["service_name"].as<std::string>();
    method_name_ = config["method_name"].as<std::string>();
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

Status Stub::Call(RpcMessage* request_msg, RpcMessage* response_msg)
{
    Context request_context;
    Context response_context;
    Internal::InternalMessage request_zk_msg;
    Internal::InternalMessage response_zk_msg;
    printf("zk ip is %s, zk port is %s\n", zookeeper_ip_.c_str(), zookeeper_port_.c_str());
    RpcUtil::GenerateCallZooKeeperMessage(&request_context, &request_zk_msg, service_name_, method_name_, zookeeper_ip_, zookeeper_port_);
    RpcUtil::SendMessage(&request_context, &request_zk_msg, &response_context, &response_zk_msg);
    printf("server ip is %s, server port is %s\n", response_zk_msg.server_ip_().c_str(), response_zk_msg.server_port_().c_str());
    RpcUtil::GenerateCallServerContext(&request_context, request_msg, service_name_, method_name_, response_zk_msg.server_ip_(), response_zk_msg.server_port_());
    RpcUtil::SendMessage(&request_context, request_msg, &response_context, response_msg);
    
    return Status::OK;
}

} // namespace Imagine_Rpc