#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodParseEndState();

 public:
    void Init() override;

 public:
    bool ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif