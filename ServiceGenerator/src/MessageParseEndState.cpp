#include "ServiceGenerator/MessageParseEndState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/MessageState.h"
#include "ServiceGenerator/NameParseState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

MessageParseEndState::MessageParseEndState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(MESSAGE_PARSE_END_STATE_NAME, parent_state, sm)
{
}

MessageParseEndState::~MessageParseEndState()
{
}

void MessageParseEndState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&MessageParseEndState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), this, std::bind(&MessageParseEndState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool MessageParseEndState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != "}") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

bool MessageParseEndState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    MessageState* msg_state = dynamic_cast<MessageState*>(sm_->GetStatePtr(MESSAGE_STATE_NAME));
    NameParseState* msg_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(MESSAGE_NAME_PARSE_STATE_NAME));
    if (msg_state == nullptr || msg_name_parse_state == nullptr) {
        throw std::exception();
    }
    if (msg_state->GetPreName().size() != 0) {
        std::string pre_name = msg_state->GetPreName();
        std::string msg_name = "";
        for (size_t i = pre_name.size() - 1; i >= 1; i--) {
            if (pre_name.substr(i, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
                msg_name = pre_name.substr(i + 1, pre_name.size() - i - 1);
                pre_name = pre_name.substr(0, i);
                break;
            }
        }
        if (msg_name.size() == 0) {
            msg_name_parse_state->SetName(pre_name);
            msg_state->SetPreName("");
        } else {
            msg_name_parse_state->SetName(msg_name);
            msg_state->SetPreName(pre_name);
        }
        sm_->EventExecute(MESSAGE_PARSE_COMPLETE_TRANSITION_TO_MESSAGE_EVENT_NAME);
    } else {
        msg_name_parse_state->SetName("");
        sm_->EventExecute(MESSAGE_PARSE_COMPLETE_TRANSITION_TO_ROOT_EVENT_NAME);
    }

    return true;
}

StateMachineState* MessageParseEndState::onEnter()
{
    return this;
}

StateMachineState* MessageParseEndState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
