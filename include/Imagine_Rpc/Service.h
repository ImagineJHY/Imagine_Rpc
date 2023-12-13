#ifndef IMAGINE_RPC_SERVICE_H
#define IMAGINE_RPC_SERVICE_H

#include <string>
#include <vector>

namespace Imagine_Rpc
{

class MethodHandler;
class ServiceDescriptor;

class Service
{
 public:
    Service(const std::string& service_name);

    virtual ~Service();

    const ServiceDescriptor* GetServiceDescriptor() const;

    void RegisterMethods(const std::vector<std::string>& methods_name, const std::vector<MethodHandler*>& handlers);

 private:
    // 约束Service的构造方式
    Service() = default;

    Service(const Service& service) = default;

    Service& operator=(const Service& service) = default;

 protected:
    ServiceDescriptor* service_descriptor_;
};

} // namespace Imagine_Rpc

#endif