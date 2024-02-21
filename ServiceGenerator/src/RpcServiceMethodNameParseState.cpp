#include "ServiceGenerator/RpcServiceMethodNameParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/RpcServiceNameParseState.h"
#include "ServiceGenerator/RpcServiceMethodState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceMethodNameParseState::RpcServiceMethodNameParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(RPCSERVICE_METHOD_NAME_PARSE_STATE_NAME, parent_state, sm)
{
}

RpcServiceMethodNameParseState::~RpcServiceMethodNameParseState()
{
}

void RpcServiceMethodNameParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&RpcServiceMethodNameParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(RPCSERVICE_METHOD_TYPE_PARSE_BEGIN_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool RpcServiceMethodNameParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    RpcServiceNameParseState* rpc_service_name_parse_state = static_cast<RpcServiceNameParseState*>(sm_->GetStatePtr(RPCSERVICE_NAME_PARSE_STATE_NAME));
    if (sm == nullptr || rpc_service_name_parse_state == nullptr) {
        return false;
    }
    std::string method_name = sm->GetContent();
    if (sm->IsCXXKeyWord(method_name) || rpc_service_name_parse_state->GetServiceName() == method_name) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    RpcServiceMethodState* rpc_service_state = dynamic_cast<RpcServiceMethodState*>(parent_state_);
    if (rpc_service_state == nullptr) {
        throw std::exception();
    }
    rpc_service_state->SetMethodName(method_name);

    return true;
}


StateMachineState* RpcServiceMethodNameParseState::onEnter()
{
    return this;
}

StateMachineState* RpcServiceMethodNameParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator


} // namespace Imagine_Rp

