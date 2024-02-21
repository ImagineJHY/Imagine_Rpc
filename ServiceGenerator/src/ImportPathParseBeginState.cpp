#include "ServiceGenerator/ImportPathParseBeginState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

ImportPathParseBeginState::ImportPathParseBeginState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(IMPORT_PATH_PARSE_BEGIN_STATE_NAME, parent_state, sm)
{
}

ImportPathParseBeginState::~ImportPathParseBeginState()
{
}

void ImportPathParseBeginState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&ImportPathParseBeginState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(IMPORT_PATH_PARSE_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool ImportPathParseBeginState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
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

StateMachineState* ImportPathParseBeginState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("this is %s\n", GetStateName().c_str());
    return this;
}

StateMachineState* ImportPathParseBeginState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
