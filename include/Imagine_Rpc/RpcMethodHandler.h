#ifndef IMAGINE_RPC_RPCMETHODHANDLER_H
#define IMAGINE_RPC_RPCMETHODHANDLER_H

#include "MethodHandler.h"
#include "TransportDecoder.h"

namespace Imagine_Rpc
{

class Context;

template <class RequestMessageType, class ResponseMessageType>
class RpcMethodHandler : public MethodHandler
{
 public:
    RpcMethodHandler();

    RpcMethodHandler(std::function<Status(Context* , RequestMessageType*, ResponseMessageType*)> func);

    ~RpcMethodHandler();

    Status HandleMethod(Context* context, RpcMessage* request_msg, RpcMessage* response_msg) const override;
 
 private:
    std::function<Status(Context* , RequestMessageType*, ResponseMessageType*)> func_;
};

template <class RequestMessageType, class ResponseMessageType>
RpcMethodHandler<RequestMessageType, ResponseMessageType>::RpcMethodHandler() : MethodHandler(new RequestMessageType(), new ResponseMessageType())
{
}

template <class RequestMessageType, class ResponseMessageType>
RpcMethodHandler<RequestMessageType, ResponseMessageType>::RpcMethodHandler(std::function<Status(Context* , RequestMessageType*, ResponseMessageType*)> func) : MethodHandler(new RequestMessageType(), new ResponseMessageType()), func_(func)
{
}

template <class RequestMessageType, class ResponseMessageType>
RpcMethodHandler<RequestMessageType, ResponseMessageType>::~RpcMethodHandler()
{
}

template <class RequestMessageType, class ResponseMessageType>
Status RpcMethodHandler<RequestMessageType, ResponseMessageType>::HandleMethod(Context* context, RpcMessage* request_msg, RpcMessage* response_msg) const
{
    RequestMessageType* request_msg_type = dynamic_cast<RequestMessageType*>(request_msg);
    if (request_msg_type == nullptr) {
        LOG_INFO("Request Message Type Error!");
        throw std::exception();
    }
    ResponseMessageType* response_msg_type = dynamic_cast<ResponseMessageType*>(response_msg);
    if (response_msg_type == nullptr) {
        LOG_INFO("Response Message Type Error!");
        throw std::exception();
    }

    return func_(context, request_msg_type, response_msg_type);
}

} // namespace Imagine_Rpc

#endif