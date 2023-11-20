#ifndef IMAGINE_RPC_RPCSERVER_H
#define IMAGINE_RPC_RPCSERVER_H

#include "Imagine_Time/Timer.h"
#include "common_definition.h"
#include "Builder.h"

namespace Imagine_Rpc
{

class RpcServerBuilder;

class RpcServer
{
 public:
    RpcServer();

    RpcServer(RpcServerBuilder* builder);

    RpcServer(const std::string& profile_name);

    RpcServer(const YAML::Node& config);

    RpcServer* const Start();

    RpcServer* const RegisterService(Service* service);

    RpcServer* const DeregisterService(Service* service);

    ~RpcServer();

 private:
    RpcServerBuilder* builder_;
};

} // namespace Imagine_Rpc

#endif