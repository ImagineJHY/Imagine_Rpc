#include "ServiceGenerator/EnumState.h"
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

EnumState::EnumState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(ENUM_STATE_NAME, parent_state, sm), pre_name_("")
{
    this->AddSubState(new NameParseState(this, sm_))->AddSubState(new ParseBeginState(this, sm_))->AddSubState(new FieldState(this, sm_, false))->AddSubState(new EnumParseEndState(this, sm_));
}

EnumState::~EnumState()
{
}

void EnumState::Init()
{
    this->SetDefaultSubState(GetSubStatePtr(ENUM_NAME_PARSE_STATE_NAME));
    this->RegisterTransitionEventCallback(FIELD_PARSE_COMPLETE_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelTwoPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ENUM_PARSE_END_STATE_NAME), nullptr);
}

void EnumState::SetPreName(const std::string& pre_name)
{
    pre_name_ = pre_name;
}

std::string EnumState::GetPreName() const
{
    return pre_name_;
}

StateMachineState* EnumState::onEnter()
{
    return this;
}

StateMachineState* EnumState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
