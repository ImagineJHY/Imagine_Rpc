#ifndef IMAGINE_RPC_METHODHANDLER_H
#define IMAGINE_RPC_METHODHANDLER_H

#include "common_typename.h"

namespace Imagine_Rpc
{

enum class Status;
class Context;

class MethodHandler
{
 public:
    MethodHandler();

    MethodHandler(RpcMessage* request_msg, RpcMessage* response_msg);

    virtual ~MethodHandler();

    virtual Status HandleMethod(Context* context, RpcMessage* request_msg, RpcMessage* response_msg) const = 0;

    RpcMessage* NewRequestMessage() const;

    RpcMessage* NewResponseMessage() const;

 private:
    RpcMessage* request_msg_;
    RpcMessage* response_msg_;
};

} // namespace Imagine_Rpc

#endif