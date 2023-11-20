#include "Imagine_Rpc/MessageHeader.h"

namespace Imagine_Rpc
{

MessageHeader::MessageHeader() : header_size_(0), context_size_(0), msg_size_(0)
{
}

MessageHeader::MessageHeader(size_t context_len, size_t msg_len) : header_size_(0), context_size_(context_len), msg_size_(msg_len)
{
}

MessageHeader::~MessageHeader()
{
}

std::string MessageHeader::SerializeToString()
{
    if (!context_size_ || !msg_size_) {
        throw std::exception();
    }

    return RpcUtil::IntToString(context_size_) + "\r\n" + RpcUtil::IntToString(msg_size_) + "\r\n";
}

bool MessageHeader::AppendToString(std::string& str)
{
    if (!context_size_ || !msg_size_) {
        throw std::exception();
    }
    str += RpcUtil::IntToString(context_size_) + "\r\n" + RpcUtil::IntToString(msg_size_) + "\r\n";

    return true;
}

bool MessageHeader::ParseFromString(const std::string& str)
{
    return false;
}

bool MessageHeader::ParseFromArray(const char* buf, size_t buf_size)
{
    size_t idx;
    std::string context_len_str;
    std::string msg_len_str;
    header_size_ = context_size_ = msg_size_ = 0;

    for (idx = 0; idx < buf_size; idx++) {
        if (buf[idx] == '\n') {
            if (idx == 0) {
                throw std::exception();
            }
            context_size_ = RpcUtil::StringToInt(context_len_str);
            break;
        } else if (buf[idx] == '\r') {
            continue;
        } else if ('0' <= buf[idx] && buf[idx] <= '9') {
            context_len_str.push_back(buf[idx]);
        } else {
            throw std::exception();
        }
    }

    if (context_size_ == 0) {
        return false;
    }

    for (idx = idx + 1; idx < buf_size; idx++) {
        if (buf[idx] == '\n') {
            if (idx == 0) {
                throw std::exception();
            }
            msg_size_ = RpcUtil::StringToInt(msg_len_str);
            break;
        } else if (buf[idx] == '\r') {
            continue;
        } else if ('0' <= buf[idx] && buf[idx] <= '9') {
            msg_len_str.push_back(buf[idx]);
        } else {
            throw std::exception();
        }
    }

    if (msg_size_ == 0) {
        return false;
    }

    header_size_ = idx + 1;
    return true;
}

size_t MessageHeader::GetHeaderSize()
{
    return header_size_;
}

size_t MessageHeader::GetContextSize()
{
    return context_size_;
}

size_t MessageHeader::GetMessageSize()
{
    return msg_size_;
}

} // namespace Imagine_Rpc
