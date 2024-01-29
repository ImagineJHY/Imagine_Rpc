#ifndef IMAGINE_RPC_SERVICEGENERATOR_SYNTAXPARSEBEGINSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_SYNTAXPARSEBEGINSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class SyntaxParseBeginState : public ServiceGeneratorStateMachineState
{
 public:
    SyntaxParseBeginState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~SyntaxParseBeginState();

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