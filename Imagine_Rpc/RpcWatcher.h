#ifndef IMAGINE_RPC_RPCWATCHER_H
#define IMAGINE_RPC_RPCWATCHER_H

#include<Imagine_ZooKeeper/Imagine_ZooKeeper/Watcher.h>

#include<string>

using namespace Imagine_ZooKeeper;



namespace Imagine_Rpc{

class RpcWatcher : public Watcher{

public:

    RpcWatcher(std::string ip,std::string port);

    void Update(const std::string& send_);

    ~RpcWatcher();

private:
    std::string ip;
    std::string port;

};



}


#endif