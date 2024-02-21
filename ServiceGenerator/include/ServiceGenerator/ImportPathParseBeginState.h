#ifndef IMAGINE_RPC_SERVICEGENERATOR_IMPORTPATHPARSEBEGINSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_IMPORTPATHPARSEBEGINSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ImportPathParseBeginState : public ServiceGeneratorStateMachineState
{
 public:
    ImportPathParseBeginState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~ImportPathParseBeginState();

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