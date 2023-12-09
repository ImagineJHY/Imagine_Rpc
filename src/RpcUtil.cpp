#include "Imagine_Rpc/RpcUtil.h"

#include "Imagine_Rpc/InternalMessage.pb.h"
#include "Imagine_Rpc/Context.pb.h"
#include "Imagine_Rpc/TransportDecoder.h"
#include "Imagine_Rpc/MessageHeader.h"

#include <unistd.h>
#include <errno.h>

namespace Imagine_Rpc
{

const double RpcUtil::default_delay_ = 2.0;

std::string RpcUtil::IntToString(size_t input)
{
    std::string temp_output;
    std::string output;

    if (!input) {
        return "0";
    }
    while (input) {
        temp_output.push_back(input % 10 + '0');
        input /= 10;
    }

    for (int i = temp_output.size() - 1; i >= 0; i--) {
        output.push_back(temp_output[i]);
    }

    return output;
}

int RpcUtil::StringToInt(const std::string &input)
{
    int output = 0;
    int size = input.size();
    for (int i = 0; i < size; i++) {
        output = output * 10 + input[i] - '0';
    }

    return output;
}

struct sockaddr_in RpcUtil::PackIpPort(const std::string &ip, const std::string &port)
{
    struct sockaddr_in addr;

    int ret = inet_pton(AF_INET, &ip[0], &addr.sin_addr.s_addr);
    if (ret != 1) {
        throw std::exception();
    }

    addr.sin_port = htons(atoi(&port[0]));
    addr.sin_family = AF_INET;

    return addr;
}

std::string RpcUtil::Communicate(const std::string& send_content, const std::string& ip, const std::string& port, bool wait_recv)
{
    return Communicate(send_content, PackIpPort(ip, port), wait_recv);
}

std::string RpcUtil::Communicate(const std::string &send_content, struct sockaddr_in addr, bool wait_recv)
{
    int ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        throw std::exception();
    }

    int sockfd = ret;
    SetSocketOpt(sockfd);
    ret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret == -1) {
        throw std::exception();
    }

    write(sockfd, &send_content[0], send_content.size());
    std::string recv_;

    if (!wait_recv) {
        close(sockfd);
        return "";
    }

    ret = 1024;
    while (ret == 1024) {
        char buffer[1024];
        ret = read(sockfd, buffer, sizeof(buffer)); // Zookeeper返回函数IP+PORT,用\r\n分隔
        if (ret == 0) {
            LOG_INFO("111 Connection Close! errno is %d", errno);
            close(sockfd);
            return "";
        }
        for (int i = 0; i < ret; i++) {
            recv_.push_back(buffer[i]);
        }
    }

    close(sockfd);

    return recv_;
}

std::string RpcUtil::Communicate(const std::string &send_content, int *sockfd, ConnectionStatus& conn_status, bool wait_recv)
{
    int ret = write(*sockfd, &send_content[0], send_content.size());
    LOG_INFO("Send Content %s to peer, ret is %d", send_content.c_str(), ret);
    if (ret == -1) {
        LOG_INFO("Communnicate write exception!");
        throw std::exception();
    }
    conn_status = ConnectionStatus::Ok;
    std::string recv_content;
    if (!wait_recv) {
        return "";
    }

    ret = 1024;
    while (ret == 1024) {
        char buffer[1024];

        ret = read(*sockfd, buffer, sizeof(buffer));
        if (ret == 0) {
            LOG_INFO("222 Connection Close! errno is %d", errno);
            conn_status = ConnectionStatus::Close;
            return "";
        }
        if (ret == -1) {
            switch (errno)
            {
            case 104 :
                LOG_INFO("Server Is busy, Please Try Again!");
                conn_status = ConnectionStatus::Again;
                return "";
                break;
            
            default:
                LOG_INFO("Ret Is -1, ERRNO Is %d, Please Add Code To Process it!", errno);
                throw std::exception();
                break;
            }
        }
        for (int i = 0; i < ret; i++) {
            recv_content.push_back(buffer[i]);
        }
        if (ret == -1) {
            LOG_INFO("ret is -1, ERRORNO is %d, send content is %s", errno, send_content.c_str());
        }
        LOG_INFO("Recv Content %s to peer, content size is %d", recv_content.c_str(), ret);
    }

    return recv_content;
}

bool RpcUtil::Connect(const std::string &ip, const std::string &port, int *sockfd)
{
    struct sockaddr_in addr = PackIpPort(ip, port);
    int ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        return false;
        throw std::exception();
    }

    *sockfd = ret;
    SetSocketOpt(*sockfd);

    ret = connect(*sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
        return false;
        throw std::exception();
    }

    LOG_INFO("connection success!");

    return true;
}

std::string RpcUtil::ConvertIpFromNetToString(const unsigned int net_ip)
{
    char char_ip[15];
    std::string string_ip;
    inet_ntop(AF_INET, &net_ip, char_ip, sizeof(char_ip));
    for (int i = 0; i < 15; i++) {
        if (char_ip[i] == '\0') {
            break;
        }
        string_ip.push_back(char_ip[i]);
    }

    return string_ip;
}

std::string RpcUtil::ConvertPortFromNetToString(const unsigned short int net_port)
{
    return IntToString(ntohs(net_port));
}

unsigned int RpcUtil::ConvertIpFromStringToNet(const std::string &string_ip)
{
    struct in_addr net_ip;

    if (inet_pton(AF_INET, &string_ip[0], (void *)&net_ip) != 1) {
        throw std::exception();
    }

    return net_ip.s_addr;
}

unsigned short int RpcUtil::ConvertPortFromStringToNet(const std::string &string_port)
{
    return htons(StringToInt(string_port));
}

void RpcUtil::SetSocketOpt(int sockfd)
{
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)); // 设置端口复用
}

bool RpcUtil::Connect(const Context* context, int* sockfd)
{
    struct sockaddr_in addr = PackIpPort(context->recv_ip_(), context->recv_port_());
    int ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        return false;
        throw std::exception();
    }

    *sockfd = ret;
    SetSocketOpt(*sockfd);

    ret = connect(*sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
        return false;
        throw std::exception();
    }

    LOG_INFO("connection success!");

    return true;
}

std::string RpcUtil::Readfd(const int* sockfd, ConnectionStatus& conn_status)
{
    std::string recv_content;
    int ret = 1024;
    
    conn_status = ConnectionStatus::Ok;
    while(ret != 1024) {
        char buf[1024];
        int ret = read(*sockfd, buf, 1024);
        if (ret == 0) {
            LOG_INFO("222 Connection Close! errno is %d", errno);
            conn_status = ConnectionStatus::Close;
            return "";
        }
        for(int i = 0; i < ret; i++) {
            recv_content.push_back(buf[i]);
        }
    }

    return recv_content;
}

std::string RpcUtil::GenerateRegisterName(const std::string& service_name, const std::string& method_name)
{
    return "/" + service_name + "/" + method_name;
}

void RpcUtil::SendMessage(const Context* request_context, const RpcMessage* request_msg, Context* response_context, RpcMessage* response_msg, int sockfd)
{
    std::string send_content;
    std::string recv_content;
    ConnectionStatus conn_status = ConnectionStatus::Again;
    SerializeMessage(request_context, request_msg, send_content);
    while (conn_status == ConnectionStatus::Again) {
        recv_content = Communicate(send_content, &sockfd, conn_status);
    }
    while(!DeserializeMessage(recv_content, response_context, response_msg)) {
        if (conn_status == ConnectionStatus::Close) {
            LOG_INFO("Connection Close");
            return;
        }
        LOG_INFO("Deserialize Recv Message Fail, Read Again!");
        recv_content += Readfd(&sockfd, conn_status);
    }
}

void RpcUtil::SendMessage(const Context* request_context, const RpcMessage* request_msg, Context* response_context, RpcMessage* response_msg)
{
    std::string send_content;
    SerializeMessage(request_context, request_msg, send_content);
    DeserializeMessage(Communicate(send_content, request_context->recv_ip_(), request_context->recv_port_()), response_context, response_msg);
}

void RpcUtil::SerializeMessage(const Context* context, const RpcMessage* msg, std::string& content)
{
    MessageHeader header(context->ByteSize(), msg->ByteSize());
    if (!header.AppendToString(content)) {
        LOG_INFO("Serialize Header Error");
    }
    if (!context->AppendToString(&content)) {
        LOG_INFO("Serialize Context Error");
    }
    if (!msg->AppendPartialToString(&content)) {
        LOG_INFO("Serialize Message Error");
    }
}

bool DeserializeMessage(const char* buf, size_t buf_size, Context* context, RpcMessage* msg)
{
    size_t header_size = 0;
    if (!TransportDecoder::ContextDecoder(buf, buf_size, context, &header_size)) {
        return false;
    }
    if (!TransportDecoder::MessageDecoder(buf + header_size + context->ByteSize(), buf_size - header_size - context->ByteSize(), msg)) {
        return false;
    }

    return true;
}

bool RpcUtil::DeserializeMessage(const std::string& content, Context* context, RpcMessage* msg)
{
    size_t header_size = 0;
    if (!TransportDecoder::ContextDecoder(content.c_str(), content.size(), context, &header_size)) {
        return false;
    }
    if (!TransportDecoder::MessageDecoder(content.c_str() + header_size + context->ByteSize(), content.size() - header_size - context->ByteSize(), msg)) {
        return false;
    }

    return true;
}

void RpcUtil::GenerateRegisterMessage(Context* context, Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& zookeeper_ip, const std::string& zookeeper_port, const std::string& server_ip, const std::string& server_port)
{
    GenerateRegisterContent(request_msg, service_name, method_name, server_ip, server_port);
    GenerateRegisterContext(context, request_msg, zookeeper_ip, zookeeper_port);
}

void RpcUtil::GenerateRegisterContent(Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& server_ip, const std::string& server_port)
{
    request_msg->set_send_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_Server);
    request_msg->set_recv_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_ZooKeeper);
    request_msg->set_service_name_(service_name);
    request_msg->set_method_name_(method_name);
    request_msg->set_server_ip_(server_ip);
    request_msg->set_server_port_(server_port);
    request_msg->set_request_type_(Internal::InternalMessage_Request::InternalMessage_Request_Register);
}

void RpcUtil::GenerateRegisterContext(Context* context, const Internal::InternalMessage* const request_msg, const std::string& zookeeper_ip, const std::string& zookeeper_port)
{
    context->set_message_size_(request_msg->ByteSize());
    context->set_service_name_(INTERNAL_REGISTER_SERVICE_NAME);
    context->set_method_name_(INTERNAL_REGISTER_METHOD_NAME);
    context->set_send_ip_("0.0.0.0");
    context->set_send_port_("0");
    context->set_recv_ip_(zookeeper_ip);
    context->set_recv_port_(zookeeper_port);
    context->set_sockfd_(0);
}

void RpcUtil::GenerateDeregisterMessage(Context* context, Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& server_ip, const std::string& server_port)
{
    GenerateDeregisterContent(request_msg, service_name, method_name, server_ip, server_port);
    GenerateDeregisterContext(context, request_msg, service_name, method_name);
}

void RpcUtil::GenerateDeregisterContent(Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& server_ip, const std::string& server_port)
{
    request_msg->set_send_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_Server);
    request_msg->set_recv_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_ZooKeeper);
    request_msg->set_service_name_(service_name);
    request_msg->set_method_name_(method_name);
    request_msg->set_server_ip_(server_ip);
    request_msg->set_server_port_(server_port);
    request_msg->set_request_type_(Internal::InternalMessage_Request::InternalMessage_Request_DeRegister);
}

void RpcUtil::GenerateDeregisterContext(Context* context, const Internal::InternalMessage* const request_msg, const std::string& service_name, const std::string& method_name)
{
    context->set_message_size_(request_msg->ByteSize());
    context->set_service_name_(service_name);
    context->set_method_name_(method_name);
}

void RpcUtil::GenerateCallServerContext(Context* context, const RpcMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& server_ip, const std::string& server_port)
{
    context->set_message_size_(request_msg->ByteSize());
    context->set_service_name_(service_name);
    context->set_method_name_(method_name);
    context->set_send_ip_("0.0.0.0");
    context->set_send_port_("0");
    context->set_recv_ip_(server_ip);
    context->set_recv_port_(server_port);
    context->set_sockfd_(0);
}

void RpcUtil::GenerateCallZooKeeperMessage(Context* context, Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name, const std::string& zookeeper_ip, const std::string& zookeeper_port)
{
    GenerateCallZooKeeperContent(request_msg, service_name, method_name);
    GenerateCallZooKeeperContext(context, request_msg, zookeeper_ip, zookeeper_port);
}

void RpcUtil::GenerateCallZooKeeperContext(Context* context, Internal::InternalMessage* request_msg, const std::string& zookeeper_ip, const std::string& zookeeper_port)
{
    context->set_message_size_(request_msg->ByteSize());
    context->set_service_name_(INTERNAL_ZOOKEEPER_SERVICE_NAME);
    context->set_method_name_(INTERNAL_ZOOKEEPER_METHOD_NAME);
    context->set_send_ip_("0.0.0.0");
    context->set_send_port_("0");
    context->set_recv_ip_(zookeeper_ip);
    context->set_recv_port_(zookeeper_port);
    context->set_sockfd_(0);
}

void RpcUtil::GenerateCallZooKeeperContent(Internal::InternalMessage* request_msg, const std::string& service_name, const std::string& method_name)
{
    request_msg->set_send_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_Client);
    request_msg->set_recv_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_ZooKeeper);
    request_msg->set_service_name_(service_name);
    request_msg->set_method_name_(method_name);
    request_msg->set_request_type_(Internal::InternalMessage_Request::InternalMessage_Request_Search);
}

void RpcUtil::GenerateHeartBeatPacketMessage(Context* context, Internal::InternalMessage* request_msg)
{
    GenerateHeartBeatPacketContent(request_msg);
    GenerateHeartBeatPacketContext(context, request_msg);
}

void RpcUtil::GenerateHeartBeatPacketContext(Context* context, const Internal::InternalMessage* request_msg)
{
    context->set_message_size_(request_msg->ByteSize());
    context->set_service_name_(INTERNAL_ZOOKEEPER_SERVICE_NAME);
    context->set_method_name_(INTERNAL_ZOOKEEPER_METHOD_NAME);
    context->set_send_ip_("0.0.0.0");
    context->set_send_port_("0");
    context->set_recv_ip_("0.0.0.0");
    context->set_recv_port_("0");
    context->set_sockfd_(0);
}

void RpcUtil::GenerateHeartBeatPacketContent(Internal::InternalMessage* request_msg)
{
    request_msg->set_send_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_Server);
    request_msg->set_recv_identity_(Internal::InternalMessage_Identity::InternalMessage_Identity_ZooKeeper);
    request_msg->set_request_type_(Internal::InternalMessage_Request::InternalMessage_Request_Heartbeat);
}

} // namespace Imagine_Rpc