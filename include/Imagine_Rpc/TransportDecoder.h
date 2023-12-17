#ifndef IMAGINE_RPC_TRANSPORTDECODER_H
#define IMAGINE_RPC_TRANSPORTDECODER_H

#include "common_typename.h"

namespace Imagine_Rpc
{

class Context;
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