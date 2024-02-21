#include "ServiceGenerator/RpcServiceMethodTypeParseBeginState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceMethodTypeParseBeginState::RpcServiceMethodTypeParseBeginState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(RPCSERVICE_METHOD_TYPE_PARSE_BEGIN_STATE_NAME, parent_state, sm)
{
}

RpcServiceMethodTypeParseBeginState::~RpcServiceMethodTypeParseBeginState()
{
}

void RpcServiceMethodTypeParseBeginState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&RpcServiceMethodTypeParseBeginState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(RPCSERVICE_METHOD_REQUEST_TYPE_PARSE_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool RpcServiceMethodTypeParseBeginState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != "<") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

StateMachineState* RpcServiceMethodTypeParseBeginState::onEnter()
{
    return this;
}

StateMachineState* RpcServiceMethodTypeParseBeginState::onExit()
{
    return this;
}

} // namespace ServiceGenerator


} // namespace Imagine_Rp

