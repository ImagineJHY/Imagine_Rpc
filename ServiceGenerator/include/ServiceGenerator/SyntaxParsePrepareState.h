#ifndef IMAGINE_RPC_SERVICEGENERATOR_SYNTAXPARSEPREPARESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_SYNTAXPARSEPREPARESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class SyntaxParsePrepareState : public ServiceGeneratorStateMachineState
{
 public:
    SyntaxParsePrepareState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~SyntaxParsePrepareState();

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