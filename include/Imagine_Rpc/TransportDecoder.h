#ifndef IMAGINE_RPC_TRANSPORTDECODER_H
#define IMAGINE_RPC_TRANSPORTDECODER_H

#include "Imagine_Muduo/TcpConnection.h"
#include "common_definition.h"
#include "Context.pb.h"

namespace Imagine_Rpc
{

class Builder;

class TransportDecoder
{
 public:
   static bool ContextDecoder(const char* buf, size_t buf_size, Context* context, size_t* header_size);

   static bool MessageDecoder(const char* buf, size_t buf_size, RpcMessage* msg);

 public:
    TransportDecoder();

    ~TransportDecoder();
};

} // namespace Imagine_Rpc

#endif