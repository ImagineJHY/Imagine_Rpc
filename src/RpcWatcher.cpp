#include "RpcWatcher.h"
#include "Rpc.h"
#include "RpcClient.h"

using namespace Imagine_Rpc;

RpcWatcher::RpcWatcher(std::string ip, std::string port) : ip_(ip), port_(port) {};

RpcWatcher::~RpcWatcher() {};

void RpcWatcher::Update(const std::string &send_content)
{

    if (send_content == "offline")
    {
        std::vector<std::string> parameters;
        // RpcClient::Call(send_,parameters,ip,port);
    }
}