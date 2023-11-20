#ifndef IMAGINE_RPC_RPCCONNECTION_H
#define IMAGINE_RPC_RPCCONNECTION_H

#include "Imagine_Muduo/TcpConnection.h"
#include "common_definition.h"
#include "TransportDecoder.h"
// #include "Imagine_Muduo/Server.h"
// #include "Imagine_Muduo/Channel.h"

namespace Imagine_Rpc
{

class RpcConnection : public Imagine_Muduo::TcpConnection
{
 public:
    RpcConnection();

    RpcConnection(std::shared_ptr<Imagine_Muduo::Channel> channel);

    RpcConnection(Imagine_Muduo::Server* server, std::shared_ptr<Imagine_Muduo::Channel> channel);

    ~RpcConnection();

    Imagine_Muduo::Connection* Create(std::shared_ptr<Imagine_Muduo::Channel> channel);

    void DefaultReadCallback(Imagine_Muduo::Connection* conn);

    void DefaultWriteCallback(Imagine_Muduo::Connection* conn);
};

} // namespace Imagine_Rpc


#endif