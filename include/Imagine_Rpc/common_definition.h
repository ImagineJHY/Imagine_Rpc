#ifndef IMAGINE_RPC_COMMON_DEFINITION_H
#define IMAGINE_RPC_COMMON_DEFINITION_H

// 外部使用时需要用到的类型定义以及宏
#include "Service.h"
#include "RpcMethodHandler.h"

namespace Imagine_Rpc
{

#define REGISTER_MEMBER_FUNCTION(METHOD_NAME, REQUEST_MESSAGE_TYPE, RESPONSE_MESSAGE_TYPE, METHOD_FUNCTION_NAME) RegisterMethods({METHOD_NAME}, {new ::Imagine_Rpc::RpcMethodHandler<REQUEST_MESSAGE_TYPE, RESPONSE_MESSAGE_TYPE>(std::bind(METHOD_FUNCTION_NAME, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))})
#define REGISTER_STATIC_FUNCTION(METHOD_NAME, REQUEST_MESSAGE_TYPE, RESPONSE_MESSAGE_TYPE, METHOD_FUNCTION_NAME) RegisterMethods({METHOD_NAME}, {new ::Imagine_Rpc::RpcMethodHandler<REQUEST_MESSAGE_TYPE, RESPONSE_MESSAGE_TYPE>(std::bind(METHOD_FUNCTION_NAME, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))})

enum class Status
{
    OK,
    ERROR
};

} // namespace Imagine_Rpc

#endif