#ifndef IMAGINE_RPC_SERVICEGENERATOR_MESSAGEFIELDDATATYPEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_MESSAGEFIELDDATATYPEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class MessageFieldDataTypeParseState : public ServiceGeneratorStateMachineState
{
public:
    MessageFieldDataTypeParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~MessageFieldDataTypeParseState();

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