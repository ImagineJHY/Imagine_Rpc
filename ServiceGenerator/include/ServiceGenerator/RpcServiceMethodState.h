#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodState();

    void SetMethodName(const std::string& method_name);

    void SetRequestMessage(const std::string& request_msg);

    void SetResponseMessage(const std::string& response_msg);

    std::string GetMethodName() const;

    std::string GetRequestMessage() const;

    std::string GetResponseMessage() const;

 public:
    void Init() override;

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    std::string method_name_;
    std::string request_msg_;
    std::string response_msg_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif