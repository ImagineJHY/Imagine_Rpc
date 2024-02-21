#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RpcServiceState : public ServiceGeneratorStateMachineState
{
 public:
    RpcServiceState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~RpcServiceState();

 public:
    void Init() override;

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif