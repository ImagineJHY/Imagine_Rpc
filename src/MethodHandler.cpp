#include "Imagine_Rpc/MethodHandler.h"

namespace Imagine_Rpc
{

MethodHandler::MethodHandler()
{
}

MethodHandler::MethodHandler(RpcMessage* request_msg, RpcMessage* response_msg) : request_msg_(request_msg), response_msg_(response_msg)
{
}

MethodHandler::~MethodHandler()
{
}

RpcMessage* MethodHandler::NewRequestMessage() const
{
    return request_msg_->New();
}

RpcMessage* MethodHandler::NewResponseMessage() const
{
    return response_msg_->New();
}

} // namespace Imagine_Rpc