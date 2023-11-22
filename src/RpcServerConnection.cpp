#include "Imagine_Rpc/RpcServerConnection.h"

#include "Imagine_Rpc/RpcUtil.h"
#include "Imagine_Rpc/Context.pb.h"

namespace Imagine_Rpc
{

RpcServerConnection::RpcServerConnection()
{
}

RpcServerConnection::RpcServerConnection(std::shared_ptr<Imagine_Muduo::Channel> channel) : RpcConnection(channel)
{
}

RpcServerConnection::RpcServerConnection(Imagine_Muduo::Server* server, std::shared_ptr<Imagine_Muduo::Channel> channel) : RpcConnection(server, channel)
{
}
    
RpcServerConnection::~RpcServerConnection()
{
}

Imagine_Muduo::Connection* RpcServerConnection::Create(std::shared_ptr<Imagine_Muduo::Channel> channel)
{
    return new RpcServerConnection(server_, channel);
}

void RpcServerConnection::DefaultReadCallback(Imagine_Muduo::Connection* conn)
{
    LOG_INFO("RpcServer Receive peer Message From %s:%s!", conn->GetPeerIp().c_str(), conn->GetPeerPort().c_str());

    RpcServerBuilder* builder = dynamic_cast<RpcServerBuilder*>(server_);
    if (builder == nullptr) {
        throw std::exception();
    }

    // 解析context
    Context* context = new Context();
    size_t header_size = 0;

    if (!TransportDecoder::ContextDecoder(conn->GetData(), conn->GetMessageLen(), context, &header_size)) {
        conn->SetRevent(Imagine_Muduo::Connection::Event::Read);
        conn->IsClearReadBuffer(false);
        LOG_INFO("Context not Complete");

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
        LOG_INFO("Request Message not Complete");

        return;
    }

    conn->SetMessageEndIdx(header_size + context->ByteSize() + request_msg->ByteSize());
    
    LOG_INFO("RpcService /%s/%s is Found!", context->service_name_().c_str(), context->method_name_().c_str());
    handler->HandleMethod(context, request_msg, response_msg);

    // 暂时默认保持连接
    builder->UpdatetUser(this);

    std::string response_content;
    LOG_INFO("context size is %d, response_msg size is %d", context->ByteSize(), response_msg->ByteSize());
    RpcUtil::SerializeMessage(context, response_msg, response_content);
    conn->AppendData(response_content.c_str(), response_content.size());
    conn->SetRevent(Imagine_Muduo::Connection::Event::Write);
    conn->IsClearReadBuffer(true);

    delete context;
    delete request_msg;
    delete response_msg;
}

void RpcServerConnection::DefaultWriteCallback(Imagine_Muduo::Connection* conn)
{
    conn->IsClearWriteBuffer(true);
    conn->SetRevent(Imagine_Muduo::Connection::Event::Read);
}

} // namespace Imagine_Rpc