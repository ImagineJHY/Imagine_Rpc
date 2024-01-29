#ifndef IMAGINE_RPC_SERVICEGENERATOR_IMPORTSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_IMPORTSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ImportState : public ServiceGeneratorStateMachineState
{
 public:
    ImportState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~ImportState();

 public:
    void Init() override;

 public:
    bool ParseImportFile(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif