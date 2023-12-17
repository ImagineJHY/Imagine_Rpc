#ifndef IMAGINE_RPC_STUB_H
#define IMAGINE_RPC_STUB_H

#include "common_typename.h"

#include <unistd.h>

namespace Imagine_Rpc
{

enum class Status;

class Stub
{
 public:
    Stub();

    Stub(const std::string& profile_name);

    Stub(const YAML::Node& config);

    Stub(const Stub& stub);

    ~Stub();

    void Init(const std::string& profile_name);

    void Init(const YAML::Node& config);

    Stub* SearchNewServer();

    Stub* ConnectServer();

    const Stub* CloseConnection() const;

    Status Call(RpcMessage* request_msg, RpcMessage* response_msg);

    Status CallConnectServer(RpcMessage* request_msg, RpcMessage* response_msg) const;

    Stub* SetServerIp(const std::string& server_ip);

    Stub* SetServerPort(const std::string& server_port);

    Stub* SetServiceName(const std::string& service_name);

    Stub* SetMethodName(const std::string& method_name);

    Stub* SetSockfd(int sockfd);

    std::string GetServerIp() const;

    std::string GetServerPort() const;

    int GetSockfd() const;

 protected:
    // 配置文件参数
    std::string server_ip_;         // server的IP
    std::string server_port_;       // server的Port
    std::string zookeeper_ip_;      // ZK的IP
    std::string zookeeper_port_;    // ZK的Port
    std::string service_name_;      // 暂时不支持在配置文件中读取(其它类的配置文件无此项, 怕遗忘造成core)
    std::string method_name_;       // 暂时不支持在配置文件中读取(其它类的配置文件无此项, 怕遗忘造成core)
    bool singleton_log_mode_;       // 日志模式(目前仅支持单例)

    Logger* logger_;                // 日志对象

 private:
    int sockfd_;                    // 建立连接后的socket(支持建立连接后直接使用其进行通信)
};

} // namespace Imagine_Rpc


#endif