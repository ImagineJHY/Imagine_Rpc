#ifndef IMAGINE_RPC_SERVICEGENERATOR_FIELDSYMBOLPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_FIELDSYMBOLPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class FieldSymbolParseState : public ServiceGeneratorStateMachineState
{
 public:
    FieldSymbolParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~FieldSymbolParseState();
   
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