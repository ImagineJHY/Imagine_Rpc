#ifndef IMAGINE_RPC_SERVICEGENERATOR_ROOTSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_ROOTSTATE_H

#include "ServiceGeneratorStateMachineState.h"

#include <functional>

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class RootState : public ServiceGeneratorStateMachineState
{
 public:
    RootState(StateMachine* sm = nullptr);

    ~RootState();
 
 public:
    void Init() override;

 public:
    bool ClassifyTaskCondition(StateMachineState* src, StateMachineEvent evt);

    bool ClassifyTaskActor(StateMachineState* src, StateMachineEvent evt);

    bool ParseSyntaxCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParsePackageCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseMessageCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseRpcServiceCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseEnumCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseImportCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool TransitionToRootCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif