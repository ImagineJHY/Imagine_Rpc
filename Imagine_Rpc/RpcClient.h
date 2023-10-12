#ifndef IMAGINE_RPC_RPCCLIENT_H
#define IMAGINE_RPC_RPCCLIENT_H

#include<string>
#include<functional>
#include<thread>
#include<vector>
#include"Rpc.h"

using namespace Imagine_Muduo;

namespace Imagine_Rpc{

class RpcClient{
    //

// public:
//     using RpcCallback=std::function<std::vector<std::string>(const std::vector<std::string>&)>;

public:
    
    RpcClient();

    ~RpcClient(){};

    //完成通信后关闭连接
    static std::vector<std::string> Caller(const std::string& method, const std::vector<std::string>& parameters, const std::string& ip_, const std::string& port_);//在Zookeeper服务器查找函数IP
    static std::vector<std::string> Call(const std::string& method, const std::vector<std::string>& parameters, const std::string& ip_, const std::string& port_);//用户访问RpcServer

    //从RpcZooKeeper获取一个服务器地址但不进行自动调用
    static bool CallerOne(const std::string& method, const std::string& keeper_ip, const std::string& keeper_port, std::string& server_ip, std::string& server_port);

    //通过已connet的socket进行保持连接的通信
    static std::vector<std::string> Call(const std::string& method, const std::vector<std::string>& parameters, int* sockfd);
    //用长连接的形式连接服务器
    static bool ConnectServer(const std::string& ip_, const std::string& port_, int* sockfd);

    static std::string GenerateDefaultRpcKeeperContent(const std::string& method);//生成与RpcKeeper通信的默认content

    static std::string GenerateDefaultRpcServerContent(const std::string& method, const std::vector<std::string>& parameters);//生成与RpcServer通信的默认content

    static RpcCommunicateCallback DefaultCommunicateCallback();

    //EventLoop* loop_;
};

}



#endif