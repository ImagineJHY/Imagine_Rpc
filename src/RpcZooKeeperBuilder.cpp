#include "Imagine_Rpc/RpcZooKeeperBuilder.h"

#include "Imagine_Rpc/log_macro.h"
#include "Imagine_Rpc/RpcWatcher.h"
#include "Imagine_Rpc/common_macro.h"
#include "Imagine_Rpc/InternalService.h"
#include "Imagine_Rpc/RpcZooKeeperConnection.h"

namespace Imagine_Rpc
{

RpcZooKeeperBuilder::RpcZooKeeperBuilder() : time_out_(SERVER_HEARTBEAT_EXPIRE_TIME)
{
}

RpcZooKeeperBuilder::RpcZooKeeperBuilder(const std::string& profile_name) : Builder(), Imagine_ZooKeeper::ZooKeeperServer(profile_name, new RpcZooKeeperConnection()), time_out_(SERVER_HEARTBEAT_EXPIRE_TIME)
{
    Init();
}

RpcZooKeeperBuilder::RpcZooKeeperBuilder(const YAML::Node& config) : Builder(), Imagine_ZooKeeper::ZooKeeperServer(config, new RpcZooKeeperConnection()), time_out_(SERVER_HEARTBEAT_EXPIRE_TIME)
{
    Init();
}
    
RpcZooKeeperBuilder::~RpcZooKeeperBuilder()
{
}

void RpcZooKeeperBuilder::Init()
{
    if (pthread_mutex_init(&heart_map_lock_, nullptr) != 0) {
        throw std::exception();
    }

    internal_service_ = new Internal::InternalService(this);
    RegisterService(internal_service_);
    SetDefaultTimerCallback();
}

void RpcZooKeeperBuilder::SetDefaultTimerCallback()
{
    timer_callback_ = [this](int sockfd, double time_out)
    {
        IMAGINE_RPC_LOG("RpcZooKeeper TimerCallback!");

        std::string cluster_name;
        long long last_request_time;
        std::pair<std::string, std::string> stat;
        if (!GetHeartNodeInfo(sockfd, cluster_name, last_request_time, stat)) {
            IMAGINE_RPC_LOG("Timer Removed already!");
            return;
        }

        if (TimeUtil::GetNow() > TimeUtil::MicroSecondsAddSeconds(last_request_time, time_out)) {
            // 已过期
            IMAGINE_RPC_LOG("RpcZooKeeper Timer Set offline!");
            // this->loop_->Closefd(sockfd);
            DeRegister(cluster_name, stat.first, stat.second, sockfd);
            return;
        } else {
            IMAGINE_RPC_LOG("Timer keep going!");
            // 未过期,忽略
        }
    };
}

RpcZooKeeperTimerCallback RpcZooKeeperBuilder::GetTimerCallback() const
{
    return timer_callback_;
}

bool RpcZooKeeperBuilder::Register(const std::string &method, const std::string &ip, const std::string &port, int sockfd)
{
    if (InsertZnode(method, Imagine_ZooKeeper::ZooKeeperUtil::GenerateZNodeStat(ip, port), Load_Balance, "online")) {
        RpcZKHeart *new_heart = new RpcZKHeart(method, std::make_pair(ip, port), SetTimer(std::bind(timer_callback_, sockfd, time_out_), 15.0, 0.0));
        pthread_mutex_lock(&heart_map_lock_);
        heart_map_.insert(std::make_pair(sockfd, new_heart));
        pthread_mutex_unlock(&heart_map_lock_);

        return true;
    }

    return false;
}

bool RpcZooKeeperBuilder::DeRegister(const std::string &method, const std::string &ip, const std::string &port, int sockfd)
{
    if (DeleteZnode(method, Imagine_ZooKeeper::ZooKeeperUtil::GenerateZNodeStat(ip, port), "offline")) {
        DeleteHeartNode(sockfd);
        return true;
    }

    return false;
}

bool RpcZooKeeperBuilder::HeartBeatProcessor(int sockfd)
{
    pthread_mutex_lock(&heart_map_lock_);
    if (heart_map_.find(sockfd) == heart_map_.end()) {
        pthread_mutex_unlock(&heart_map_lock_);
        return false;
    }
    heart_map_.find(sockfd)->second->ReSetLastRequestTime();
    pthread_mutex_unlock(&heart_map_lock_);

    return true;
}

std::pair<std::string, std::string> RpcZooKeeperBuilder::SearchMethod(const std::string &method, std::shared_ptr<RpcWatcher> new_watcher)
{
    return GetClusterZnodeStat(method, true, new_watcher);
}

bool RpcZooKeeperBuilder::DeleteHeartNode(int sockfd)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<int, RpcZKHeart *>::iterator it = heart_map_.find(sockfd);
    if (it == heart_map_.end()) {
        return false; // 已删除
        throw std::exception();
    }
    RpcZKHeart *heart_node = it->second;
    heart_map_.erase(it);
    RemoveTimer(heart_node->GetTimerfd());
    delete heart_node;
    pthread_mutex_unlock(&heart_map_lock_);

    return true;
}

bool RpcZooKeeperBuilder::GetHeartNodeInfo(int sockfd, std::string &cluster_name, long long &last_request_time, std::pair<std::string, std::string> &stat)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<int, RpcZKHeart *>::iterator it = heart_map_.find(sockfd);
    if (it == heart_map_.end()) {
        // 已删除
        pthread_mutex_unlock(&heart_map_lock_);
        return false;
    }
    cluster_name = it->second->GetClusterName();
    last_request_time = it->second->GetLastRequestTime();
    stat = it->second->GetStat();
    pthread_mutex_unlock(&heart_map_lock_);

    return true;
}

long long RpcZooKeeperBuilder::GetHeartNodeLastRequestTime(int sockfd)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<int, RpcZKHeart *>::iterator it = heart_map_.find(sockfd);
    if (it == heart_map_.end()) {
        // 已删除
        pthread_mutex_unlock(&heart_map_lock_);
        return -1;
    }
    long long last_request_time = it->second->GetLastRequestTime();
    pthread_mutex_unlock(&heart_map_lock_);

    return last_request_time;
}

} // namespace Imagine_Rpc