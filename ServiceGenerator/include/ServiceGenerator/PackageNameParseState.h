#ifndef IMAGINE_RPC_SERVICEGENERATOR_PACKAGENAMEPARSERSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_PACKAGENAMEPARSERSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class PackageNameParseState : public ServiceGeneratorStateMachineState
{
 public:
    PackageNameParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);
    ~PackageNameParseState();

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