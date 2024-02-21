#include "ServiceGenerator/EnumParseEndState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/EnumState.h"
#include "ServiceGenerator/NameParseState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

EnumParseEndState::EnumParseEndState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(ENUM_PARSE_END_STATE_NAME, parent_state, sm)
{
}

EnumParseEndState::~EnumParseEndState()
{
}

void EnumParseEndState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&EnumParseEndState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), this, std::bind(&EnumParseEndState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ENUM_FIELD_NAME_PARSE_STATE_NAME), std::bind(&EnumParseEndState::ParseFieldCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    this->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool EnumParseEndState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
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

bool EnumParseEndState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() == ";") {
        return true;
    }
    EnumState* enum_state = dynamic_cast<EnumState*>(parent_state_);
    NameParseState* enum_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(ENUM_NAME_PARSE_STATE_NAME));
    if (enum_state == nullptr || enum_name_parse_state == nullptr) {
        throw std::exception();
    }
    if (enum_state->GetPreName().size() != 0) {
        sm_->EventExecute(ENUM_PARSE_COMPLETE_TRANSITION_TO_MESSAGE_EVENT_NAME);
    } else {
        sm_->EventExecute(ENUM_PARSE_COMPLETE_TRANSITION_TO_ROOT_EVENT_NAME);
    }
    enum_state->SetPreName("");
    enum_name_parse_state->SetName("");

    return true;
}

bool EnumParseEndState::ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    sm_->EventExecute(PARSE_FIELD_EVENT_NAME);

    return true;
}

StateMachineState* EnumParseEndState::onEnter()
{
    return this;
}

StateMachineState* EnumParseEndState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
