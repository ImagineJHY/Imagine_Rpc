#ifndef IMAGINE_RPC_RPCSERVERBUILDER_H
#define IMAGINE_RPC_RPCSERVERBUILDER_H

#include "Imagine_Log/Logger.h"
#include "Imagine_Muduo/EventLoop.h"
#include "Imagine_Muduo/TcpServer.h"
#include "Builder.h"
#include "RpcServerConnection.h"

namespace Imagine_Rpc
{

class RpcServerBuilder : public Builder, public Imagine_Muduo::TcpServer
{
 public:
   class RpcSHeart
   {
    public:
      RpcSHeart(long long timerId, long long time = Imagine_Tool::TimeUtil::GetNow())
            : timerId_(timerId), last_request_time_(time) {}

      bool ReSetLastRequestTime()
      {
            last_request_time_ = Imagine_Tool::TimeUtil::GetNow();
            return true;
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

   RpcServerBuilder* const RegisterService(Service* service);

   RpcServerBuilder* const DeregisterService(Service* service);

   void SetDefaultTimerCallback();

   bool UpdatetUser(RpcServerConnection* conn);

   bool DeleteUser(RpcServerConnection* conn);

   bool GetHeartNodeInfo(RpcServerConnection* conn, long long &last_request_time);

   long long GetHeartNodeLastRequestTime(RpcServerConnection* conn);

   void HeartBeatPacketSender(int sockfd);

 private:
   std::string ip_;
   std::string port_;
   std::string zookeeper_ip_;
   std::string zookeeper_port_;
   std::string log_name_;
   std::string log_path_;
   size_t max_log_file_size_;
   bool async_log_;
   bool singleton_log_mode_;
   std::string log_title_;
   bool log_with_timestamp_;
   Imagine_Tool::Logger* logger_;

 private:
   pthread_mutex_t heart_map_lock_;
   std::unordered_map<RpcServerConnection*, RpcSHeart *> heart_map_;
   RpcServerTimerCallback timer_callback_;
   const double time_out_ = 1.0;
};

} // namespace Imagine_Rpc

#endif