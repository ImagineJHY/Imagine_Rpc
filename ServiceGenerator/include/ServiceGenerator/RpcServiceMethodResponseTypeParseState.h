#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODRESPONSETYPEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODRESPONSETYPEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodResponseTypeParseState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodResponseTypeParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodResponseTypeParseState();

 public:
    void Init() override;

 public:
    bool ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif