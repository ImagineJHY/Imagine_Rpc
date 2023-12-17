#ifndef IMAGINE_RPC_RPCSTUB_H
#define IMAGINE_RPC_RPCSTUB_H

#include "Stub.h"

namespace Imagine_Rpc
{

template <class RequestMessageType, class ResponseMessageType>
class RpcStub : public Stub
{
 public:
    RpcStub(const std::string& profile_name, const std::string& service_name, const std::string& method_name);

    RpcStub(const YAML::Node& config, const std::string& service_name, const std::string& method_name);

    ~RpcStub();

    Status Call(Context* context, RequestMessageType* request_msg, ResponseMessageType* response_msg);

 private:
    
};

template <class RequestMessageType, class ResponseMessageType>
RpcStub<RequestMessageType, ResponseMessageType>::RpcStub(const std::string& profile_name, const std::string& service_name, const std::string& method_name) : Stub(profile_name, service_name, method_name, new RequestMessageType(), new ResponseMessageType())
{
}

template <class RequestMessageType, class ResponseMessageType>
RpcStub<RequestMessageType, ResponseMessageType>::RpcStub(const YAML::Node& config, const std::string& service_name, const std::string& method_name) : Stub(config, service_name, method_name, new RequestMessageType(), new ResponseMessageType())
{
}

template <class RequestMessageType, class ResponseMessageType>
RpcStub<RequestMessageType, ResponseMessageType>::~RpcStub()
{
}

template <class RequestMessageType, class ResponseMessageType>
Status RpcStub<RequestMessageType, ResponseMessageType>::Call(Context* context, RequestMessageType* request_msg, ResponseMessageType* response_msg)
{
    if (!server_ip_.size() || !server_port_.size()) {
        // 未初始化server, 向zk获取server
        Context request_context_zk;
        Internal::InternalMessage request_msg_zk;
        Context response_context_zk;
        Internal::InternalMessage response_msg_zk;
        RpcUtil::GenerateCallZooKeeperContext(&request_context_zk, &request_msg_zk, service_name_, method_name_);
        RpcUtil::SendMessage(&request_context_zk, &request_msg_zk, &response_context_zk, &response_msg_zk, zookeeper_ip_, zookeeper_port_);
        server_ip_ = response_msg_zk.server_ip_();
        server_port_ = response_msg_zk.server_port_();
    }

    RpcUtil::GenerateCallServerContext(context, request_msg, service_name_, method_name_);
    Context response_context;
    RpcUtil::SendMessage(context, request_msg, &response_context, response_msg, server_ip_, server_port_);

    return Status::OK;
}

} // namespace Imagine_Rpc

#endif