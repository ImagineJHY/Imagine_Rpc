#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICENAMEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICENAMEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceNameParseState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceNameParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceNameParseState();

    std::string GetServiceName() const;

 public:
    void Init() override;

 public:
    bool ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    std::string service_name_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif