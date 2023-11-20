#include "Imagine_Rpc/RpcServer.h"

#include "Imagine_Rpc/RpcServerBuilder.h"

namespace Imagine_Rpc
{

RpcServer::RpcServer()
{
}

RpcServer::RpcServer(RpcServerBuilder* builder) : builder_(builder)
{
}

RpcServer::~RpcServer()
{
}

} // namespace Imagine_Rpc