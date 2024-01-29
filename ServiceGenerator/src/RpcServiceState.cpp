#include "ServiceGenerator/RpcServiceState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/RpcServiceMethodState.h"
#include "ServiceGenerator/RpcServiceParseEndState.h"
#include "ServiceGenerator/RpcServiceNameParseState.h"
#include "ServiceGenerator/RpcServiceParseBeginState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceState::RpcServiceState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(RPCSERVICE_STATE_NAME, parent_state, sm)
{
    this->AddSubState(new RpcServiceNameParseState(this, sm_))->AddSubState(new RpcServiceParseBeginState(this, sm_))->AddSubState(new RpcServiceMethodState(this, sm_))->AddSubState(new RpcServiceParseEndState(this, sm_));
}

RpcServiceState::~RpcServiceState()
{
}

void RpcServiceState::Init()
{
    this->SetDefaultSubState(sm_->GetStatePtr(RPCSERVICE_NAME_PARSE_STATE_NAME));
    this->RegisterTransitionEventCallback(RPCSERVICE_METHOD_PARSE_COMPLETE_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelTwoPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(RPCSERVICE_PARSE_END_STATE_NAME), nullptr);
}

StateMachineState* RpcServiceState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("this is %s\n", GetStateName().c_str());
    return this;
}

StateMachineState* RpcServiceState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
