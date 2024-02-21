#include "ServiceGenerator/MessageState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/FieldState.h"
#include "ServiceGenerator/NameParseState.h"
#include "ServiceGenerator/ParseBeginState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/MessageParsePreState.h"
#include "ServiceGenerator/MessageParseEndState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

MessageState::MessageState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(MESSAGE_STATE_NAME, parent_state, sm)
{
    this->AddSubState(new NameParseState(this, sm_))->AddSubState(new ParseBeginState(this, sm_))->AddSubState(new MessageParsePreState(this, sm_))->AddSubState(new FieldState(this, sm_))->AddSubState(new MessageParseEndState(this, sm_));
}

MessageState::~MessageState()
{
}

void MessageState::Init()
{
    this->SetDefaultSubState(sm_->GetStatePtr(MESSAGE_NAME_PARSE_STATE_NAME));
    this->RegisterTransitionEventCallback(FIELD_PARSE_COMPLETE_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelTwoPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(MESSAGE_PARSE_PRE_STATE_NAME), nullptr);
}

void MessageState::SetPreName(const std::string& pre_name)
{
    pre_name_ = pre_name;
}

std::string MessageState::GetPreName() const
{
    return pre_name_;
}

StateMachineState* MessageState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("This is MessageState!\n");
    return this;
}

StateMachineState* MessageState::onExit()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("message exit\n");
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
