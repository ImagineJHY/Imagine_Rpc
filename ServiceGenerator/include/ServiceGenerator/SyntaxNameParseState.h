#ifndef IMAGINE_RPC_SERVICEGENERATOR_SYNTAXNAMEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_SYNTAXNAMEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class SyntaxNameParseState : public ServiceGeneratorStateMachineState
{
 public:
    SyntaxNameParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~SyntaxNameParseState();

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