#include "Imagine_Rpc/RpcWatcher.h"

namespace Imagine_Rpc
{

RpcWatcher::RpcWatcher(const std::string& ip, const std::string& port) : ip_(ip), port_(port)
{
}

RpcWatcher::~RpcWatcher()
{
}

void RpcWatcher::Update(const std::string &send_content)
{

    if (send_content == "offline")
    {
        std::vector<std::string> parameters;
        // RpcClient::Call(send_,parameters,ip,port);
    }
}

} // namespace Imagine_Rpc