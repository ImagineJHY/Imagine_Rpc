#ifndef IMAGINE_RPC_RPCZOOKEEPERSERVER_H
#define IMAGINE_RPC_RPCZOOKEEPERSERVER_H

#include <list>
#include <string>
#include <unordered_map>

namespace Imagine_Rpc
{

class Builder;

class RpcZooKeeperServer
{
 public:
    RpcZooKeeperServer();

    RpcZooKeeperServer(Builder* builder);

    ~RpcZooKeeperServer();

    void Init();

 private:
    Builder* builder_;
};

} // namespace Imagine_Rpc

#endif