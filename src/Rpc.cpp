#include "Imagine_Rpc/Rpc.h"

#include <unistd.h>
#include <errno.h>

using namespace Imagine_Rpc;

const double Rpc::default_delay_ = 2.0;

std::string Rpc::Serialize(const std::vector<std::string> &input)
{
    int size = input.size();
    // if(size==1&&input[0]=="\r\n")return "0\r\n";

    std::string output;

    for (int i = 0; i < size; i++) {
        if (!(input[i].size())) {
            continue;
        }
        for (size_t j = 0; j < input[i].size(); j++) {
            if (0 < j && input[i][j] == '\n' && input[i][j - 1] == '\r') {
                output += "\n\r";
            }
            output.push_back(input[i][j]);
        }
        output += "\r\n";
    }

    return output;
}

std::vector<std::string> Rpc::Deserialize(const std::string &input, int num)
{
    /*
        -num用于表示应当接收的最少的字段数
            -num为0表示不作检查
    */
    // int idx = 0;
    int size = input.size();
    std::vector<std::string> output;

    // if(size<=2||input[size-2]!='\r'||input[size-1]!='\n'){
    //     //一定发生了粘包
    //     output.push_back("\r\n");
    //     return output;
    // }
    std::string temp_string;
    for (int i = 0; i < size; i++) {
        if (input[i] == '\r' && input[i + 1] == '\n') {
            if (i + 3 < size && input[i + 2] == '\r' && input[i + 3] == '\n') {
                temp_string += "\r\n";
                i = i + 3;
            } else {
                output.push_back(temp_string);
                temp_string.clear();
                i = i + 1;
            }
        } else {
            temp_string.push_back(input[i]);
        }
    }

    if (num && !IsComplete(output, num)) {
        // 字段不足,粘包
        output.clear();
        output.push_back("\r\n");
        return output;
    }

    return output;
}

std::string Rpc::IntToString(int input)
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

int Rpc::StringToInt(const std::string &input)
{
    int output = 0;
    int size = input.size();
    for (int i = 0; i < size; i++) {
        output = output * 10 + input[i] - '0';
    }

    return output;
}

bool Rpc::IsComplete(const std::vector<std::string> &output, int num)
{
    if (output.size() < static_cast<size_t>(num)) {
        return false;
    }

    return true;
}

struct sockaddr_in Rpc::PackIpPort(const std::string &ip, const std::string &port)
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

std::string Rpc::Communicate(const std::string &send_content, const struct sockaddr_in *addr, bool wait_recv)
{
    int ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        throw std::exception();
    }

    int sockfd = ret;
    SetSocketOpt(sockfd);

    ret = connect(sockfd, (struct sockaddr *)addr, sizeof(*addr));
    if (ret == -1) {
        throw std::exception();
    }

    write(sockfd, &send_content[0], send_content.size());
    std::string recv_;

    if (!wait_recv) {
        close(sockfd);
        return "";
    }

    while (1) {
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
        if (DefaultCommunicateCallback(buffer, ret)) {
            break;
        }
    }

    close(sockfd);

    return recv_;
}

std::string Rpc::Communicate(const std::string &send_content, int *sockfd, bool wait_recv)
{
    int ret = write(*sockfd, &send_content[0], send_content.size());
    if (ret == -1) {
        LOG_INFO("Communnicate write exception!");
        throw std::exception();
    }
    std::string recv_content;
    if (!wait_recv) {
        return "";
    }

    while (1) {
        char buffer[1024];

        ret = read(*sockfd, buffer, sizeof(buffer)); // Zookeeper返回函数IP+PORT,用\r\n分隔
        if (ret == 0) {
            LOG_INFO("222 Connection Close! errno is %d", errno);
            return "";
        }
        for (int i = 0; i < ret; i++) {
            recv_content.push_back(buffer[i]);
        }
        if (DefaultCommunicateCallback(buffer, ret)) {
            break;
        }
    }

    return recv_content;
}

bool Rpc::Connect(const std::string &ip, const std::string &port, int *sockfd)
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

bool Rpc::Unpack(std::vector<std::string> &message)
{
    // for(int i=0;i<message.size();i++)printf("UnPack : %s\n",&message[i][0]);
    if (message.size() < 2) {
        // printf("%s\n",&message[0][0]);
        LOG_INFO("Unpack exception!");
        throw std::exception();
    }
    message.erase(message.begin(), message.begin() + 2);

    return true;
}

struct sockaddr_in *Rpc::GetAddr(const struct iovec *input_iovec)
{
    return (struct sockaddr_in *)input_iovec[1].iov_base;
}

std::string Rpc::GetIovec(const struct iovec *input_iovec)
{
    int len = input_iovec[0].iov_len;
    int num = 0;
    std::string input;

    // output_iovec[0].iov_len=2;
    // output_iovec[0].iov_base=new char[2];
    for (int i = 2; i < len; i++) {
        num += input_iovec[i].iov_len;
    }
    input.resize(num);
    num = 0;

    // 获取input_iovec的全部数据
    for (int i = 2; i < len; i++) {
        int temp_len = input_iovec[i].iov_len;
        for (int j = 0; j < temp_len; j++) {
            input[num++] = *((char *)(input_iovec[i].iov_base) + j);
            // printf("%c",input[num-1]);
        }
    }
    // printf("\n");

    return input;
}

struct iovec *Rpc::SetIovec(const std::string &input, int len, bool keep_alive, bool read_all)
{
    struct iovec *output_iovec = new struct iovec[2];
    char *control_char = new char[6];

    for (int i = 0; i < 6; i++) {
        control_char[i] = '1';
    }
    if (!keep_alive) {
        control_char[2] = '0'; // 不需要保持连接,其它标志位没有用
    } else {
        if (read_all) {
            control_char[3] = '0';
            control_char[4] = '0';
        } else {
            control_char[5] = '0';
        }
    }
    output_iovec[0].iov_len = 2;
    output_iovec[0].iov_base = control_char;
    output_iovec[1].iov_len = len;
    output_iovec[1].iov_base = new char[len];

    for (int i = 0; i < len; i++) {
        *((char *)(output_iovec[1].iov_base) + i) = input[i];
    }

    return output_iovec;
}

bool Rpc::IsComplete(const std::string &recv_content)
{
    int size = recv_content.size();
    for (int i = 0; i < size; i++) {
        if (i + 1 < size && recv_content[i] == '\r' && recv_content[i + 1] == '\n') {
            return Rpc::StringToInt(recv_content.substr(0, i)) == size ? true : false;
        }
    }

    return false;
}

bool Rpc::DefaultCommunicateCallback(const char *recv_content, int size)
{
    std::string recv_size;
    for (int i = 0; i < size; i++) {
        if (i + 1 < size && recv_content[i] == '\r' && recv_content[i + 1] == '\n') {
            return (Rpc::StringToInt(recv_size) + i + 2) == size ? true : false;
        }
        recv_size.push_back(recv_content[i]);
    }

    return false;
}

std::string Rpc::GenerateDefaultHead(const std::string &content)
{
    return Rpc::IntToString(content.size()) + "\r\n";
}

std::string Rpc::GenerateDefaultSuccessMessage()
{
    return "9\r\nSuccess\r\n";
}

std::string Rpc::GenerateDefaultFailureMessage()
{
    return "9\r\nFailure\r\n";
}

std::string Rpc::ConvertIpFromNetToString(const unsigned int net_ip)
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

std::string Rpc::ConvertPortFromNetToString(const unsigned short int net_port)
{
    return IntToString(ntohs(net_port));
}

unsigned int Rpc::ConvertIpFromStringToNet(const std::string &string_ip)
{
    struct in_addr net_ip;

    if (inet_pton(AF_INET, &string_ip[0], (void *)&net_ip) != 1) {
        throw std::exception();
    }

    return net_ip.s_addr;
}

unsigned short int Rpc::ConvertPortFromStringToNet(const std::string &string_port)
{
    return htons(StringToInt(string_port));
}

void Rpc::DefaultKeepAliveClient(EventLoop *loop, RpcTimerCallback timer_callback)
{
    loop->SetTimer(timer_callback, default_delay_);
}

void Rpc::DefaultClientTimerCallback(int sockfd, const std::string &name, RpcTimeOutCallback callback)
{
    std::string content = "RpcServer\r\n" + GenerateDefaultHeartbeatContent(name);
    std::string send_content = GenerateDefaultHead(content) + content;
    write(sockfd, &send_content[0], send_content.size());
    std::string recv_content;
    int ret;

    while (1) {
        char buffer[1024];
        ret = read(sockfd, buffer, sizeof(buffer)); // Zookeeper返回函数IP+PORT,用\r\n分隔
        if (ret == 0) {
            // 服务器已关闭连接
            LOG_INFO("333 Connection Close! errno is %d", errno);
            return;
        }
        for (int i = 0; i < ret; i++) {
            recv_content.push_back(buffer[i]);
        }
        if (DefaultCommunicateCallback(buffer, ret)) {
            break;
        }
    }
    if (recv_content == "9\r\nSuccess\r\n") {
        LOG_INFO("Heartbeat Success!");
    } else {
        LOG_INFO("recv is %s", &recv_content[0]);
        LOG_INFO("DefaultClientTimerCallback exception!");
        throw std::exception();
    }
}

std::string Rpc::GenerateDefaultHeartbeatContent(const std::string &name)
{
    return "online\r\n" + name + "\r\n";
}

void Rpc::SetSocketOpt(int sockfd)
{
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)); // 设置端口复用
}