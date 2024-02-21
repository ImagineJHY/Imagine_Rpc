#include "ServiceGenerator/FieldParseEndState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/FieldState.h"
#include "ServiceGenerator/MessageState.h"
#include "ServiceGenerator/EnumState.h"
#include "ServiceGenerator/NameParseState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

FieldParseEndState::FieldParseEndState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(parent_state->GetStateName() == MESSAGE_FIELD_STATE_NAME ? MESSAGE_FIELD_PARSE_END_STATE_NAME : ENUM_FIELD_PARSE_END_STATE_NAME, parent_state, sm)
{
}

FieldParseEndState::~FieldParseEndState()
{
}

void FieldParseEndState::Init()
{
    // 此处不为Actor仅为了保证更高的优先级, 优先处理当前事件
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, this, std::bind(&FieldParseEndState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool FieldParseEndState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != ";") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    // sm->AddField();
    FieldState* field_state = dynamic_cast<FieldState*>(parent_state_);
    if (GetStateName() == MESSAGE_FIELD_PARSE_END_STATE_NAME) {
        MessageState* msg_state = dynamic_cast<MessageState*>(sm_->GetStatePtr(MESSAGE_STATE_NAME));
        NameParseState* msg_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(MESSAGE_NAME_PARSE_STATE_NAME));
        sm->AddMessageField((msg_state->GetPreName().size() ? msg_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + msg_name_parse_state->GetName(), field_state->GetAttribute(), field_state->GetDataType(), field_state->GetName(), field_state->GetValue());
    } else {
        EnumState* enum_state = dynamic_cast<EnumState*>(sm_->GetStatePtr(ENUM_STATE_NAME));
        NameParseState* enum_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(ENUM_NAME_PARSE_STATE_NAME));
        sm->AddEnumField((enum_state->GetPreName().size() ? enum_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + enum_name_parse_state->GetName(), field_state->GetName(), field_state->GetValue());
    }
    sm_->EventExecute(FIELD_PARSE_COMPLETE_EVENT_NAME);

    return true;
}

StateMachineState* FieldParseEndState::onEnter()
{
    return this;
}

StateMachineState* FieldParseEndState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
