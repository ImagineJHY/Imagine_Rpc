#include "ServiceGenerator/RpcServiceMethodResponseTypeParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/RpcServiceMethodState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceMethodResponseTypeParseState::RpcServiceMethodResponseTypeParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(RPCSERVICE_METHOD_RESPONSE_TYPE_PARSE_STATE_NAME, parent_state, sm)
{
}

RpcServiceMethodResponseTypeParseState::~RpcServiceMethodResponseTypeParseState()
{
}

void RpcServiceMethodResponseTypeParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&RpcServiceMethodResponseTypeParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(RPCSERVICE_METHOD_TYPE_PARSE_END_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool RpcServiceMethodResponseTypeParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    std::string response_msg = sm->GetContent();
    if (sm->IsCXXKeyWord(response_msg)) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    // TODO : 这里没有判断是否是enum类型
    if (!sm->IsCustomKeyWord(response_msg)) {
        sm->AddUndefinedKeyWord("", response_msg);
    }

    RpcServiceMethodState* rpc_service_state = dynamic_cast<RpcServiceMethodState*>(parent_state_);
    if (rpc_service_state == nullptr) {
        throw std::exception();
    }
    rpc_service_state->SetResponseMessage(response_msg);

    return true;
}

StateMachineState* RpcServiceMethodResponseTypeParseState::onEnter()
{
    return this;
}

StateMachineState* RpcServiceMethodResponseTypeParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator


} // namespace Imagine_Rp

