#ifndef IMAGINE_RPC_INTERNALSERVICE_H
#define IMAGINE_RPC_INTERNALSERVICE_H

#include "common_definition.h"
#include "Service.h"
#include "InternalMessage.pb.h"

namespace Imagine_Rpc
{

class RpcZooKeeperBuilder;
class Context;

namespace Internal
{

class InternalService : public Service
{
 public:
   InternalService(RpcZooKeeperBuilder* builder);

   ~InternalService();

   void GenerateNormalRespoonseInformation(const InternalMessage* request, InternalMessage* response);

   Status InternalMessageProcessor(Context* context, InternalMessage* request, InternalMessage* response);

   Status InternalClientMessageProcessor(Context* context, InternalMessage* request, InternalMessage* response);

   Status InternalServerMessageProcessor(Context* context, InternalMessage* request, InternalMessage* response);

 private:
   RpcZooKeeperBuilder* builder_;
};

} // namespace Internal
} // namespace Imagine_Rpc

#endif