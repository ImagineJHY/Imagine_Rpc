#ifndef IMAGINE_RPC_SERVICEGENERATOR_SERVICEGENERATORSTATEMACHINESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_SERVICEGENERATORSTATEMACHINESTATE_H

#include "common_typename.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ServiceGeneratorStateMachineState : public StateMachineState
{
 public:
    ServiceGeneratorStateMachineState(const std::string& state_name, StateMachineState* const parent_state = nullptr, StateMachine* sm = nullptr);

    ~ServiceGeneratorStateMachineState();

    virtual void Init() = 0;

    void InitAll();
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc

#endif