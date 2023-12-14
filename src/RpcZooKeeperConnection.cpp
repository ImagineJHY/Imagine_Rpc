#include "Imagine_Rpc/RpcZooKeeperConnection.h"

#include "Imagine_Rpc/RpcUtil.h"
#include "Imagine_Rpc/log_macro.h"
#include "Imagine_Rpc/Context.pb.h"
#include "Imagine_Rpc/MethodHandler.h"
#include "Imagine_Rpc/TransportDecoder.h"
#include "Imagine_Rpc/ServiceDescriptor.h"
#include "Imagine_Rpc/RpcZooKeeperBuilder.h"

namespace Imagine_Rpc
{

RpcZooKeeperConnection::RpcZooKeeperConnection() : RpcConnection()
{
}

RpcZooKeeperConnection::RpcZooKeeperConnection(std::shared_ptr<Imagine_Muduo::Channel> channel) : RpcConnection(channel)
{
}

RpcZooKeeperConnection::RpcZooKeeperConnection(Imagine_Muduo::Server* server, std::shared_ptr<Imagine_Muduo::Channel> channel) : RpcConnection(server, channel)
{
}

RpcZooKeeperConnection::~RpcZooKeeperConnection()
{
}

Imagine_Muduo::Connection* RpcZooKeeperConnection::Create(const std::shared_ptr<Imagine_Muduo::Channel>& channel) const
{
    return new RpcZooKeeperConnection(server_, channel);
}

void RpcZooKeeperConnection::DefaultReadCallback(Imagine_Muduo::Connection* conn)
{
    IMAGINE_RPC_LOG("this is RpcZooKeeper!");

    RpcZooKeeperBuilder* builder = dynamic_cast<RpcZooKeeperBuilder*>(server_);
    if (builder == nullptr) {
        throw std::exception();
    }
    // 解析context
    Context* context = new Context();
    size_t header_size = 0;

    if (!TransportDecoder::ContextDecoder(conn->GetData(), conn->GetMessageLen(), context, &header_size)) {
        conn->SetRevent(Imagine_Muduo::Connection::Event::Read);
        conn->IsClearReadBuffer(false);
        IMAGINE_RPC_LOG("Context not Complete");

        return;
    }

    // 获取handler, 获取message指针并解析message
    const MethodHandler* handler = builder->FindServiceDescriptor(context->service_name_())->FindMethodHandler(context->method_name_());
    RpcMessage* request_msg = handler->NewRequestMessage();
    RpcMessage* response_msg = handler->NewResponseMessage();

    if (conn->GetMessageLen() - header_size - context->ByteSize() < context->message_size_() || 
        !TransportDecoder::MessageDecoder(conn->GetData() + header_size + context->ByteSize(), conn->GetMessageLen() - header_size - context->ByteSize(), request_msg)) {
        conn->SetRevent(Imagine_Muduo::Connection::Event::Read);
        conn->IsClearReadBuffer(false);
        IMAGINE_RPC_LOG("Request Message not Complete");

        delete context;
        delete request_msg;
        delete response_msg;

        return;
    }

    conn->SetMessageEndIdx(header_size + context->ByteSize() + request_msg->ByteSize());

    context->set_sockfd_(conn->GetSockfd());
    context->set_send_ip_(conn->GetPeerIp());
    context->set_send_port_(conn->GetPeerPort());
    handler->HandleMethod(context, request_msg, response_msg);

    std::string response_content;
    RpcUtil::SerializeMessage(context, response_msg, response_content);
    conn->AppendData(response_content.c_str(), response_content.size());
    conn->SetRevent(Imagine_Muduo::Connection::Event::Write);
    conn->IsClearReadBuffer(true);

    delete context;
    delete request_msg;
    delete response_msg;
}

void RpcZooKeeperConnection::DefaultWriteCallback(Imagine_Muduo::Connection* conn)
{
    conn->IsClearWriteBuffer(true);
    conn->SetRevent(Imagine_Muduo::Connection::Event::Read);
}

} // namespace Imagine_Rpc