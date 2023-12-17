#include "Imagine_Rpc/RpcServer.h"

#include "Imagine_Rpc/Service.h"
#include "Imagine_Rpc/log_macro.h"
#include "Imagine_Rpc/RpcServerBuilder.h"
#include "Imagine_Rpc/ServiceDescriptor.h"

namespace Imagine_Rpc
{

RpcServer::RpcServer()
{
}

RpcServer::RpcServer(RpcServerBuilder* builder) : builder_(builder)
{
}

RpcServer::RpcServer(const std::string& profile_name) : builder_(new RpcServerBuilder(profile_name))
{
}

RpcServer::RpcServer(const YAML::Node& config) : builder_(new RpcServerBuilder(config))
{
}

RpcServer::~RpcServer()
{
}

RpcServer* RpcServer::Start() const
{
    builder_->Start();
}

const RpcServer* RpcServer::RegisterService(Service* service) const
{
    if (builder_) {
        builder_->RegisterService(service);
        IMAGINE_RPC_LOG("Register Service %s Success!", service->GetServiceDescriptor()->GetServiceName().c_str());
    }

    return this;
}

RpcServer* RpcServer::DeregisterService(Service* service)
{
    if (builder_) {
        builder_->DeregisterService(service);
    }

    return this;
}

long long RpcServer::SetTimer(TimerCallback timer_callback, double interval, double delay)
{
    if (builder_) {
        return builder_->SetTimer(timer_callback, interval, delay);
    }

    return 0;
}

RpcServer* RpcServer::RemoveTimer(long long timerfd)
{
    if (builder_) {
        builder_->RemoveTimer(timerfd);
    }

    return this;
}

} // namespace Imagine_Rpc