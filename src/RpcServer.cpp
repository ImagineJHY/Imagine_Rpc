#include "Imagine_Rpc/RpcServer.h"

#include <sys/uio.h>
#include <cstdarg>

namespace Imagine_Rpc
{

RpcServer::RpcServer()
{
    if (pthread_mutex_init(&callback_lock_, nullptr) != 0) {
        throw std::exception();
    }

    if (pthread_mutex_init(&heart_map_lock_, nullptr) != 0) {
        throw std::exception();
    }

    loop_ = new Imagine_Muduo::EventLoop();
}

RpcServer::RpcServer(std::string profile_name)
{
    Init(profile_name);

    if (pthread_mutex_init(&callback_lock_, nullptr) != 0) {
        throw std::exception();
    }

    if (pthread_mutex_init(&heart_map_lock_, nullptr) != 0) {
        throw std::exception();
    }

    loop_ = new Imagine_Muduo::EventLoop(muduo_profile_name_);
}

RpcServer::RpcServer(const std::string &ip, const std::string &port, const std::string &keeper_ip, const std::string &keeper_port, int max_client_num)
                     : ip_(ip), port_(port), rpc_zookeeper_ip_(keeper_ip), rpc_zookeeper_port_(keeper_port)
{
    int temp_port = Rpc::StringToInt(port_);
    if (temp_port < 0) {
        throw std::exception();
    }

    if (pthread_mutex_init(&callback_lock_, nullptr) != 0) {
        throw std::exception();
    }

    if (pthread_mutex_init(&heart_map_lock_, nullptr) != 0) {
        throw std::exception();
    }

    SetDefaultCallback();

    loop_ = new Imagine_Muduo::EventLoop(temp_port, 5, max_client_num, read_callback_, write_callback_, communicate_callback_);
}

RpcServer::RpcServer(const std::string &ip, const std::string &port, std::unordered_map<std::string, RpcCallback> callbacks, const std::string &keeper_ip, const std::string &keeper_port, int max_client_num)
                     : ip_(ip), port_(port), rpc_zookeeper_ip_(keeper_ip), rpc_zookeeper_port_(keeper_port)
{
    int temp_port = Rpc::StringToInt(port_);
    if (temp_port <= 0) {
        throw std::exception();
    }

    if (pthread_mutex_init(&callback_lock_, nullptr) != 0) {
        throw std::exception();
    }

    // 设置本机IP+PORT(均用字符串进行表示和传输)
    // port = htons(port_);
    //  port = Rpc::IntToString(port_);
    // inet_pton(AF_INET,"192.168.83.129",&ip);

    SetDefaultReadCallback();

    SetDefaultWriteCallback();

    SetDefaultCommunicateCallback();

    SetDefaultTimerCallback();

    loop_ = new EventLoop(temp_port, 5, max_client_num, read_callback_, write_callback_, communicate_callback_);

    callback_num_ = callbacks.size();
    pthread_mutex_lock(&callback_lock_);
    for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
        // Callee(it->first,it->second);
        callbacks_.insert(std::make_pair(it->first, it->second));
        // callbacks_.insert({it->first,it->second});
        if (rpc_zookeeper_ip_.size() && rpc_zookeeper_port_.size())
            Register(it->first, rpc_zookeeper_ip_, rpc_zookeeper_port_);
    }
    pthread_mutex_unlock(&callback_lock_);
    // register_loop_=new EventLoop(0,max_register_num,)
    // loop->loop();
}

RpcServer::~RpcServer()
{
    delete loop_;
}

void RpcServer::Init(std::string profile_name)
{
    if (profile_name == "") {
        throw std::exception();
    }

    YAML::Node config = YAML::LoadFile(profile_name);
    ip_ = config["ip"].as<std::string>();
    port_ = config["port"].as<std::string>();
    rpc_zookeeper_ip_ = config["zookeeper_ip"].as<std::string>();
    rpc_zookeeper_port_ = config["zookeeper_port"].as<std::string>();
    thread_num_ = config["thread_num"].as<size_t>();
    log_name_ = config["log_name"].as<std::string>();
    log_path_ = config["log_path"].as<std::string>();
    max_log_file_size_ = config["max_log_file_size"].as<size_t>();
    async_log_ = config["async_log"].as<bool>();
    singleton_log_mode_ = config["singleton_log_mode"].as<bool>();
    log_title_ = config["log_title"].as<std::string>();
    log_with_timestamp_ = config["log_with_timestamp"].as<bool>();

    if (singleton_log_mode_) {
        logger_ = Imagine_Tool::SingletonLogger::GetInstance();
    } else {
        logger_ = new Imagine_Tool::NonSingletonLogger();
        Imagine_Tool::Logger::SetInstance(logger_);
    }

    logger_->Init(config);

    InitProfilePath(profile_name);

    GenerateSubmoduleProfile(config);

    SetDefaultCallback();
}

void RpcServer::InitProfilePath(std::string profile_name)
{
    size_t idx = profile_name.find_last_of("/");
    profile_path_ = profile_name.substr(0, idx + 1);
    muduo_profile_name_ = profile_path_ + "generate_Muduo_profile.yaml";
}

void RpcServer::GenerateSubmoduleProfile(YAML::Node config)
{
    int fd = open(muduo_profile_name_.c_str(), O_RDWR | O_CREAT);
    config.remove(config["ip"]);
    config.remove(config["zookeeper_ip"]);
    config.remove(config["zookeeper_port"]);
    config["log_name"] = "imagine_muduo_log.log";
    write(fd, config.as<std::string>().c_str(), config.as<std::string>().size());
    close(fd);
}

bool RpcServer::SetKeeper(const std::string &keeper_ip, const std::string &keeper_port)
{
    rpc_zookeeper_ip_ = keeper_ip;
    rpc_zookeeper_port_ = keeper_port;

    return true;
}

void RpcServer::SetDefaultCallback()
{
    SetDefaultReadCallback();
    SetDefaultWriteCallback();
    SetDefaultCommunicateCallback();
    SetDefaultTimerCallback();
}

void RpcServer::SetDefaultReadCallback()
{
    read_callback_ = [this](const struct iovec *input_iovec)
    {
        LOG_INFO("this is RpcServer : %s", &(ip_ + port_)[0]);

        std::string input = Rpc::GetIovec(input_iovec);

        int sockfd = *(int *)input_iovec[0].iov_base;

        // 解析数据
        std::vector<std::string> de_input = Rpc::Deserialize(input, 0);

        std::string content = de_input[1] + "\r\n";

        // 搜索函数
        auto func = this->SearchFunc(de_input[1]);
        if (!func) {
            // 函数未找到
            struct iovec *output_iovec = Rpc::SetIovec(Rpc::GenerateDefaultFailureMessage(), 12, false);
            return output_iovec;
        }
        Rpc::Unpack(de_input);

        // 执行并输出
        content += Rpc::Serialize(func(de_input));

        std::string head = Rpc::GenerateDefaultHead(content);

        // 暂时默认保持连接
        UpdatetUser(sockfd);

        struct iovec *output_iovec = Rpc::SetIovec(head + content, head.size() + content.size());

        return output_iovec;
    };
    if (loop_) {
        loop_->SetWriteCallback(write_callback_);
    }
}

void RpcServer::SetDefaultWriteCallback()
{
    write_callback_ = [](const struct iovec *input_iovec)
    {
        std::string input = Rpc::GetIovec(input_iovec);
        struct iovec *output_iovec = Rpc::SetIovec(input, input.size());
        *((char *)output_iovec[0].iov_base + 4) = '1';
        *((char *)output_iovec[0].iov_base + 5) = '0';

        return output_iovec;
    };
    if (loop_) {
        loop_->SetWriteCallback(write_callback_);
    }
}

void RpcServer::SetDefaultCommunicateCallback()
{
    communicate_callback_ = Rpc::DefaultCommunicateCallback;
    if (loop_) {
        loop_->SetWriteCallback(write_callback_);
    }
}

void RpcServer::SetDefaultTimerCallback()
{
    timer_callback_ = [this](int sockfd, double time_out)
    {
        // printf("RpcServer TimerCallback!\n");

        long long last_request_time;
        if (!GetHeartNodeInfo(sockfd, last_request_time)) {
            return;
        }

        if (Imagine_Tool::TimeUtil::GetNow() > Imagine_Tool::TimeUtil::MicroSecondsAddSeconds(last_request_time, time_out)) {
            // 已过期
            LOG_INFO("RpcServer Timer Set offline!");
            this->loop_->Closefd(sockfd);
            this->DeleteUser(sockfd);
            return;
        } else {
            // 未过期,忽略
        }
    };
}

void RpcServer::SetDefaultTimeOutCallback()
{
    timeout_callback_ = [](void) -> void {

    };
}

RpcServerTimerCallback RpcServer::GetTimerCallback()
{
    return timer_callback_;
}

void RpcServer::loop()
{
    loop_->loop();
}

bool RpcServer::UpdatetUser(int sockfd)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<int, RpcSHeart *>::iterator it = heart_map_.find(sockfd);
    if (it == heart_map_.end()) {
        RpcSHeart *new_heart = new RpcSHeart(SetTimer(5.0, 0.0, std::bind(timer_callback_, sockfd, time_out_)));
        heart_map_.insert(std::make_pair(sockfd, new_heart));
    } else {
        it->second->ReSetLastRequestTime();
    }
    pthread_mutex_unlock(&heart_map_lock_);

    return true;
}

bool RpcServer::DeleteUser(int sockfd)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<int, RpcSHeart *>::iterator it = heart_map_.find(sockfd);
    if (it == heart_map_.end()) {
        return false; // 已删除
        throw std::exception();
    }
    RpcSHeart *heart_node = it->second;
    heart_map_.erase(it);
    RemoveTimer(heart_node->GetTimerfd());
    delete heart_node;
    pthread_mutex_unlock(&heart_map_lock_);

    return true;
}

void RpcServer::Callee(const std::string &method, RpcCallback callback)
{ // 服务器注册函数
    pthread_mutex_lock(&callback_lock_);
    if (rpc_zookeeper_ip_.size() && rpc_zookeeper_port_.size()) {
        Register(method, rpc_zookeeper_ip_, rpc_zookeeper_port_); // 在服务器上注册name:ip_port
    }
    callbacks_.insert(std::make_pair(method, callback));
    pthread_mutex_unlock(&callback_lock_);
}

bool RpcServer::Register(const std::string &method, const std::string &keeper_ip, const std::string &keeper_port)
{
    // struct sockaddr_in addr = Rpc::PackIpPort(keeper_ip, keeper_port);
    // struct sockaddr_in addr=Rpc::PackIpPort(keeper_ip,keeper_port);
    std::string content = GenerateDefaultRpcKeeperContent("Register", method);
    std::string head = Rpc::GenerateDefaultHead(content);
    int sockfd;
    while (1) {
        if (Rpc::Connect(keeper_ip, keeper_port, &sockfd)) {
            if (Rpc::Deserialize(Rpc::Communicate(head + content, &sockfd))[1] == "Success") {
                LOG_INFO("Server %s Register Success!", &(ip_ + port_)[0]);
                Rpc::DefaultKeepAliveClient(loop_, std::bind(&Rpc::DefaultClientTimerCallback, sockfd, method, nullptr));

                return true;
            } else {
                close(sockfd);
            }
        }
        LOG_INFO("Register unsuccess!try again after 5 second!");
        sleep(5);
    }

    LOG_INFO("Register exception!");
    throw std::exception();

    return false;
}

bool RpcServer::DeRegister(const std::string &method, const std::string &keeper_ip, const std::string &keeper_port)
{
    struct sockaddr_in addr = Rpc::PackIpPort(keeper_ip, keeper_port);
    // struct sockaddr_in addr=Rpc::PackIpPort(keeper_ip,keeper_port);

    std::string content = GenerateDefaultRpcKeeperContent("DeRegister", method);
    std::string head = Rpc::GenerateDefaultHead(content);
    if (Rpc::Deserialize(Rpc::Communicate(head + content, &addr, true), 0)[1] == "Success") {
        LOG_INFO("Server %s Deregister Success!", &(ip_ + port_)[0]);
        return true;
    }

    LOG_INFO("DeRegister exception!");
    throw std::exception();

    return false;
}

std::string RpcServer::GenerateDefaultRpcKeeperContent(const std::string &option, const std::string &method)
{
    return "RpcServer\r\n" + option + "\r\n" + method + "\r\n" + ip_ + "\r\n" + port_ + "\r\n";
}

RpcCallback RpcServer::SearchFunc(std::string method)
{
    pthread_mutex_lock(&callback_lock_);
    auto it = callbacks_.find(method);
    if (it == callbacks_.end()) {
        // 没找到
        LOG_INFO("SearchFunc exception!");
        throw std::exception();
    }
    auto callback = it->second;
    pthread_mutex_unlock(&callback_lock_);

    return callback;
}

long long RpcServer::SetTimer(double interval, double delay, RpcTimerCallback callback)
{
    return loop_->SetTimer(callback, interval, delay);
}

bool RpcServer::RemoveTimer(long long timerfd)
{
    return loop_->CloseTimer(timerfd);
}

bool RpcServer::GetHeartNodeInfo(int sockfd, long long &last_request_time)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<int, RpcSHeart *>::iterator it = heart_map_.find(sockfd);
    if (it == heart_map_.end()) {
        // 已删除
        pthread_mutex_unlock(&heart_map_lock_);
        return false;
    }
    last_request_time = it->second->GetLastRequestTime();
    pthread_mutex_unlock(&heart_map_lock_);

    return true;
}

long long RpcServer::GetHeartNodeLastRequestTime(int sockfd)
{
    pthread_mutex_lock(&heart_map_lock_);
    std::unordered_map<int, RpcSHeart *>::iterator it = heart_map_.find(sockfd);
    if (it == heart_map_.end()) {
        // 已删除
        pthread_mutex_unlock(&heart_map_lock_);
        return -1;
    }
    long long last_request_time = it->second->GetLastRequestTime();
    pthread_mutex_unlock(&heart_map_lock_);

    return last_request_time;
}

} // namespace Imagine_Rpc