#include "Imagine_Rpc/Builder.h"

#include "Imagine_Rpc/Service.h"
#include "Imagine_Rpc/log_macro.h"
#include "Imagine_Rpc/ServiceDescriptor.h"

namespace Imagine_Rpc
{

Builder::Builder()
{
}
    
Builder::~Builder()
{
}

Builder* Builder::RegisterService(const Service* service)
{
    const ServiceDescriptor* service_descriptor = service->GetServiceDescriptor();
    std::unique_lock<std::mutex> lock(service_map_lock_);
    service_map_.insert(std::make_pair(service_descriptor->GetServiceName(), service_descriptor));

    return this;
}

Builder* Builder::DeregisterService(const std::string& service_name)
{
    std::unique_lock<std::mutex> lock(service_map_lock_);
    if (service_map_.find(service_name) == service_map_.end()) {
        IMAGINE_RPC_LOG_INFO("NO SERVICE NAMED %s is Registetered!", service_name.c_str());
    }
    service_map_.erase(service_map_.find(service_name));

    return this;
}

const ServiceDescriptor* Builder::FindServiceDescriptor(const std::string& service_name) const
{
    auto it = service_map_.find(service_name);
    if (it == service_map_.end()) {
        return nullptr;
    }

    return it->second;
}

} // namespace Imagine_Rpc