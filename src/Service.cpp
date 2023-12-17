#include "Imagine_Rpc/Service.h"

#include "Imagine_Rpc/ServiceDescriptor.h"

namespace Imagine_Rpc
{

Service::Service(const std::string& service_name) : service_descriptor_(new ServiceDescriptor(service_name))
{
}

Service::~Service()
{
    delete service_descriptor_;
}

const ServiceDescriptor* Service::GetServiceDescriptor() const
{
    return service_descriptor_;
}

void Service::RegisterMethods(const std::vector<std::string>& methods_name, const std::vector<MethodHandler*>& handlers)
{
    for(size_t i = 0; i < methods_name.size(); i++) {
        service_descriptor_->RegisterMethods(methods_name[i], handlers[i]);
    }
}

} // namespace Imagine_Rpc