#ifndef IMAGINE_RPC_SERVICEGENERATOR_MESSAGEPARSEPRESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_MESSAGEPARSEPRESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class MessageParsePreState : public ServiceGeneratorStateMachineState
{
 public:
    MessageParsePreState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~MessageParsePreState();

 public:
    void Init() override;

 public:
    bool ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);
    
    bool ClassifyTaskCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ClassifyTaskCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif