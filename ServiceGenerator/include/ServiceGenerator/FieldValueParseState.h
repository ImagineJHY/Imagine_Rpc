#ifndef IMAGINE_RPC_SERVICEGENERATOR_FIELDVALUEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_FIELDVALUEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class FieldValueParseState : public ServiceGeneratorStateMachineState
{
 public:
    FieldValueParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~FieldValueParseState();

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