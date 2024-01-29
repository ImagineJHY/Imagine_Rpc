#include "ServiceGenerator/FieldNameParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/EnumState.h"
#include "ServiceGenerator/MessageState.h"
#include "ServiceGenerator/NameParseState.h"
#include "ServiceGenerator/FieldState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

FieldNameParseState::FieldNameParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(parent_state->GetStateName() == MESSAGE_FIELD_STATE_NAME ? MESSAGE_FIELD_NAME_PARSE_STATE_NAME : ENUM_FIELD_NAME_PARSE_STATE_NAME, parent_state, sm)
{
    if (parent_state->GetStateName() == MESSAGE_STATE_NAME) {

    } else {
    }
}

FieldNameParseState::~FieldNameParseState()
{
}

void FieldNameParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&FieldNameParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(GetStateName() == MESSAGE_FIELD_NAME_PARSE_STATE_NAME ? MESSAGE_FIELD_SYMBOL_PARSE_STATE_NAME : ENUM_FIELD_SYMBOL_PARSE_STATE_NAME), nullptr);
    
    if (GetStateName() == MESSAGE_FIELD_NAME_PARSE_STATE_NAME) {
        this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
    } else {
        this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&FieldNameParseState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), this, nullptr);
    }
    // TODO : 这里实际应该能够接收Field为message/enum/package/syntax/RpcService的情况
    this->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool FieldNameParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    field_name_ = sm->GetContent();
    if (field_name_.find(".") != std::string::npos || sm->IsCXXKeyWord(field_name_)) {
        sm->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    if (parent_state_->GetStateName() == MESSAGE_FIELD_STATE_NAME) {
        MessageState* msg_state = dynamic_cast<MessageState*>(sm_->GetStatePtr(MESSAGE_STATE_NAME));
        NameParseState* msg_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(MESSAGE_NAME_PARSE_STATE_NAME));
        if (msg_state == nullptr || msg_name_parse_state == nullptr) {
            throw std::exception();
        }
        if (sm->IsKeyWord((msg_state->GetPreName().size() ? msg_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + msg_name_parse_state->GetName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + field_name_)) {
            sm->EventExecute(PARSE_ERROR_EVENT_NAME);

            return false;
        }
        sm->AddCustomField((msg_state->GetPreName().size() ? msg_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + msg_name_parse_state->GetName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + field_name_);
    } else {
        EnumState* enum_state = dynamic_cast<EnumState*>(sm_->GetStatePtr(ENUM_STATE_NAME));
        NameParseState* enum_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(ENUM_NAME_PARSE_STATE_NAME));
        if (enum_state == nullptr || enum_name_parse_state == nullptr) {
            throw std::exception();
        }
        if (sm->IsKeyWord((enum_state->GetPreName().size() ? enum_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + enum_name_parse_state->GetName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + field_name_)) {
            sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

            return false;
        }
        sm->AddCustomField(enum_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + field_name_);
    }
    FieldState* field_state = dynamic_cast<FieldState*>(parent_state_);
    if (field_state == nullptr) {
        throw std::exception();
    }
    field_state->SetName(field_name_);

    return true;
}

bool FieldNameParseState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != ";") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

StateMachineState* FieldNameParseState::onEnter()
{
    return this;
}

StateMachineState* FieldNameParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
