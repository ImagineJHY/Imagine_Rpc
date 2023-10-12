#include"RpcWatcher.h"
#include"Rpc.h"
#include"RpcClient.h"

using namespace Imagine_Rpc;

RpcWatcher::RpcWatcher(std::string ip_, std::string port_):ip(ip_),port(port_){};

RpcWatcher::~RpcWatcher(){};

void RpcWatcher::Update(const std::string& send_){

    if(send_=="offline"){
        std::vector<std::string> parameters;
        // RpcClient::Call(send_,parameters,ip,port);
    }
}