#include "ServiceGenerator/FieldSymbolParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

FieldSymbolParseState::FieldSymbolParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(parent_state->GetStateName() == MESSAGE_FIELD_STATE_NAME ? MESSAGE_FIELD_SYMBOL_PARSE_STATE_NAME : ENUM_FIELD_SYMBOL_PARSE_STATE_NAME, parent_state, sm)
{
}

FieldSymbolParseState::~FieldSymbolParseState()
{
}

void FieldSymbolParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&FieldSymbolParseState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(GetStateName() == MESSAGE_FIELD_SYMBOL_PARSE_STATE_NAME ? MESSAGE_FIELD_VALUE_PARSE_STATE_NAME : ENUM_FIELD_VALUE_PARSE_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool FieldSymbolParseState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != "=") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

StateMachineState* FieldSymbolParseState::onEnter()
{
    return this;
}

StateMachineState* FieldSymbolParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
