#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODNAMEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODNAMEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodNameParseState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodNameParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodNameParseState();

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