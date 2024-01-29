#ifndef IMAGINE_RPC_SERVICEGENERATOR_IMPORTPATHPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_IMPORTPATHPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ImportPathParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    ImportPathParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~ImportPathParseEndState();

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