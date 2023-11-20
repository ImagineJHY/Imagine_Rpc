#include "Imagine_Rpc/TransportDecoder.h"

#include "Imagine_Rpc/Builder.h"
#include "Imagine_Rpc/Context.pb.h"
#include "Imagine_Rpc/MessageHeader.h"

namespace Imagine_Rpc
{

bool TransportDecoder::ContextDecoder(const char* buf, size_t buf_size, Context* context, size_t* header_size)
{
    MessageHeader header;
    if (!header.ParseFromArray(buf, buf_size)) {
        return false;
    }

    *header_size = header.GetHeaderSize();

    if (buf_size < *header_size + header.GetContextSize()) {
        return false;
    }

    if (!context->ParsePartialFromArray(buf + *header_size, header.GetContextSize())) {
        return false;
    }

    return true;
}

bool TransportDecoder::MessageDecoder(const char* buf, size_t buf_size, RpcMessage* msg)
{
    if (!msg->ParsePartialFromArray(buf, buf_size)) {
        return false;
    }

    return true;
}

TransportDecoder::TransportDecoder()
{
}

TransportDecoder::~TransportDecoder()
{
}

} // namespace Imagine_Rpc