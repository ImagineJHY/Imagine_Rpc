#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODTYPEPARSEBEGINSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODTYPEPARSEBEGINSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodTypeParseBeginState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodTypeParseBeginState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodTypeParseBeginState();

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