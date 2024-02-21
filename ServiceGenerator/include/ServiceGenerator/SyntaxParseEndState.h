#ifndef IMAGINE_RPC_SERVICEGENERATOR_SYNTAXPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_SYNTAXPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class SyntaxParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    SyntaxParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~SyntaxParseEndState();

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