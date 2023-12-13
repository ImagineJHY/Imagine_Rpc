#ifndef IMAGINE_RPC_COMMON_TYPENAME_H
#define IMAGINE_RPC_COMMON_TYPENAME_H

#include "Imagine_Time/Imagine_Time.h"
#include "Imagine_Log/Imagine_Log.h"

#include <google/protobuf/message.h>

#include <functional>
#include <vector>

namespace Imagine_Rpc
{

class RpcServerConnection;

using RpcCallback                   =   std::function<std::vector<std::string>(const std::vector<std::string> &)>;      // 用户回调函数
using RpcZooKeeperTimerCallback     =   std::function<void(int, double)>;                                               // ZooKeeper心跳检测函数
using RpcServerTimerCallback        =   std::function<void(const RpcServerConnection*, double)>;                        // Server心跳检测函数
using RpcCommunicateCallback        =   std::function<bool(const char *, int)>;                                         // Communicate函数中用于粘包判断的回调函数
using RpcTimerCallback              =   std::function<void()>;
using RpcTimeOutCallback            =   std::function<void()>;

using RpcMessage                    =   ::google::protobuf::Message;

using TimerCallback                 =   ::Imagine_Tool::Imagine_Time::TimerCallback;
using TimeUtil                      =   ::Imagine_Tool::Imagine_Time::TimeUtil;

using Logger                        =   ::Imagine_Tool::Imagine_Log::Logger;
using SingletonLogger               =   ::Imagine_Tool::Imagine_Log::SingletonLogger;
using NonSingletonLogger            =   ::Imagine_Tool::Imagine_Log::NonSingletonLogger;

} // namespace Imagine_Rpc


#endif