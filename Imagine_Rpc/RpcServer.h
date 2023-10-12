#ifndef IMAGINE_RPC_RPCSERVER_H
#define IMAGINE_RPC_RPCSERVER_H

#include<unistd.h>
#include<string>
#include<functional>
#include<unordered_map>
#include<Imagine_Muduo/Imagine_Muduo/EventLoop.h>
#include"Rpc.h"
#include<stdarg.h>
#include<unordered_map>
#include"RpcZooKeeper.h"

using namespace Imagine_Muduo;


namespace Imagine_Rpc{

class RpcServer{

// public:
    // using RpcCallback=std::function<std::vector<std::string>(const std::vector<std::string>&)>;
    // using RpcServerTimerCallback=std::function<void(int,double)>;//client请求保持连接

public:
    class RpcSHeart{
        public:
            RpcSHeart(long long timerfd_, long long time_=TimeUtil::GetNow())
                :timerfd(timerfd_),last_request_time(time_)
            {
            }

            bool ReSetLastRequestTime(){
                last_request_time=TimeUtil::GetNow();
                return true;
            }

            long long GetLastRequestTime(){
                return last_request_time;
            }

            long long GetTimerfd(){
                return timerfd;
            }

        private:
            long long timerfd;
            long long last_request_time;//记录最后一次心跳时间(绝对时间)
    };

public:

    RpcServer(const std::string& ip_, const std::string& port_, const std::string& keeper_ip_="", const std::string& keeper_port_="", int max_client_num=10000);
    
    RpcServer(const std::string& ip_, const std::string& port_, std::unordered_map<std::string,RpcCallback> callbacks_, const std::string& keeper_ip_="", const std::string& keeper_port_="", int max_client_num=10000);

    ~RpcServer();

    bool SetKeeper(const std::string& keeper_ip_, const std::string& keeper_port_);
    
    //注册函数(加锁),若没有zookeeper则只在本地注册
    void Callee(const std::string& method, RpcCallback callback);

    void loop();

    //有用户请求调用函数,为其注册心跳检测
    bool UpdatetUser(int sockfd);

    //心跳超时,关闭连接
    bool DeleteUser(int sockfd);

    // EventLoop* GetEventLoop(){return loop_;}

    //向ZooKeeper注册函数
    bool Register(const std::string& method,const std::string& keeper_ip, const std::string& keeper_port);
    bool DeRegister(const std::string& method, const std::string& keeper_ip, const std::string& keeper_port);

    RpcCallback SearchFunc(std::string method);

    void SetDefaultReadCallback();

    void SetDefaultWriteCallback();

    void SetDefaultCommunicateCallback();

    void SetDefaultTimerCallback();

    void SetDefaultTimeOutCallback();

    RpcServerTimerCallback GetTimerCallback();

    std::string GenerateDefaultRpcKeeperContent(const std::string& option, const std::string& method);

    std::string GenerateDefaultRpcClientContent();

    long long SetTimer(double interval, double delay, RpcTimerCallback callback);

    bool RemoveTimer(long long timerfd);

    bool GetHeartNodeInfo(int sockfd, long long& last_request_time);

    long long GetHeartNodeLastRequestTime(int sockfd);

private:

    const std::string ip;
    const std::string port;
    std::string keeper_ip;
    std::string keeper_port;

    pthread_mutex_t callback_lock;
    std::unordered_map<std::string,RpcCallback> callbacks;
    int callback_num;

    EventCallback read_callback;
    EventCallback write_callback;
    EventCommunicateCallback communicate_callback;
    EventLoop* loop_=nullptr;

    pthread_mutex_t heart_map_lock;
    std::unordered_map<int,RpcSHeart*> heart_map;
    RpcServerTimerCallback timer_callback;

    RpcTimeOutCallback timeout_callback;

    // EventLoop* register_loop_=nullptr;
    // int max_register_num=100;

    const double time_out=120.0;
};



}


#endif