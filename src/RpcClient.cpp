#include "Imagine_Rpc/RpcClient.h"

#include "Imagine_Rpc/RpcUtil.h"

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

RpcClient::RpcClient(const std::string& profile_name)
{
    Init(profile_name);
}

RpcClient::RpcClient(const YAML::Node& config)
{
    Init(config);
}

void RpcClient::Init(const std::string& profile_name)
{
    if (profile_name == "") {
        throw std::exception();
    }

    YAML::Node config = YAML::LoadFile(profile_name);
    Init(config);
}

void RpcClient::Init(const YAML::Node& config)
{
    singleton_log_mode_ = config["singleton_log_mode"].as<bool>();

    if (singleton_log_mode_) {
        logger_ = SingletonLogger::GetInstance();
    } else {
        logger_ = new NonSingletonLogger();
        Logger::SetInstance(logger_);
    }

    logger_->Init(config);
}

bool RpcClient::ConnectServer(const std::string &ip, const std::string &port, int *sockfd)
{
    return RpcUtil::Connect(ip, port, sockfd);
}

} // namespace Imagine_Rpc