#ifndef IMAGINE_RPC_RPCUTIL_H
#define IMAGINE_RPC_RPCUTIL_H

#include "common_typename.h"

#include <string>
#include <vector>
#include <functional>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

namespace Imagine_Rpc
{

class Context;

namespace Internal
{

class InternalMessage;

} // namespace Internal

class RpcUtil
{
 public:
   enum class ConnectionStatus
   {
      Ok = 0,
      ReadAgain = 1,
      Close = 2
   };

 public:
    static const double default_delay_;

 public:
    static int StringToInt(const std::string &input);
    static std::string IntToString(size_t input);
    static double StringToDouble(const std::string &input);

    // 内部使用的通信函数
    static struct sockaddr_in PackIpPort(const std::string &ip, const std::string &port); // 打包IP端口号到struct sockaddr_in

    // Server、Client调用一次会话通信接口
    static std::string Communicate(const std::string& send_content, const std::string& ip, const std::string& port, bool wait_recv = true);
    static std::string Communicate(const std::string &send_content, struct sockaddr_in addr, bool wait_recv = true);

    // Server、Client调用长连接通信接口
    static std::string Communicate(const std::string &send_content, int *sockfd, ConnectionStatus& conn_status, bool wait_recv = true);
    static bool Connect(const std::string &ip, const std::string &port, int *sockfd); // sockfd_为nullptr表示结束直接关闭socket

    // IP/Port转换函数
    static std::string ConvertIpFromNetToString(const unsigned int net_ip);
    static std::string ConvertPortFromNetToString(const unsigned short int net_port);
    static unsigned int ConvertIpFromStringToNet(const std::string &string_ip);
    static unsigned short int ConvertPortFromStringToNet(const std::string &string_port);

    // 设置端口复用
    static void SetSocketOpt(int sockfd);

    static bool Connect(const Context* context, int* sockfd);

    static std::string Readfd(const int* sockfd, ConnectionStatus& conn_status);

    static std::string GenerateRegisterName(const std::string& service_name, const std::string& method_name);

    static void SendMessage(const Context* request_context, const RpcMessage* request_msg, Context* response_context, RpcMessage* response_msg, int sockfd);

    static void SendMessage(const Context* request_context, const RpcMessage* request_msg, Context* response_context, RpcMessage* response_msg);

    static void SerializeMessage(const Context* context, const RpcMessage* msg, std::string& content);

    static bool DeserializeMessage(const char* buf, size_t buf_size, Context* context, RpcMessage* msg);

    static bool DeserializeMessage(const std::string& content, Context* context, RpcMessage* msg);

    static void GenerateRegisterMessage(Context* context, Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& zookeeper_ip, const std::string& zookeeper_port, const std::string& server_ip, const std::string& server_port);
    
    // 注册发起通信的IpPort不是服务器监听端口
    static void GenerateRegisterContext(Context* context, const Internal::InternalMessage* const request_msg, const std::string& zookeeper_ip, const std::string& zookeeper_port);

    static void GenerateRegisterContent(Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& server_ip, const std::string& server_port);
   
    static void GenerateDeregisterMessage(Context* context, Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& server_ip, const std::string& server_port);

    static void GenerateDeregisterContext(Context* context, const Internal::InternalMessage* const request_msg, const std::string& service_name, const std::string& method_name);

    static void GenerateDeregisterContent(Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& server_ip, const std::string& server_port);

    static void GenerateCallServerContext(Context* context, const RpcMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& server_ip, const std::string& server_port);

    static void GenerateCallZooKeeperMessage(Context* context, Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& zookeeper_ip, const std::string& zookeeper_port);

    static void GenerateCallZooKeeperContext(Context* context, Internal::InternalMessage* request_msg, const std::string& zookeeper_ip, const std::string& zookeeper_port);

    static void GenerateCallZooKeeperContent(Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name);

    static void GenerateHeartBeatPacketMessage(Context* context, Internal::InternalMessage* request_msg);

    static void GenerateHeartBeatPacketContext(Context* context, const Internal::InternalMessage* request_msg);

    static void GenerateHeartBeatPacketContent(Internal::InternalMessage* request_msg);
};

} // namespace Imagine_Rpc

#endif