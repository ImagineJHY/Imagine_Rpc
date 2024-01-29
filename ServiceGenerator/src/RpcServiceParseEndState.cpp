#include "ServiceGenerator/RpcServiceParseEndState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceParseEndState::RpcServiceParseEndState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(RPCSERVICE_PARSE_END_STATE_NAME, parent_state, sm)
{
}

RpcServiceParseEndState::~RpcServiceParseEndState()
{
}

void RpcServiceParseEndState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&RpcServiceParseEndState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), this, std::bind(&RpcServiceParseEndState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(RPCSERVICE_METHOD_LABEL_PARSE_STATE_NAME), std::bind(&RpcServiceParseEndState::ParseFieldCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    this->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool RpcServiceParseEndState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != "}" && sm->GetContent() != ";") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);
        throw std::exception();

        return false;
    }

    return true;
}

bool RpcServiceParseEndState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() == ";") {
        return true;
    }
    sm_->EventExecute(RPCSERVICE_PARSE_COMPLETE_EVENT_NAME);

    return true;
}

bool RpcServiceParseEndState::ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    sm_->EventExecute(PARSE_FIELD_EVENT_NAME);

    return true;
}

StateMachineState* RpcServiceParseEndState::onEnter()
{
    return this;
}

StateMachineState* RpcServiceParseEndState::onExit()
{
    return this;
}

} // namespace ServiceGenerator


} // namespace Imagine_Rp

