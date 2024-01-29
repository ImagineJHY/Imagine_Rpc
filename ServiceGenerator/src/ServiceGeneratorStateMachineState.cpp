#include "ServiceGenerator/ServiceGeneratorStateMachineState.h"

#include "ServiceGenerator/log_macro.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

ServiceGeneratorStateMachineState::ServiceGeneratorStateMachineState(const std::string& state_name, StateMachineState* const parent_state, StateMachine* sm) : StateMachineState(state_name, parent_state, sm)
{
}

ServiceGeneratorStateMachineState::~ServiceGeneratorStateMachineState()
{
}

void ServiceGeneratorStateMachineState::InitAll()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Init %s\n", GetStateName().c_str());
    Init();
    for (auto subState_it = subState_map_.begin(); subState_it != subState_map_.end(); subState_it++) {
        auto subState = dynamic_cast<ServiceGeneratorStateMachineState*>(subState_it->second);
        if (subState == nullptr) {
            throw std::exception();
        }
        subState->InitAll();
    }
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
