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

/*
用户提供函数名,函数参数,函数IP+端口号进行通信
特别的,若没有参数,参数列表中放入"\r\n"
*/
// std::vector<std::string> RpcClient::CallServer(const std::string &method, const std::vector<std::string> &parameters, const std::string &ip, const std::string &port)
// {
//     struct sockaddr_in addr = RpcUtil::PackIpPort(ip, port);

//     std::string content = GenerateDefaultRpcServerContent(method, parameters);
//     std::string head = RpcUtil::GenerateDefaultHead(content);

//     std::vector<std::string> recv_content = RpcUtil::Deserialize(RpcUtil::Communicate(head + content, addr, true));
//     // for(int i=0;i<recv_.size();i++)printf("%s\n",&recv_[i][0]);
//     RpcUtil::Unpack(recv_content);

//     if (recv_content.size()) {
//         return recv_content;
//     } else {
//         std::vector<std::string> no_content;
//         no_content.push_back("");
//         return no_content;
//     }
// }

// bool RpcClient::CallZooKeeper(const std::string &method, const std::string &keeper_ip, const std::string &keeper_port, std::string &server_ip, std::string &server_port)
// {
//     struct sockaddr_in addr = RpcUtil::PackIpPort(keeper_ip, keeper_port);
//     std::string content = RpcClient::GenerateDefaultRpcKeeperContent(method);
//     std::string head = RpcUtil::GenerateDefaultHead(content);

//     std::string server_addr = RpcUtil::Communicate(head + content, addr, true); // 得到ip和端口号
//     std::vector<std::string> recv_addr = RpcUtil::Deserialize(server_addr);
//     if (recv_addr[1] == "Failure") {
//         LOG_INFO("没有找到函数!");
//         throw std::exception();
//     }
//     server_ip = recv_addr[1];
//     server_port = recv_addr[2];

//     return true;
// }

RpcMessage* RpcClient::CallServer(const std::string& service_name, const std::string& method_name, const RpcMessage* request_msg, int *sockfd)
{
    // std::string content;
    // Context* context;
    // RpcUtil::ConnectionStatus conn_status;
    // RpcUtil::GenerateCallServerContext(context, request_msg, service_name, method_name);
    // context->AppendToString(&content);
    // request_msg->AppendToString(&content);
    // RpcUtil::Communicate(content, sockfd, conn_status, true);

    return nullptr;
}

bool RpcClient::ConnectServer(const std::string &ip, const std::string &port, int *sockfd)
{
    return RpcUtil::Connect(ip, port, sockfd);
}

} // namespace Imagine_Rpc