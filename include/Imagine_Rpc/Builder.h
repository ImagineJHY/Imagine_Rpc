#ifndef IMAGINE_RPC_BUILDER_H
#define IMAGINE_RPC_BUILDER_H

#include "Service.h"
#include "TransportDecoder.h"

#include <unordered_map>

namespace Imagine_Rpc
{

// as interface
class Builder
{
 public:
    Builder();

    virtual ~Builder();

    Builder* const RegisterService(Service* service);

    Builder* const DeregisterService(std::string service_name);

    const ServiceDescriptor* FindServiceDescriptor(std::string service_name);

 private:
    std::unordered_map<std::string, const ServiceDescriptor*> service_map_;
    std::mutex service_map_lock_;
};

} // namespace Imagine_Rpc

#endif