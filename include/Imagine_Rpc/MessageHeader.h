#ifndef IMAGINE_RPC_MESSAGEHEADER_H
#define IMAGINE_RPC_MESSAGEHEADER_H

#include "RpcUtil.h"

#include <unistd.h>
#include <string>

namespace Imagine_Rpc
{

class MessageHeader
{
 public:
    MessageHeader();

    MessageHeader(size_t context_len, size_t msg_len);

    ~MessageHeader();

    std::string SerializeToString();

    bool AppendToString(std::string& str);

    bool ParseFromString(const std::string& str);

    bool ParseFromArray(const char* buf, size_t buf_size);

    size_t GetHeaderSize();

    size_t GetContextSize();

    size_t GetMessageSize();

 private:
    size_t header_size_;
    size_t context_size_;
    size_t msg_size_;
};


} // namespace Imagine_Rpc



#endif