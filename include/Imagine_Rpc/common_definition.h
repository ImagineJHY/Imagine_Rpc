#ifndef IMAGINE_RPC_COMMON_DEFINITION_H
#define IMAGINE_RPC_COMMON_DEFINITION_H

#include <google/protobuf/message.h>

#include <functional>
#include <vector>

namespace Imagine_Rpc
{

class RpcServerConnection;

#define INTERNAL_ZOOKEEPER_SERVICE_NAME "Internal_Service"
#define INTERNAL_ZOOKEEPER_METHOD_NAME "Internal_Processor"
#define INTERNAL_REGISTER_SERVICE_NAME INTERNAL_ZOOKEEPER_SERVICE_NAME
#define INTERNAL_REGISTER_METHOD_NAME INTERNAL_ZOOKEEPER_METHOD_NAME
#define INTERNAL_DEREGISTER_SERVICE_NAME INTERNAL_ZOOKEEPER_SERVICE_NAME
#define INTERNAL_DEREGISTER_METHOD_NAME INTERNAL_ZOOKEEPER_METHOD_NAME

#define HEARTBEAT_INTERVAL_TIME 1
#define CLIENT_HEARTBEAT_EXPIRE_TIME 120.0
#define SERVER_HEARTBEAT_EXPIRE_TIME 120.0


using RpcCallback = std::function<std::vector<std::string>(const std::vector<std::string> &)>; // 用户回调函数
using RpcZooKeeperTimerCallback = std::function<void(int, double)>;                            // ZooKeeper心跳检测函数
using RpcServerTimerCallback = std::function<void(RpcServerConnection*, double)>;                               // Server心跳检测函数
using RpcCommunicateCallback = std::function<bool(const char *, int)>;                         // Communicate函数中用于粘包判断的回调函数
using RpcTimerCallback = std::function<void()>;
using RpcTimeOutCallback = std::function<void()>;

enum class Status
{
    OK,
    ERROR
};

class Context;
using RpcMessage = ::google::protobuf::Message;

} // namespace Imagine_Rpc

#endif