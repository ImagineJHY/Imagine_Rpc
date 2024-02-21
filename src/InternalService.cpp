#include "Imagine_Rpc/InternalService.h"

#include "Imagine_Rpc/RpcUtil.h"
#include "Imagine_Rpc/log_macro.h"
#include "Imagine_Rpc/Context.pb.h"
#include "Imagine_Rpc/common_macro.h"
#include "Imagine_Rpc/RpcMethodHandler.h"
#include "Imagine_Rpc/common_definition.h"
#include "Imagine_Rpc/InternalMessage.pb.h"
#include "Imagine_Rpc/RpcZooKeeperBuilder.h"

namespace Imagine_Rpc
{
namespace Internal
{

void InternalService::GenerateNormalRespoonseInformation(const InternalMessage* request, InternalMessage* response)
{
    response->set_send_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_ZooKeeper);
    response->set_recv_identity_(request->send_identity_());
    response->set_service_name_(request->service_name_());
    response->set_method_name_(request->method_name_());
    response->set_request_type_(Internal::InternalMessage_Request::InternalMessage_Request_Response);
}

Status InternalService::InternalMessageProcessor(Context* context, InternalMessage* request, InternalMessage* response)
{
    if (request->recv_identity_() != InternalMessage_Identity::InternalMessage_Identity_ZooKeeper) {
        throw std::exception();
    }
    GenerateNormalRespoonseInformation(request, response);
    switch (request->send_identity_())
    {
        case InternalMessage_Identity::InternalMessage_Identity_Client :
            return InternalClientMessageProcessor(context, request, response);
            break;
            
        case InternalMessage_Identity::InternalMessage_Identity_Server :
            return InternalServerMessageProcessor(context, request, response);
            break;

        default:
            IMAGINE_RPC_LOG_INFO("Bad Request!");
            throw std::exception();
            break;
    }

    return Status::OK;
}

Status InternalService::InternalClientMessageProcessor(Context* context, InternalMessage* request, InternalMessage* response)
{
    // std::shared_ptr<RpcWatcher> new_watcher = std::make_shared<RpcWatcher>(context->send_ip_(), context->send_port_());
    std::pair<std::string, std::string> stat;
    switch (request->request_type_())
    {
        case InternalMessage_Request::InternalMessage_Request_Search :
            stat = builder_->SearchMethod(RpcUtil::GenerateRegisterName(request->service_name_(), request->method_name_())); // 暂时未用watcher
            // stat = builder_->SearchMethod(RpcUtil::GenerateRegisterName(request->service_name_(), request->method_name_()), new_watcher);
            response->set_server_ip_(stat.first);
            response->set_server_port_(stat.second);
            break;
        
        default :
            IMAGINE_RPC_LOG_INFO("NO Function Named %s is Found!", request->method_name_());
            throw std::exception();
            break;
    }

    return Status::OK;
}

Status InternalService::InternalServerMessageProcessor(Context* context, InternalMessage* request, InternalMessage* response)
{
    switch (request->request_type_())
    {
        case InternalMessage_Request::InternalMessage_Request_Register :
            if (builder_->Register(RpcUtil::GenerateRegisterName(request->service_name_(), request->method_name_()), request->server_ip_(), request->server_port_(), context->sockfd_())) {
                // 注册成功
                IMAGINE_RPC_LOG_INFO("%s:%s Register Success!", context->send_ip_().c_str(), context->send_port_().c_str());
            } else {
                // 注册失败
                IMAGINE_RPC_LOG_INFO("%s:%s Register Fail!", context->send_ip_().c_str(), context->send_port_().c_str());
            }
            break;
        
        case InternalMessage_Request::InternalMessage_Request_DeRegister :
            if (builder_->DeRegister(RpcUtil::GenerateRegisterName(request->service_name_(), request->method_name_()), context->send_ip_(), context->send_port_(), context->sockfd_())) {
                // 注销成功
                IMAGINE_RPC_LOG_INFO("%s:%s DeRegister Success!", context->send_ip_().c_str(), context->send_port_().c_str());
            } else {
                // 注销失败
                IMAGINE_RPC_LOG_INFO("%s:%s DeRegister Fail!", context->send_ip_().c_str(), context->send_port_().c_str());
            }
            break;
        
        case InternalMessage_Request::InternalMessage_Request_Heartbeat :
            if (builder_->HeartBeatProcessor(context->sockfd_())) {
                IMAGINE_RPC_LOG_INFO("%s:%s HeartBeat Success!", context->send_ip_().c_str(), context->send_port_().c_str());
            } else {
                IMAGINE_RPC_LOG_INFO("Bad HeartBeat Request!");
                throw std::exception();
            }
            break;
        
        default:
            IMAGINE_RPC_LOG_INFO("%s:%s Bad Request!", context->send_ip_().c_str(), context->send_port_().c_str());
            break;
    }

    return Status::OK;
}

InternalService::InternalService(RpcZooKeeperBuilder* builder) : Service(INTERNAL_ZOOKEEPER_SERVICE_NAME), builder_(builder)
{
    RegisterMethods({INTERNAL_ZOOKEEPER_METHOD_NAME}, {new RpcMethodHandler<Internal::InternalMessage, Internal::InternalMessage>(std::bind(&InternalService::InternalMessageProcessor, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))});
}

InternalService::~InternalService()
{
}

} // namespace Internal
} // namespace Imagine_Rpc