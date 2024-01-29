#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceParseEndState();

 public:
    void Init() override;

 public:
    bool ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif