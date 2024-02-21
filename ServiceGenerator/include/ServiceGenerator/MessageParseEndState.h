#ifndef IMAGINE_RPC_SERVICEGENERATOR_MESSAGEPARSEENDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_MESSAGEPARSEENDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class MessageParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    MessageParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~MessageParseEndState();

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