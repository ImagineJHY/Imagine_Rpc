#ifndef IMAGINE_RPC_BUILDER_H
#define IMAGINE_RPC_BUILDER_H

#include <mutex>
#include <unordered_map>

namespace Imagine_Rpc
{

class Service;
class ServiceDescriptor;

// as interface
class Builder
{
 public:
    Builder();

    virtual ~Builder();

    Builder* RegisterService(const Service* service);

    Builder* DeregisterService(const std::string& service_name);

    const ServiceDescriptor* FindServiceDescriptor(const std::string& service_name) const;

 private:
    std::unordered_map<std::string, const ServiceDescriptor*> service_map_;
    std::mutex service_map_lock_;
};

} // namespace Imagine_Rpc

#endif