#ifndef IMAGINE_RPC_SERVICE_H
#define IMAGINE_RPC_SERVICE_H

#include "common_definition.h"
#include "ServiceDescriptor.h"

#include <string>
#include <vector>

namespace Imagine_Rpc
{

class Service
{
 public:
    Service();

    Service(const std::string& service_name);

    virtual ~Service();

    const ServiceDescriptor* GetServiceDescriptor() const;

    void RegisterMethods(std::vector<std::string>&& methods_name, std::vector<MethodHandler*>&& handlers);

 protected:
    ServiceDescriptor* service_descriptor_;
};

} // namespace Imagine_Rpc

#endif