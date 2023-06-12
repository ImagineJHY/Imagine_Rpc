# Readme

## 简介

Imagine_Rpc对RPC功能进行了实现，并整合了ZooKeeper模块提供服务的发现和注册，主要功能有：

- RpcServer可以向RpcZooKeeper注册函数方法
- 多个RpcServer可通过RpcZooKeeper实现负载均衡
- RpcClient可通过RpcZooKeeper获取服务，也可直接访问RpcServer获取服务

## 快速上手

- 使用说明

  - RpcServer端

    添加头文件RpcServer.h，使用namespace Imagine_Rpc即可快速使用

  - RpcClient端

    添加头文件RpcClient.h，使用namespace Imagine_Rpc即可快速使用

  - RpcZooKeeper端

    若需要第三方提供服务注册和发现功能，添加头文件RpcZooKeeper.h，使用namespace Imagine_Rpc即可快速使用

- 操作系统：Linux

- 依赖：

  - Imagine_ZooKeeper
  - Imagine_Muduo
  - Linux下线程库pthread

- 启动：

  - RpcServer端

    将调用函数注册到本地或RpcZooKeeper后，使用RpcServer::loop()即可自动运转

  - RpcClient端

    - 方式一：使用RpcClient::Caller()在RpcZooKeeper上发现服务并自动调用获取返回
    - 方式二：使用RpcClient::Call()直接访问RpcServer
    - 方式三：
      - 使用RpcClient::CallerOne()从RpcZooKeeper上获取服务器地址
      - 使用RpcClient::ConnectServer()与获取的服务器建立连接
      - 使用RpcClient::Call()进行保持连接的调用


## 说明

- RpcServer相关接口

  ```cpp
  //构造函数
  RpcServer::RpcServer(const std::string& ip_, const std::string& port_, const std::string& keeper_ip_="", const std::string& keeper_port_="", int max_client_num=10000);
  /*
  -参数
  	-ip_:服务器Server的Ip
  	-port:你想要服务器运行的端口
  	-keeper_ip:服务器zookeeper的IP
  	-keeper_port:服务器zookeeper的port
  	-max_client_num:服务器能够接收的最大连接数
  注:框架中还提供了另一个RpcServer的构造函数，可以直接把要注册的函数传进去，此处不介绍
  */
  
  //注册函数,若没有设置zookeeper则只在本地注册
  void RpcServer::Callee(const std::string& method, RpcCallback callback);
  /*
  -参数:
  	-method:函数方法名
  	-callback:回调函数指针(必须是RpcCallback类型)
  */
  ```

- RpcClient相关接口

  ```cpp
  //静态方法,在zookeeper服务器发现服务并调用返回,通信完成后不保持连接
  std::vector<std::string> RpcClient::Caller(const std::string& method, const std::vector<std::string>& parameters, const std::string& ip_, const std::string& port_);
  /*
  -参数
  	-method:要调用的方法名
  	-parameters:参数(无参传空vector)
  	-ip_:服务器zookeeper的ip
  	-port_:服务器zookeeper的port
  -返回值
  	-函数返回值
  */
  
  //静态方法,直接访问RpcClient,通信完成后不保持连接
  std::vector<std::string> RpcClient::Call(const std::string& method, const std::vector<std::string>& parameters, const std::string& ip_, const std::string& port_);
  /*
  -参数
  	-method:要调用的方法名
  	-parameters:参数(无参传空vector)
  	-ip_:服务器Server的ip
  	-port_:服务器Server的port
  -返回值
  	-函数返回值
  */
  
  //静态方法,从RpcZooKeeper获取一个服务器地址但不进行自动调用
  bool RpcClient::CallerOne(const std::string& method, const std::string& keeper_ip, const std::string& keeper_port, std::string& server_ip, std::string& server_port);
  /*
  -参数
  	-method:要调用的方法名
  	-keeper_ip:服务器zookeeper的ip
  	-keeper_port:服务器zookeeper的port
  	-server_ip:传出参数,服务器Server的ip
  	-server_port:传出参数,服务器Server的port
  -返回值
  	-true:成功
  	-false:失败
  */
  
  //静态方法,与已经connect的Server进行通信
  std::vector<std::string> RpcClient::Call(const std::string& method, const std::vector<std::string>& parameters, int* sockfd);
  /*
  -参数
  	-method:要调用的方法名
  	-parameters:参数(无参传空vector)
  	-sockfd:与Server建立连接的socketfd
  -返回值
  	-函数返回值
  */
  
  //静态方法,用长连接的形式连接服务器
  bool RpcClient::ConnectServer(const std::string& ip_, const std::string& port_, int* sockfd);
  /*
  -参数
  	-ip_:服务器Server的ip
  	-port_:服务器Server的port
  	-sockfd:传出参数,用于保存与Server通信的socketfd
  -返回值
  	-true:成功
  	-false:失败
  */
  ```

- RpcZooKeeper相关接口

  ```cpp
  //构造函数
  RpcZooKeeper::RpcZooKeeper(const std::string& ip_, const std::string& port_, double time_out_=120.0, int max_request_num=10000);
  /*
  -参数
  	-ip_:服务器zookeeper的ip
  	-port_:你想要服务器运行的端口
  	-time_out_:服务器Server与zookeeper的心跳保活时间(time_out_时间内必须收到心跳包保活)
  	-max_request_num:服务器zookeeper允许的最大连接数
  */
  ```

  