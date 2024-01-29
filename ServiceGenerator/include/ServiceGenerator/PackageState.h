#ifndef IMAGINE_RPC_SERVICEGENERATOR_PACKAGESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_PACKAGESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class PackageState : public ServiceGeneratorStateMachineState
{
 public:
    PackageState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~PackageState();

 public:
    void Init() override;
    
 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    bool is_parsed_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif