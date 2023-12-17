#ifndef IMAGINE_RPC_MESSAGEHEADER_H
#define IMAGINE_RPC_MESSAGEHEADER_H

#include <string>
#include <unistd.h>

namespace Imagine_Rpc
{

class MessageHeader
{
 public:
    MessageHeader();

    MessageHeader(size_t context_len, size_t msg_len);

    ~MessageHeader();

    std::string SerializeToString() const;

    const MessageHeader* AppendToString(std::string& str) const;

    bool ParseFromString(const std::string& str);

    bool ParseFromArray(const char* buf, size_t buf_size);

    size_t GetHeaderSize() const;

    size_t GetContextSize() const;

    size_t GetMessageSize() const;

 private:
    size_t header_size_;
    size_t context_size_;
    size_t msg_size_;
};


} // namespace Imagine_Rpc



#endif