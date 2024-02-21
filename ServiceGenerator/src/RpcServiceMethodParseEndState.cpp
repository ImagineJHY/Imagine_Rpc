#include "ServiceGenerator/RpcServiceMethodParseEndState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/RpcServiceMethodState.h"
#include "ServiceGenerator/RpcServiceNameParseState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceMethodParseEndState::RpcServiceMethodParseEndState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(RPCSERVICE_METHOD_PARSE_END_STATE_NAME, parent_state, sm)
{
}

RpcServiceMethodParseEndState::~RpcServiceMethodParseEndState()
{
}

void RpcServiceMethodParseEndState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, this, std::bind(&RpcServiceMethodParseEndState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool RpcServiceMethodParseEndState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != ";") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    RpcServiceMethodState* method_state = dynamic_cast<RpcServiceMethodState*>(parent_state_);
    RpcServiceNameParseState* rpc_service_name_parse_state = dynamic_cast<RpcServiceNameParseState*>(sm_->GetStatePtr(RPCSERVICE_NAME_PARSE_STATE_NAME));
    if (method_state == nullptr || rpc_service_name_parse_state == nullptr) {
        throw std::exception();
    }
    sm->AddMethod(rpc_service_name_parse_state->GetServiceName(), method_state->GetMethodName(), method_state->GetRequestMessage(), method_state->GetResponseMessage());

    sm_->EventExecute(RPCSERVICE_METHOD_PARSE_COMPLETE_EVENT_NAME);

    return true;
}

StateMachineState* RpcServiceMethodParseEndState::onEnter()
{
    return this;
}

StateMachineState* RpcServiceMethodParseEndState::onExit()
{
    return this;
}

} // namespace ServiceGenerator


} // namespace Imagine_Rp

