#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODTYPEPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODTYPEPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodTypeParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodTypeParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodTypeParseEndState();

 public:
    void Init() override;

 public:
    bool ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif