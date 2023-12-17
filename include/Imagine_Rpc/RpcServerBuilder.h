#ifndef IMAGINE_RPC_RPCSERVERBUILDER_H
#define IMAGINE_RPC_RPCSERVERBUILDER_H

#include "Builder.h"
#include "common_typename.h"

#include "Imagine_Muduo/Imagine_Muduo.h"

namespace Imagine_Rpc
{

class RpcServerConnection;

class RpcServerBuilder : public Builder, public Imagine_Muduo::TcpServer
{
 public:
   class RpcSHeart
   {
    public:
      RpcSHeart(long long timerId, long long time = TimeUtil::GetNow()) : timerId_(timerId), last_request_time_(time) 
      {
      }

      RpcSHeart* ReSetLastRequestTime()
      {
            last_request_time_ = TimeUtil::GetNow();

            return this;
      }

      long long GetLastRequestTime()
      {
            return last_request_time_;
      }

      long long GetTimerfd()
      {
            return timerId_;
      }

    private:
      long long timerId_;
      long long last_request_time_; // 记录最后一次心跳时间(绝对时间)
   };

 public:
   RpcServerBuilder();

   RpcServerBuilder(const std::string& profile_name);

   RpcServerBuilder(const YAML::Node& config);

   ~RpcServerBuilder();

   void Init(const std::string& profile_name);

   void Init(const YAML::Node& config);

   RpcServerBuilder* RegisterService(const Service* service);

   RpcServerBuilder* DeregisterService(const Service* service);

   void SetDefaultTimerCallback();

   RpcServerBuilder* UpdatetUser(const RpcServerConnection* conn);

   RpcServerBuilder* DeleteUser(const RpcServerConnection* conn);

   bool GetHeartNodeInfo(const RpcServerConnection* conn, long long &last_request_time);

   long long GetHeartNodeLastRequestTime(const RpcServerConnection* conn);

   // 向ZK发送心跳包的回调函数
   void HeartBeatPacketSender(int sockfd);

 private:
   // 配置文件参数
   std::string ip_;                                                           // IP
   std::string port_;                                                         // Port
   std::string zookeeper_ip_;                                                 // ZK的IP
   std::string zookeeper_port_;                                               // ZK的Port
   bool singleton_log_mode_;                                                  // 日志模式(目前仅支持单例)

   Logger* logger_;                                                           // 日志对象

 private:
   pthread_mutex_t heart_map_lock_;                                           // heart_map_的锁
   std::unordered_map<const RpcServerConnection*, RpcSHeart *> heart_map_;    // 所有建立连接的客户端集合
   RpcServerTimerCallback timer_callback_;                                    // 对与服务端建立连接的客户端进行定期心跳检测的回调函数
   const double time_out_;                                                    // 连接过期事件(暂不支持调整)
};

} // namespace Imagine_Rpc

#endif