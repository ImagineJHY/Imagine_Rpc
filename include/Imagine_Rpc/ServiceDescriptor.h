#ifndef IMAGINE_RPC_SERVICEDESCRIPTOR_H
#define IMAGINE_RPC_SERVICEDESCRIPTOR_H

#include <string>
#include <unordered_map>

namespace Imagine_Rpc
{

class MethodHandler;

class ServiceDescriptor
{
 public:
    ServiceDescriptor();

    ServiceDescriptor(const std::string& service_name);

    ~ServiceDescriptor();

   std::string GetServiceName() const;

    const std::unordered_map<std::string, MethodHandler*>& GetMethodHandlers() const;

    void RegisterMethods(const std::string& method_name, MethodHandler* handler_);

    const MethodHandler* FindMethodHandler(const std::string& method_name) const;

 private:
    std::string service_name_;
    std::unordered_map<std::string, MethodHandler*> handler_map_;
};

} // namespace Imagine_Rpc

#endif