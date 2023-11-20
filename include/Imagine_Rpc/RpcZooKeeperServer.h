#ifndef IMAGINE_RPC_RPCZOOKEEPERSERVER_H
#define IMAGINE_RPC_RPCZOOKEEPERSERVER_H

#include "Imagine_Muduo/EventLoop.h"
#include "Imagine_ZooKeeper/ZooKeeperServer.h"
#include "Imagine_Rpc/common_definition.h"
#include "Imagine_Rpc/RpcUtil.h"
#include "ServiceDescriptor.h"
#include "InternalService.h"
#include "Builder.h"

#include <unordered_map>
#include <string>
#include <list>

namespace Imagine_Rpc
{

class RpcZooKeeperServer
{
 public:
    RpcZooKeeperServer();

    RpcZooKeeperServer(Builder* builder);

    ~RpcZooKeeperServer() {}

    void Init();

 private:
    Builder* builder_;
};

} // namespace Imagine_Rpc

#endif