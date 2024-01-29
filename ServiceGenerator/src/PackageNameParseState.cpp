#include "ServiceGenerator/PackageNameParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

PackageNameParseState::PackageNameParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(PACKAGE_NAME_PARSE_STATE_NAME, parent_state, sm)
{
}

PackageNameParseState::~PackageNameParseState()
{
}

void PackageNameParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&PackageNameParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(PACKAGE_PARSE_END_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool PackageNameParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->IsCXXKeyWord(sm->GetContent())) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    if (sm->GetPackageName().size() != 0) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    sm->SetPackageName(sm->GetContent());

    return true;
}

StateMachineState* PackageNameParseState::onEnter()
{
    return this;
}

StateMachineState* PackageNameParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
