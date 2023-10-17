#ifndef IMAGINE_RPC_COMMON_DEFINITION_H
#define IMAGINE_RPC_COMMON_DEFINITION_H

#include <functional>
#include <vector>

namespace Imagine_Rpc
{

using RpcCallback = std::function<std::vector<std::string>(const std::vector<std::string> &)>; // 用户回调函数
using RpcZooKeeperTimerCallback = std::function<void(int, double)>;                            // ZooKeeper心跳检测函数
using RpcServerTimerCallback = std::function<void(int, double)>;                               // Server心跳检测函数
using RpcCommunicateCallback = std::function<bool(const char *, int)>;                         // Communicate函数中用于粘包判断的回调函数
using RpcTimerCallback = std::function<void()>;
using RpcTimeOutCallback = std::function<void()>;

} // namespace Imagine_Rpc

#endif