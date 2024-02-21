#ifndef IMAGINE_RPC_SERVICEGENERATOR_FIELDNAMEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_FIELDNAMEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class FieldNameParseState : public ServiceGeneratorStateMachineState
{
 public:
    FieldNameParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~FieldNameParseState();

 public:
    void Init() override;

 public:
    bool ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    std::string field_name_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif