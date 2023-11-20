#ifndef IMAGINE_RPC_RPCSERVERCONNECTION_H
#define IMAGINE_RPC_RPCSERVERCONNECTION_H

#include "RpcConnection.h"
#include "RpcServerBuilder.h"

namespace Imagine_Rpc
{

class RpcServerConnection : public RpcConnection
{
 public:
    RpcServerConnection();

    RpcServerConnection(std::shared_ptr<Imagine_Muduo::Channel> channel);

    RpcServerConnection(Imagine_Muduo::Server* server, std::shared_ptr<Imagine_Muduo::Channel> channel);

    ~RpcServerConnection();

    Imagine_Muduo::Connection* Create(std::shared_ptr<Imagine_Muduo::Channel> channel);

    void DefaultReadCallback(Imagine_Muduo::Connection* conn);

    void DefaultWriteCallback(Imagine_Muduo::Connection* conn);
};

} // namespace Imagine_Rpc

#endif