#ifndef IMAGINE_RPC_SERVICEGENERATOR_IMPORTPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_IMPORTPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ImportParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    ImportParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~ImportParseEndState();

 public:
    void Init() override;

 public:
    bool ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif