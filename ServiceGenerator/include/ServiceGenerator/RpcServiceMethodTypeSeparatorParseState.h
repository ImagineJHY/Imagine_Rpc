#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODTYPESEPARATORPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODTYPESEPARATORPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodTypeSeparatorParseState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodTypeSeparatorParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodTypeSeparatorParseState();

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