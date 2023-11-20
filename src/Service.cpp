#include "Imagine_Rpc/Service.h"

namespace Imagine_Rpc
{

Service::Service()
{
}

Service::Service(const std::string& service_name) : service_descriptor_(new ServiceDescriptor(service_name))
{
}

Service::~Service()
{
}

const ServiceDescriptor* Service::GetServiceDescriptor() const
{
    return service_descriptor_;
}

void Service::RegisterMethods(std::vector<std::string>&& methods_name, std::vector<MethodHandler*>&& handlers)
{
    for(size_t i = 0; i < methods_name.size(); i++) {
        service_descriptor_->RegisterMethods(methods_name[i], handlers[i]);
    }
}

} // namespace Imagine_Rpc