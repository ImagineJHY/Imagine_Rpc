#ifndef IMAGINE_RPC_RPCSERVER_H
#define IMAGINE_RPC_RPCSERVER_H

#include "common_typename.h"

namespace Imagine_Rpc
{

class Service;
class RpcServerBuilder;

class RpcServer
{
 public:
    RpcServer();

    RpcServer(RpcServerBuilder* builder);

    RpcServer(const std::string& profile_name);

    RpcServer(const YAML::Node& config);

    ~RpcServer();

    RpcServer* Start() const;

    // Service由用户传递进来, 也由用户自己释放空间
    const RpcServer* RegisterService(Service* service) const;

    RpcServer* DeregisterService(Service* service);

    long long SetTimer(TimerCallback timer_callback, double interval, double delay = 0.0);

    RpcServer* RemoveTimer(long long timerfd);

 private:
    RpcServerBuilder* builder_;
};

} // namespace Imagine_Rpc

#endif