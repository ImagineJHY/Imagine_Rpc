#ifndef IMAGINE_RPC_SERVICEGENERATOR_PACKAGEPARSEENDRSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_PACKAGEPARSEENDRSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class PackageParseEndState : public ServiceGeneratorStateMachineState
{
 public:
    PackageParseEndState(StateMachineState* const parent_state, StateMachine* sm = nullptr);
    ~PackageParseEndState();

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