#ifndef IMAGINE_RPC_RPCSERVER_H
#define IMAGINE_RPC_RPCSERVER_H

#include "Imagine_Muduo/EventLoop.h"
#include "Imagine_Rpc/Rpc.h"
#include "Imagine_Rpc/RpcZooKeeper.h"

#include <unistd.h>
#include <string>
#include <functional>
#include <unordered_map>
#include <stdarg.h>
#include <unordered_map>

namespace Imagine_Rpc
{

class RpcServer
{
 public:
    class RpcSHeart
    {
     public:
        RpcSHeart(long long timerfd, long long time = Imagine_Tool::TimeUtil::GetNow())
            : timerfd_(timerfd), last_request_time_(time) {}

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
            return timerfd_;
        }

    private:
        long long timerfd_;
        long long last_request_time_; // 记录最后一次心跳时间(绝对时间)
    };

 public:
    RpcServer();

    RpcServer(std::string profile_name);

    RpcServer(const std::string &ip, const std::string &port, const std::string &keeper_ip = "", const std::string &keeper_port = "", int max_client_num = 10000);

    RpcServer(const std::string &ip, const std::string &port, std::unordered_map<std::string, RpcCallback> callbacks, const std::string &keeper_ip = "", const std::string &keeper_port = "", int max_client_num = 10000);

    ~RpcServer();

    void Init(std::string profile_name);

    void InitProfilePath(std::string profile_name);

    void GenerateSubmoduleProfile(YAML::Node config);

    bool SetKeeper(const std::string &keeper_ip, const std::string &keeper_port);

    // 注册函数(加锁),若没有zookeeper则只在本地注册
    void Callee(const std::string &method, RpcCallback callback);

    void loop();

    // 有用户请求调用函数,为其注册心跳检测
    bool UpdatetUser(int sockfd);

    // 心跳超时,关闭连接
    bool DeleteUser(int sockfd);

    // EventLoop* GetEventLoop(){return loop_;}

    // 向ZooKeeper注册函数
    bool Register(const std::string &method, const std::string &keeper_ip, const std::string &keeper_port);
    bool DeRegister(const std::string &method, const std::string &keeper_ip, const std::string &keeper_port);

    RpcCallback SearchFunc(std::string method);

    void SetDefaultCallback();

    void SetDefaultReadCallback();

    void SetDefaultWriteCallback();

    void SetDefaultCommunicateCallback();

    void SetDefaultTimerCallback();

    void SetDefaultTimeOutCallback();

    RpcServerTimerCallback GetTimerCallback();

    std::string GenerateDefaultRpcKeeperContent(const std::string &option, const std::string &method);

    std::string GenerateDefaultRpcClientContent();

    long long SetTimer(double interval, double delay, RpcTimerCallback callback);

    bool RemoveTimer(long long timerfd);

    bool GetHeartNodeInfo(int sockfd, long long &last_request_time);

    long long GetHeartNodeLastRequestTime(int sockfd);

 private:
    std::string ip_;
    std::string port_;
    std::string rpc_zookeeper_ip_;
    std::string rpc_zookeeper_port_;
    size_t thread_num_;
    std::string log_name_;
    std::string log_path_;
    size_t max_log_file_size_;
    bool async_log_;
    bool singleton_log_mode_;
    std::string log_title_;
    bool log_with_timestamp_;

    std::string profile_path_;
    std::string muduo_profile_name_;

 private:
    pthread_mutex_t callback_lock_;
    std::unordered_map<std::string, RpcCallback> callbacks_;
    int callback_num_;

    Imagine_Muduo::EventCallback read_callback_;
    Imagine_Muduo::EventCallback write_callback_;
    Imagine_Muduo::EventCommunicateCallback communicate_callback_;
    Imagine_Muduo::EventLoop *loop_;
    Imagine_Tool::Logger* logger_;

    pthread_mutex_t heart_map_lock_;
    std::unordered_map<int, RpcSHeart *> heart_map_;
    RpcServerTimerCallback timer_callback_;

    RpcTimeOutCallback timeout_callback_;

    // EventLoop* register_loop_ = nullptr;
    // int max_register_num_ = 100;

    const double time_out_ = 120.0;
};

} // namespace Imagine_Rpc

#endif