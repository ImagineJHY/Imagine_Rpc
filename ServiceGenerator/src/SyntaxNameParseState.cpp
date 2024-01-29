#include "ServiceGenerator/SyntaxNameParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

SyntaxNameParseState::SyntaxNameParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(SYNTAX_NAME_PARSE_STATE_NAME, parent_state, sm)
{
}

SyntaxNameParseState::~SyntaxNameParseState()
{
}

void SyntaxNameParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&SyntaxNameParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(SYNTAX_PARSE_END_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool SyntaxNameParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != "proto3" && sm->GetContent() != "proto2") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    sm->SetSyntax(sm->GetContent());

    return true;
}

StateMachineState* SyntaxNameParseState::onEnter()
{
    return this;
}

StateMachineState* SyntaxNameParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
