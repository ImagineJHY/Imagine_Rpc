#ifndef IMAGINE_RPC_RPCWATCHER_H
#define IMAGINE_RPC_RPCWATCHER_H

#include "Imagine_ZooKeeper/Imagine_ZooKeeper.h"

#include <string>


namespace Imagine_Rpc
{

class RpcWatcher : public Imagine_ZooKeeper::Watcher
{

 public:
    RpcWatcher(const std::string& ip, const std::string& port);

    void Update(const std::string &send_content);

    ~RpcWatcher();

 private:
    std::string ip_;
    std::string port_;
};

} // namespace Imagine_Rpc

#endif