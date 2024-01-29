#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODREQUESTTYPEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODREQUESTTYPEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodRequestTypeParseState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodRequestTypeParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodRequestTypeParseState();

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