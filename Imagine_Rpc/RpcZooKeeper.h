#ifndef IMAGINE_RPC_RPCZOOKEEPER_H
#define IMAGINE_RPC_RPCZOOKEEPER_H

#include<Imagine_ZooKeeper/Imagine_ZooKeeper/ZooKeeper.h>
#include<Imagine_Muduo/Imagine_Muduo/EventLoop.h>
// #include<Imagine_Muduo/TimeUtil.h>
#include<unordered_map>
#include<string>
#include<list>

#include"Callbacks.h"
#include"RpcWatcher.h"
#include"Rpc.h"

// #define DEFAULT_KEEPER_IP "192.168.83.129"
// #define DEFAULT_KEEPER_PORT "9999"

using namespace Imagine_Muduo;

namespace Imagine_Rpc{

class RpcZooKeeper : public ZooKeeper{

// public:
//     using RpcZooKeeperTimerCallback=std::function<void(int,double)>;

public:
    class RpcZKHeart{
        public:
            RpcZKHeart(const std::string& cluster_name_, const std::string& stat_, long long timerfd_, long long time_=TimeUtil::GetNow())
                :cluster_name(cluster_name_),znode_stat(stat_),timerfd(timerfd_),last_request_time(time_)
            {
            }

            bool ReSetLastRequestTime(){
                last_request_time=TimeUtil::GetNow();
                return true;
            }

            long long GetLastRequestTime(){
                return last_request_time;
            }

            std::string GetClusterName(){
                return cluster_name;
            }

            std::string GetStat(){
                return znode_stat;
            }

            long long GetTimerfd(){
                return timerfd;
            }

        private:
            long long timerfd;
            long long last_request_time;//记录最后一次心跳时间(绝对时间)
            std::string cluster_name;//记录所属的cluster
            std::string znode_stat;//用于记录znode标识
    };

public:
    RpcZooKeeper(const std::string& ip_, const std::string& port_, EventCallback read_callback_, EventCallback write_callback_, EventCommunicateCallback communicate_callback_, double time_out_=120.0, int max_request_num=10000);

    RpcZooKeeper(const std::string& ip_, const std::string& port_, double time_out_=120.0, int max_request_num=10000);

    ~RpcZooKeeper(){};

    void SetDefaultReadCallback();

    void SetDefaultWriteCallback();

    void SetDefaultCommunicateCallback();

    void SetDefaultTimerCallback();

    RpcZooKeeperTimerCallback GetTimerCallback();

    //注册服务
    bool Register(const std::string& method, const std::string& ip_, const std::string& port_, int sockfd);

    //下线服务(会设置watcher_stat为offline并进行notify),并且也会删除heart_map中的相应节点
    bool DeRegister(const std::string& method, const std::string& ip_, const std::string& port_, int sockfd);

    std::string SearchMethod(const std::string& method, std::shared_ptr<RpcWatcher> new_watcher=nullptr);

    bool DeleteHeartNode(int sockfd);

    long long SetTimer(double interval, double delay, RpcTimerCallback callback);

    bool RemoveTimer(long long timerfd);

    bool GetHeartNodeInfo(int sockfd, std::string& cluster_name, long long& last_request_time, std::string& stat);

    long long GetHeartNodeLastRequestTime(int sockfd);

private:

    const std::string ip;
    const std::string port;

    pthread_mutex_t heart_map_lock;
    std::unordered_map<int,RpcZooKeeper::RpcZKHeart*> heart_map;
    RpcZooKeeperTimerCallback timer_callback;

    const double time_out=120.0;
};




}



#endif