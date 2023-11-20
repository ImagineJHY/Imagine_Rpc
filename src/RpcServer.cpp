#include "Imagine_Rpc/RpcServer.h"

#include "Imagine_Rpc/RpcServerBuilder.h"

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

RpcServer* const RpcServer::Start()
{
    builder_->Start();
}

RpcServer* const RpcServer::RegisterService(Service* service)
{
    if (builder_) {
        builder_->RegisterService(service);
    }

    return this;
}

RpcServer* const RpcServer::DeregisterService(Service* service)
{
    if (builder_) {
        builder_->DeregisterService(service);
    }

    return this;
}

} // namespace Imagine_Rpc