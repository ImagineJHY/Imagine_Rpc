#include "Imagine_Rpc/RpcConnection.h"

namespace Imagine_Rpc
{

RpcConnection::RpcConnection()
{
}

RpcConnection::RpcConnection(std::shared_ptr<Imagine_Muduo::Channel> channel) : TcpConnection(channel)
{
}

RpcConnection::RpcConnection(Imagine_Muduo::Server* server, std::shared_ptr<Imagine_Muduo::Channel> channel) : TcpConnection(server, channel)
{
}

RpcConnection::~RpcConnection()
{
}

Imagine_Muduo::Connection* RpcConnection::Create(const std::shared_ptr<Imagine_Muduo::Channel>& channel) const
{
    return new RpcConnection(server_, channel);
}

void RpcConnection::DefaultReadCallback(Imagine_Muduo::Connection* conn) const
{
    return;
}

void RpcConnection::DefaultWriteCallback(Imagine_Muduo::Connection* conn) const
{
    return;
}

} // namespace Imagine_Rpc