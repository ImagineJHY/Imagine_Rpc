#ifndef IMAGINE_RPC_SERVICEGENERATOR_IMPORTPATHPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_IMPORTPATHPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ImportPathParseState : public ServiceGeneratorStateMachineState
{
 public:
    ImportPathParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~ImportPathParseState();

    void ResetPath();

    std::string GetPath() const;

 public:
    void Init() override;

 public:
    bool ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

    bool ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    std::string path_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif