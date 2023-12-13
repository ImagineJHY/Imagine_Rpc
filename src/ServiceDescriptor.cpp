#include "Imagine_Rpc/ServiceDescriptor.h"

namespace Imagine_Rpc
{

ServiceDescriptor::ServiceDescriptor()
{
}

ServiceDescriptor::ServiceDescriptor(const std::string& service_name) : service_name_(service_name)
{
}

ServiceDescriptor::~ServiceDescriptor()
{
    for (auto it = handler_map_.begin(); it != handler_map_.end(); it++) {
        delete it->second;
    }
}

const std::string& ServiceDescriptor::GetServiceName() const
{
    return service_name_;
}

const std::unordered_map<std::string, MethodHandler*>& ServiceDescriptor::GetMethodHandlers() const
{
    return handler_map_;
}

void ServiceDescriptor::RegisterMethods(const std::string& method_name, MethodHandler* handler)
{
    handler_map_.insert(std::make_pair(method_name, handler));
}

const MethodHandler* ServiceDescriptor::FindMethodHandler(const std::string& method_name) const
{
    auto it = handler_map_.find(method_name);
    if (it == handler_map_.end()) {
        return nullptr;
    }

    return it->second;
}

} // namespace Imagine_Rpc