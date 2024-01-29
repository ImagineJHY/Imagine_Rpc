#ifndef IMAGINE_RPC_SERVICEGENERATOR_MESSAGEFIELDATTRIBUTEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_MESSAGEFIELDATTRIBUTEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class MessageFieldAttributeParseState : public ServiceGeneratorStateMachineState
{
public:
    MessageFieldAttributeParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~MessageFieldAttributeParseState();

 public:
    void Init() override;

 public:
    bool ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif