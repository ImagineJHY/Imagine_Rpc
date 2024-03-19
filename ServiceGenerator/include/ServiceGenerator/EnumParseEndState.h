#ifndef IMAGINE_RPC_SERVICEGENERATOR_ENUMPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_ENUMPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class EnumParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    EnumParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~EnumParseEndState();

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