#ifndef IMAGINE_RPC_RPC_H
#define IMAGINE_RPC_RPC_H

#include<Imagine_Muduo/Imagine_Muduo/EventLoop.h>
// #include<Imagine_Muduo/Imagine_Muduo/TimeUtil.h>

#include<string>
#include<vector>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<functional>

#include"Callbacks.h"

using namespace Imagine_Muduo;


namespace Imagine_Rpc{


class Rpc{

// public:
//     using RpcCommunicateCallback=std::function<bool(const char*,int)>;//Communicate函数中用于粘包判断的回调函数
//     using RpcTimerCallback=std::function<void()>;
//     using RpcTimeOutCallback=std::function<void()>;
    /*
        -第一个参数用于传入新收到的数据(不会重复读,之前读过的内容会放在vector中)
        -每次调用都会将收到的数据全部放在vector中(传出参数)
        -如果一次读取的数据结尾恰好是"\r\n",并且发生粘包,则在vector中push_back一个"\r\n"标识
        -在readback中
            -若vector不以"\r\n"结尾,则新数据的第一段需要和vector尾部元素拼接在一起
            -否则，将vector尾部的"\r\n删除,再push_back新数据
    */

public:
    static const double default_delay_;

public:
    // static int Send(const std::string& data);
    // static std::string Recv();
    //
    /*
        序列化规则:
            -string中:
                -通过\r\n作数据切片
                -第一个数据记录总字节数
                -第二个数据记录函数名
                //-第三个数据记录参数数目,用于进行粘包判断-----------废弃
                -最后一个数据也以\r\n结尾
            -vector中:
                -第一个数据是函数名
                -第二个数据是参数数目
                -之后的每一个数据是一个参数
                -若vector的string中含有\r\n,则Rpc为其添加一个\r\n(两个连续的\r\n表示一个用户的\r\n)
        粘包问题:
            -在Deserialize函数中进行判断,若发生粘包,返回仅包含一个元素"\r\n"的std::vector<std::string>
    */

   //只能用于Client和Server之间通信信息的序列化
    static std::string Serialize(const std::vector<std::string>& input);
    static std::vector<std::string> Deserialize(const std::string& input, int num=0);
    static bool IsComplete(const std::vector<std::string>& output,int num);//判断粘包
    static bool IsComplete(const std::string& recv_);//判断粘包

    //粘包判断函数
    static bool DefaultCommunicateCallback(const char* recv_, int size);

    static int StringToInt(const std::string& input);
    static std::string IntToString(int input);
    static double StringToDouble(const std::string& input);

    //内部使用的通信函数
    static struct sockaddr_in PackIpPort(const std::string& ip_, const std::string& port_);//打包IP端口号到struct sockaddr_in

    //Server、Client调用一次会话通信接口
    static std::string Communicate(const std::string& send_, const struct sockaddr_in* addr, bool wait_recv=true);//sockfd_为nullptr表示结束直接关闭socket

    //Server、Client调用长连接通信接口
    static std::string Communicate(const std::string& send_, int* sockfd, bool wait_recv=true);
    static bool Connect(const std::string& ip, const std::string& port, int* sockfd);

    //去掉Rpc通信协议的多余信息
    static bool Unpack(std::vector<std::string>& message);

    //对简单iovec进行处理
    static struct sockaddr_in* GetAddr(const struct iovec* input_iovec);
    static std::string GetIovec(const struct iovec* input_iovec);//将输入的iovec全部读到string
    static struct iovec* SetIovec(const std::string& input,int len, bool alive_=true, bool read_all=true);//初始化一个传出iovec

    static std::string GenerateDefaultHead(const std::string& content);//生成默认通信头部

    //RpcZooKeeper请求的默认回复函数
    static std::string GenerateDefaultSuccessMessage();
    static std::string GenerateDefaultFailureMessage();

    //IP/Port转换函数
    static std::string ConvertIpFromNetToString(const unsigned int net_ip);
    static std::string ConvertPortFromNetToString(const unsigned short int net_port);
    static unsigned int ConvertIpFromStringToNet(const std::string& string_ip);
    static unsigned short int ConvertPortFromStringToNet(const std::string& string_port);

    static void DefaultKeepAliveClient(EventLoop* loop_, RpcTimerCallback timer_callback_);//客户端用于定时发送心跳的函数
    static void DefaultClientTimerCallback(int sockfd, const std::string& name, RpcTimeOutCallback callback);//客户端默认定时器回调函数，用于发送心跳包
    
    static std::string GenerateDefaultHeartbeatContent(const std::string& name);//生成默认心跳包

    static void SetSocketOpt(int sockfd);//设置端口复用

    // static long long SetTimer(double interval, double delay, Rpc::RpcTimerCallback callback);
    // bool RemoveTimer(long long timerfd);

    /*
    -flag为true:表示粘包,设置为只读不写
    -flag为false:表示未粘包,设置为只写不读
    */
};



}


#endif