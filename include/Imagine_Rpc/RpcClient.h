#ifndef IMAGINE_RPC_RPCCLIENT_H
#define IMAGINE_RPC_RPCCLIENT_H

#include "common_typename.h"

#include <string>
#include <thread>
#include <vector>
#include <functional>

namespace Imagine_Rpc
{

class RpcClient
{
 public:
    RpcClient();

    RpcClient(const std::string& profile_name);

    RpcClient(const YAML::Node& config);

    ~RpcClient(){};

    void Init(const std::string& profile_name);

    void Init(const YAML::Node& config);

    // 用长连接的形式连接服务器, 暂时用Stub, 弃用
    static bool ConnectServer(const std::string &ip, const std::string &port, int *sockfd);

 private:
    bool singleton_log_mode_;

    Logger* logger_;
};

} // namespace Imagine_Rpc

#endif