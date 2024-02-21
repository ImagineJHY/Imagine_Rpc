#include "ServiceGenerator/SyntaxParseEndState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

SyntaxParseEndState::SyntaxParseEndState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(SYNTAX_PARSE_END_STATE_NAME, parent_state, sm)
{
}

SyntaxParseEndState::~SyntaxParseEndState()
{
}

void SyntaxParseEndState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, this, std::bind(&SyntaxParseEndState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool SyntaxParseEndState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() == "\"") {
        return true;
    } else if (sm->GetContent() == ";") {
        sm_->EventExecute(SYNTAX_PARSE_COMPLETE_EVENT_NAME);

        return true;
    } else {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);
    }

    return false;
}

StateMachineState* SyntaxParseEndState::onEnter()
{
    return this;
}

StateMachineState* SyntaxParseEndState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
