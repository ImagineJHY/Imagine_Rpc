#include "Imagine_Rpc/RpcClient.h"

#include "Imagine_Rpc/common_definition.h"
#include "Imagine_Rpc/Context.pb.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/*
用户提供函数名在Zookeeper上查找函数地址
*/

namespace Imagine_Rpc
{

RpcClient::RpcClient()
{
}

RpcClient::RpcClient(std::string profile_name)
{
    Init(profile_name);
}

RpcClient::RpcClient(YAML::Node config)
{
    Init(config);
}

void RpcClient::Init(std::string profile_name)
{
    if (profile_name == "") {
        throw std::exception();
    }

    YAML::Node config = YAML::LoadFile(profile_name);
    Init(config);
}

void RpcClient::Init(YAML::Node config)
{
    ip_ = config["ip"].as<std::string>();
    port_ = config["port"].as<std::string>();
    rpc_zookeeper_ip_ = config["zookeeper_ip"].as<std::string>();
    rpc_zookeeper_port_ = config["zookeeper_port"].as<std::string>();
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

bool RpcClient::ConnectServer(const std::string &ip, const std::string &port, int *sockfd)
{
    return RpcUtil::Connect(ip, port, sockfd);
}

} // namespace Imagine_Rpc