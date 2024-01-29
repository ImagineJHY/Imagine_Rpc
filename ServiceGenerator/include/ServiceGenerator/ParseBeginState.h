#ifndef IMAGINE_RPC_SERVICEGENERATOR_PARSEBEGINSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_PARSEBEGINSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ParseBeginState : public ServiceGeneratorStateMachineState
{
 public:
    ParseBeginState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~ParseBeginState();

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