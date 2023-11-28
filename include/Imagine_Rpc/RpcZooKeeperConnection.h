#ifndef IMAGINE_RPC_RPCZOOKEEPERCONNECTION_H
#define IMAGINE_RPC_RPCZOOKEEPERCONNECTION_H

#include "RpcConnection.h"
#include "RpcServerBuilder.h"

namespace Imagine_Rpc
{

class RpcZooKeeperConnection : public RpcConnection
{
 public:
    RpcZooKeeperConnection();

    RpcZooKeeperConnection(std::shared_ptr<Imagine_Muduo::Channel> channel);

    RpcZooKeeperConnection(Imagine_Muduo::Server* server, std::shared_ptr<Imagine_Muduo::Channel> channel);

    ~RpcZooKeeperConnection();

    Imagine_Muduo::Connection* Create(std::shared_ptr<Imagine_Muduo::Channel> channel);

    void DefaultReadCallback(Imagine_Muduo::Connection* conn);

    void DefaultWriteCallback(Imagine_Muduo::Connection* conn);
};

} // namespace Imagine_Rpc

#endif