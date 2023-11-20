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

    ~RpcServer();

 private:
    Builder* builder_;
};

} // namespace Imagine_Rpc

#endif