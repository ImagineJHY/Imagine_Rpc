#ifndef IMAGINE_RPC_RPCZOOKEEPER_H
#define IMAGINE_RPC_RPCZOOKEEPER_H

#include "Imagine_Muduo/EventLoop.h"
#include "Imagine_ZooKeeper/ZooKeeper.h"
#include "Imagine_Rpc/RpcWatcher.h"
#include "Imagine_Rpc/common_definition.h"
#include "Imagine_Rpc/Rpc.h"

#include <unordered_map>
#include <string>
#include <list>

namespace Imagine_Rpc
{

class RpcZooKeeper : public ZooKeeper
{
 public:
    class RpcZKHeart
    {
     public:
        RpcZKHeart(const std::string &cluster_name, const std::string &stat, long long timerfd, long long time = Imagine_Tool::TimeUtil::GetNow())
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

        std::string GetStat()
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
        std::string znode_stat_;      // 用于记录znode标识
    };

 public:
    RpcZooKeeper();
    
    RpcZooKeeper(std::string profile_name);

    RpcZooKeeper(const std::string &ip, const std::string &port, Imagine_Muduo::EventCallback read_callback, Imagine_Muduo::EventCallback write_callback, Imagine_Muduo::EventCommunicateCallback communicate_callback, double time_out = 120.0, int max_request_num = 10000);

    RpcZooKeeper(const std::string &ip, const std::string &port, double time_out = 120.0, int max_request_num = 10000);

    ~RpcZooKeeper() {}

    void Init(std::string profile_path);

    void SetDefaultCallback();

    void SetDefaultReadCallback();

    void SetDefaultWriteCallback();

    void SetDefaultCommunicateCallback();

    void SetDefaultTimerCallback();

    RpcZooKeeperTimerCallback GetTimerCallback();

    // 注册服务
    bool Register(const std::string &method, const std::string &ip, const std::string &port, int sockfd);

    // 下线服务(会设置watcher_stat为offline并进行notify),并且也会删除heart_map中的相应节点
    bool DeRegister(const std::string &method, const std::string &ip, const std::string &port, int sockfd);

    std::string SearchMethod(const std::string &method, std::shared_ptr<RpcWatcher> new_watcher = nullptr);

    bool DeleteHeartNode(int sockfd);

    long long SetTimer(double interval, double delay, RpcTimerCallback callback);

    bool RemoveTimer(long long timerfd);

    bool GetHeartNodeInfo(int sockfd, std::string &cluster_name, long long &last_request_time, std::string &stat);

    long long GetHeartNodeLastRequestTime(int sockfd);

 private:
    // const std::string ip_;
    // const std::string port_;

    pthread_mutex_t heart_map_lock_;
    std::unordered_map<int, RpcZooKeeper::RpcZKHeart *> heart_map_;
    RpcZooKeeperTimerCallback timer_callback_;

    const double time_out_ = 120.0;
};

} // namespace Imagine_Rpc

#endif