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

Imagine_Muduo::Connection* RpcConnection::Create(std::shared_ptr<Imagine_Muduo::Channel> channel)
{
    return new RpcConnection(server_, channel);
}

void RpcConnection::DefaultReadCallback(Imagine_Muduo::Connection* conn)
{
    return;
}

void RpcConnection::DefaultWriteCallback(Imagine_Muduo::Connection* conn)
{
    return;
}

} // namespace Imagine_Rpc