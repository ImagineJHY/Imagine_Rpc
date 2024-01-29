#ifndef IMAGINE_RPC_SERVICEGENERATOR_SYNTAXSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_SYNTAXSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class SyntaxState : public ServiceGeneratorStateMachineState
{
 public:
    SyntaxState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~SyntaxState();

 public:
    void Init() override;

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    bool is_parsed_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif