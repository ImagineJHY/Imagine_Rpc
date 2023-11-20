#ifndef IMAGINE_RPC_RPCCLIENT_H
#define IMAGINE_RPC_RPCCLIENT_H

#include "Imagine_Rpc/RpcUtil.h"

#include <string>
#include <functional>
#include <thread>
#include <vector>

using namespace Imagine_Muduo;

namespace Imagine_Rpc
{

class RpcClient
{
 public:
    RpcClient();

    RpcClient(std::string profile_name);

    RpcClient(YAML::Node config);

    ~RpcClient(){};

    void Init(std::string profile_name);

    void Init(YAML::Node config);

    // 完成通信后关闭连接
    static std::vector<std::string> CallServer(const std::string &method, const std::vector<std::string> &parameters, const std::string &ip, const std::string &port);   // 用户访问RpcServer

    // 从RpcZooKeeper获取一个服务器地址但不进行自动调用
    static bool CallZooKeeper(const std::string &method, const std::string &keeper_ip, const std::string &keeper_port, std::string &server_ip, std::string &server_port);

    // 通过已connet的socket进行保持连接的通信
    static RpcMessage* CallServer(const std::string& service_name, const std::string& method_name, const RpcMessage* request_msg, int *sockfd);

    // 用长连接的形式连接服务器
    static bool ConnectServer(const std::string &ip, const std::string &port, int *sockfd);

 private:
    std::string ip_;
    std::string port_;
    std::string rpc_zookeeper_ip_;
    std::string rpc_zookeeper_port_;
    std::string log_name_;
    std::string log_path_;
    size_t max_log_file_size_;
    bool async_log_;
    bool singleton_log_mode_;
    std::string log_title_;
    bool log_with_timestamp_;

    Imagine_Tool::Logger* logger_;
};

} // namespace Imagine_Rpc

#endif