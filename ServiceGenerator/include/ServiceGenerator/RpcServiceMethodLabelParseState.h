#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODLABELPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICEMETHODLABELPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceMethodLabelParseState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceMethodLabelParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceMethodLabelParseState();

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