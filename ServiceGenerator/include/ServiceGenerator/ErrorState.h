#ifndef IMAGINE_RPC_SERVICEGENERATOR_ERRORSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_ERRORSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ErrorState : public ServiceGeneratorStateMachineState
{
 public:
    ErrorState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~ErrorState();

 public:
    void Init() override;

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif