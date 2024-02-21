#include "ServiceGenerator/MessageFieldDataTypeParseState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/FieldState.h"
#include "ServiceGenerator/MessageState.h"
#include "ServiceGenerator/NameParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

MessageFieldDataTypeParseState::MessageFieldDataTypeParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(MESSAGE_FIELD_DATATYPE_PARSE_STATE_NAME, parent_state, sm)
{
}

MessageFieldDataTypeParseState::~MessageFieldDataTypeParseState()
{
}

void MessageFieldDataTypeParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&MessageFieldDataTypeParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(MESSAGE_FIELD_NAME_PARSE_STATE_NAME), nullptr);

    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool MessageFieldDataTypeParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    MessageState* msg_state = dynamic_cast<MessageState*>(sm_->GetStatePtr(MESSAGE_STATE_NAME));
    NameParseState* msg_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(MESSAGE_NAME_PARSE_STATE_NAME));
    if (msg_state == nullptr || msg_name_parse_state == nullptr) {
        throw std::exception();
    }
    std::string content = sm->GetContent();
    FieldState* field_state = dynamic_cast<FieldState*>(parent_state_);
    if (field_state == nullptr) {
        throw std::exception();
    }
    field_state->SetDataType(content); // content是否要优化(规范化)？
    if (sm->IsProtobufDataTypeKeyWord(content) || sm->IsDirectImportCustomKeyWord(content)) {
        return true;
    } else if (sm->IsCXXKeyWord(content) || sm->IsIndirectImportCustomKeyWord(content)) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    } else {
        MessageState* msg_state = dynamic_cast<MessageState*>(sm_->GetStatePtr(MESSAGE_STATE_NAME));
        sm->AddUndefinedKeyWord((msg_state->GetPreName().size() ? msg_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + msg_name_parse_state->GetName(), content);

        return true;
    }

    return true;
}

StateMachineState* MessageFieldDataTypeParseState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("This is %s\n", GetStateName().c_str());

    return this;
}

StateMachineState* MessageFieldDataTypeParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
