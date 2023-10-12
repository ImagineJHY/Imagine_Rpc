#include"RpcClient.h"
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>

/*
用户提供函数名在Zookeeper上查找函数地址
*/

using namespace Imagine_Rpc;

RpcClient::RpcClient()
{
    //loop_=new EventLoop()
}

std::vector<std::string> RpcClient::Caller(const std::string& method, const std::vector<std::string>& parameters, const std::string& ip_, const std::string& port_)
{
    struct sockaddr_in addr=Rpc::PackIpPort(ip_,port_);

    std::string content=RpcClient::GenerateDefaultRpcKeeperContent(method);
    
    std::string head=Rpc::GenerateDefaultHead(content);

    std::string recv_=Rpc::Communicate(head+content,&addr,true);//得到ip和端口号

    std::vector<std::string> recv_addr=Rpc::Deserialize(recv_);
    if(recv_addr[1]=="Failure"){
        printf("没有找到函数!\n");
        throw std::exception();
    }

    return Call(method,parameters,recv_addr[1],recv_addr[2]);
}

/*
用户提供函数名,函数参数,函数IP+端口号进行通信
特别的,若没有参数,参数列表中放入"\r\n"
*/
std::vector<std::string> RpcClient::Call(const std::string& method, const std::vector<std::string>& parameters, const std::string& ip_, const std::string& port_)
{
    struct sockaddr_in addr=Rpc::PackIpPort(ip_,port_);

    std::string content=GenerateDefaultRpcServerContent(method,parameters);
    std::string head=Rpc::GenerateDefaultHead(content);

    std::vector<std::string> recv_=Rpc::Deserialize(Rpc::Communicate(head+content,&addr,true));
    // for(int i=0;i<recv_.size();i++)printf("%s\n",&recv_[i][0]);
    Rpc::Unpack(recv_);

    if(recv_.size())return recv_;
    else{
        std::vector<std::string> no_recv_;
        no_recv_.push_back("");
        return no_recv_;
    }
}

bool RpcClient::CallerOne(const std::string& method, const std::string& keeper_ip, const std::string& keeper_port, std::string& server_ip, std::string& server_port)
{
    struct sockaddr_in addr=Rpc::PackIpPort(keeper_ip,keeper_port);
    std::string content=RpcClient::GenerateDefaultRpcKeeperContent(method);
    std::string head=Rpc::GenerateDefaultHead(content);

    std::string recv_=Rpc::Communicate(head+content,&addr,true);//得到ip和端口号
    std::vector<std::string> recv_addr=Rpc::Deserialize(recv_);
    if(recv_addr[1]=="Failure"){
        printf("没有找到函数!\n");
        throw std::exception();
    }
    server_ip=recv_addr[1];
    server_port=recv_addr[2];

    return true;
}

std::vector<std::string> RpcClient::Call(const std::string& method, const std::vector<std::string>& parameters, int* sockfd)
{
    std::string content=GenerateDefaultRpcServerContent(method,parameters);
    std::string head=Rpc::GenerateDefaultHead(content);

    std::vector<std::string> recv_=Rpc::Deserialize(Rpc::Communicate(head+content,sockfd));
    if(!recv_.size())return recv_;//接收异常
    Rpc::Unpack(recv_);

    return recv_;
}

bool RpcClient::ConnectServer(const std::string& ip_, const std::string& port_, int* sockfd)
{
    return Rpc::Connect(ip_,port_,sockfd);
}

std::string RpcClient::GenerateDefaultRpcKeeperContent(const std::string& method){
    return "RpcClient\r\n"+method+"\r\n";
}

std::string RpcClient::GenerateDefaultRpcServerContent(const std::string& method, const std::vector<std::string>& parameters){
    
    std::string content=method+"\r\n";
    content+=Rpc::Serialize(parameters);
    // if(parameters.size()==1&&parameters[0]=="\r\n")return content;

    // for(int i=0;i<parameters.size();i++){
    //     content+=parameters[i]+"\r\n";
    // }

    return content;
}

RpcCommunicateCallback RpcClient::DefaultCommunicateCallback(){
    return Rpc::DefaultCommunicateCallback;
}