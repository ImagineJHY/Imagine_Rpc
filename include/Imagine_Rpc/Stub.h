#ifndef IMAGINE_RPC_STUB_H
#define IMAGINE_RPC_STUB_H

#include "Imagine_Log/Logger.h"
#include "common_definition.h"

namespace Imagine_Rpc
{

class Stub
{
 public:
    Stub();

    Stub(std::string profile_name);

    Stub(YAML::Node config);

    ~Stub();

    void Init(std::string profile_name);

    void Init(YAML::Node config);

    Status Call(RpcMessage* request_msg, RpcMessage* response_msg);

 protected:
    std::string zookeeper_ip_;
    std::string zookeeper_port_;
    std::string log_name_;
    std::string log_path_;
    size_t max_log_file_size_;
    bool async_log_;
    bool singleton_log_mode_;
    std::string log_title_;
    bool log_with_timestamp_;

    Imagine_Tool::Logger* logger_;

 protected:
    RpcMessage* request_msg_;
    RpcMessage* response_msg_;
    std::string server_ip_;
    std::string server_port_;
    std::string service_name_;
    std::string method_name_;
};

} // namespace Imagine_Rpc


#endif