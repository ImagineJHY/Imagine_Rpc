#include "ServiceGenerator/ErrorState.h"

#include "ServiceGenerator/log_macro.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

ErrorState::ErrorState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(ERROR_STATE_NAME, parent_state, sm)
{
}

ErrorState::~ErrorState()
{
}

void ErrorState::Init()
{
}

StateMachineState* ErrorState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Error File!\n");
    throw std::exception();
    return this;
}

StateMachineState* ErrorState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
