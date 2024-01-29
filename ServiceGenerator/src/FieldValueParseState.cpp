#include "ServiceGenerator/FieldValueParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/EnumState.h"
#include "ServiceGenerator/NameParseState.h"
#include "ServiceGenerator/MessageState.h"
#include "ServiceGenerator/FieldState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

FieldValueParseState::FieldValueParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(parent_state->GetStateName() == MESSAGE_FIELD_STATE_NAME ? MESSAGE_FIELD_VALUE_PARSE_STATE_NAME : ENUM_FIELD_VALUE_PARSE_STATE_NAME, parent_state, sm)
{
}

FieldValueParseState::~FieldValueParseState()
{
}

void FieldValueParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&FieldValueParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(GetStateName() == MESSAGE_FIELD_VALUE_PARSE_STATE_NAME ? MESSAGE_FIELD_PARSE_END_STATE_NAME : ENUM_FIELD_PARSE_END_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool FieldValueParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    std::string content = sm->GetContent();
    bool value_flag = true;
    size_t value = 0;
    size_t zero_num = 0;
    size_t flag = true;
    if (content[0] == '-') {
        value_flag = false;
    }
    for (size_t i = value_flag ? 0 : 1; i < content.size(); i++) {
        int temp_value = content[i] - '0';
        if (0 <= temp_value && temp_value <= 9) {
            value = value * 10 + temp_value;
        } else {
            sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

            return false;
        }
        if (flag && value == 0) {
            zero_num++;
        } else {
            flag = false;
        }
    }

    if (zero_num == content.size()) {
        content = "0";
    } else {
        content = content.substr(zero_num, content.size() - zero_num);
    }
    if (parent_state_->GetStateName() == MESSAGE_FIELD_STATE_NAME) {
        MessageState* msg_state = dynamic_cast<MessageState*>(sm_->GetStatePtr(MESSAGE_STATE_NAME));
        NameParseState* msg_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(MESSAGE_NAME_PARSE_STATE_NAME));
        if (msg_state == nullptr || msg_name_parse_state == nullptr) {
            throw std::exception();
        }
        sm->AddCustomField((msg_state->GetPreName().size() ? msg_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + msg_name_parse_state->GetName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + content);
    } else {
        EnumState* enum_state = dynamic_cast<EnumState*>(sm_->GetStatePtr(ENUM_STATE_NAME));
        NameParseState* enum_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(ENUM_NAME_PARSE_STATE_NAME));
        if (enum_state == nullptr || enum_name_parse_state == nullptr) {
            throw std::exception();
        }
        sm->AddCustomField((enum_state->GetPreName().size() ? enum_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + enum_name_parse_state->GetName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + content);
    }
    FieldState* field_state = dynamic_cast<FieldState*>(parent_state_);
    if (field_state == nullptr) {
        throw std::exception();
    }
    field_state->SetValue(value_flag ? content : "-" + content);

    return true;
}

StateMachineState* FieldValueParseState::onEnter()
{
    return this;
}

StateMachineState* FieldValueParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
