#ifndef IMAGINE_RPC_SERVICEGENERATOR_FIELDPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_FIELDPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class FieldParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    FieldParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~FieldParseEndState();
   
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