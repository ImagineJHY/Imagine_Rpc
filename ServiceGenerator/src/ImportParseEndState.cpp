#include "ServiceGenerator/ImportParseEndState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/FieldState.h"
#include "ServiceGenerator/NameParseState.h"
#include "ServiceGenerator/ParseBeginState.h"
#include "ServiceGenerator/EnumParseEndState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

ImportParseEndState::ImportParseEndState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(IMPORT_PARSE_END_STATE_NAME, parent_state, sm)
{
}

ImportParseEndState::~ImportParseEndState()
{
}

void ImportParseEndState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&ImportParseEndState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), this, std::bind(&ImportParseEndState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool ImportParseEndState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != ";") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

bool ImportParseEndState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    sm_->EventExecute(IMPORT_PARSE_COMPLETE_EVENT_NAME);

    return true;
}

StateMachineState* ImportParseEndState::onEnter()
{
    return this;
}

StateMachineState* ImportParseEndState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
