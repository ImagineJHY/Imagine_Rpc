#include "ServiceGenerator/ImportPathParseEndState.h"
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

ImportPathParseEndState::ImportPathParseEndState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(IMPORT_PATH_PARSE_END_STATE_NAME, parent_state, sm)
{
}

ImportPathParseEndState::~ImportPathParseEndState()
{
}

void ImportPathParseEndState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&ImportPathParseEndState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(IMPORT_PARSE_END_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool ImportPathParseEndState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }

    if (sm->GetContent() != "\"") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

StateMachineState* ImportPathParseEndState::onEnter()
{
    return this;
}

StateMachineState* ImportPathParseEndState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
