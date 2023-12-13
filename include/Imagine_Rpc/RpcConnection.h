#ifndef IMAGINE_RPC_RPCCONNECTION_H
#define IMAGINE_RPC_RPCCONNECTION_H

#include "Imagine_Muduo/Imagine_Muduo.h"

namespace Imagine_Rpc
{

class RpcConnection : public Imagine_Muduo::TcpConnection
{
 public:
    RpcConnection();

    RpcConnection(std::shared_ptr<Imagine_Muduo::Channel> channel);

    RpcConnection(Imagine_Muduo::Server* server, std::shared_ptr<Imagine_Muduo::Channel> channel);

    ~RpcConnection();

    Imagine_Muduo::Connection* Create(const std::shared_ptr<Imagine_Muduo::Channel>& channel) const;

    void DefaultReadCallback(Imagine_Muduo::Connection* conn);

    void DefaultWriteCallback(Imagine_Muduo::Connection* conn);
};

} // namespace Imagine_Rpc


#endif