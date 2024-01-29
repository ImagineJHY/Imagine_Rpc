#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEPARSEBEGINSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEPARSEBEGINSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceParseBeginState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceParseBeginState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceParseBeginState();

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