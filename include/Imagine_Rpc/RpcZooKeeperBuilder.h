#ifndef IMAGINE_RPC_RPCZOOKEEPERBUILDER_H
#define IMAGINE_RPC_RPCZOOKEEPERBUILDER_H

#include "Imagine_ZooKeeper/ZooKeeperServer.h"
#include "RpcWatcher.h"
#include "Builder.h"
#include "Imagine_Rpc/RpcUtil.h"
#include "RpcZooKeeperConnection.h"
#include "InternalService.h"

namespace Imagine_Rpc
{

class RpcZooKeeperBuilder : public Builder, public Imagine_ZooKeeper::ZooKeeperServer
{
 public:
   class RpcZKHeart
   {
    public:
      RpcZKHeart(const std::string &cluster_name, const std::pair<std::string, std::string> &stat, long long timerfd, long long time = NOW_MS)
         : timerfd_(timerfd), last_request_time_(time), cluster_name_(cluster_name), znode_stat_(stat) {}

      bool ReSetLastRequestTime()
      {
         last_request_time_ = Imagine_Tool::TimeUtil::GetNow();
         return true;
      }

      long long GetLastRequestTime()
      {
         return last_request_time_;
      }

      std::string GetClusterName()
      {
         return cluster_name_;
      }

      std::pair<std::string, std::string> GetStat()
      {
         return znode_stat_;
      }

      long long GetTimerfd()
      {
         return timerfd_;
      }

    private:
      long long timerfd_;
      long long last_request_time_; // 记录最后一次心跳时间(绝对时间)
      std::string cluster_name_;    // 记录所属的cluster
      std::pair<std::string, std::string> znode_stat_;      // 用于记录znode标识
   };

 public:
   RpcZooKeeperBuilder();

   RpcZooKeeperBuilder(const std::string& profile_name);

   RpcZooKeeperBuilder(const YAML::Node& config);

   ~RpcZooKeeperBuilder();
   
   void Init();

   void SetDefaultTimerCallback();

   RpcZooKeeperTimerCallback GetTimerCallback();

   // 注册服务
   bool Register(const std::string &method, const std::string &ip, const std::string &port, int sockfd);

   // 下线服务(会设置watcher_stat为offline并进行notify),并且也会删除heart_map中的相应节点
   bool DeRegister(const std::string &method, const std::string &ip, const std::string &port, int sockfd);

   bool HeartBeatProcessor(int sockfd);

   std::pair<std::string, std::string> SearchMethod(const std::string &method, std::shared_ptr<RpcWatcher> new_watcher = nullptr);

   bool DeleteHeartNode(int sockfd);

   bool GetHeartNodeInfo(int sockfd, std::string &cluster_name, long long &last_request_time, std::pair<std::string, std::string> &stat);

   long long GetHeartNodeLastRequestTime(int sockfd);

 private:
   Service* internal_service_;

 private:
   pthread_mutex_t heart_map_lock_;
   std::unordered_map<int, RpcZooKeeperBuilder::RpcZKHeart *> heart_map_;
   RpcZooKeeperTimerCallback timer_callback_;

   const double time_out_ = SERVER_HEARTBEAT_EXPIRE_TIME;
};

} // namespace Imagine_Rpc

#endif