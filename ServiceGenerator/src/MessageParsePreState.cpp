#include "ServiceGenerator/MessageParsePreState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/EnumState.h"
#include "ServiceGenerator/MessageState.h"
#include "ServiceGenerator/NameParseState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

MessageParsePreState::MessageParsePreState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(MESSAGE_PARSE_PRE_STATE_NAME, parent_state, sm)
{
}

MessageParsePreState::~MessageParsePreState()
{
}

void MessageParsePreState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(MESSAGE_FIELD_STATE_NAME), std::bind(&MessageParsePreState::ParseFieldCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&MessageParsePreState::ClassifyTaskCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(ROOT_STATE_NAME), std::bind(&MessageParsePreState::ClassifyTaskCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, this, std::bind(&MessageParsePreState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    this->RegisterTransitionEventCallback(MESSAGE_PARSE_COMPLETE_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(MESSAGE_PARSE_END_STATE_NAME), nullptr);
}

bool MessageParsePreState::ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    sm_->EventExecute(PARSE_FIELD_EVENT_NAME);
}

bool MessageParsePreState::ClassifyTaskCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    std::string content = sm->GetContent();
    if (content != KEYWORD_ENUM && content != KEYWORD_MESSAGE) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

bool MessageParsePreState::ClassifyTaskCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    MessageState* msg_state = dynamic_cast<MessageState*>(sm_->GetStatePtr(MESSAGE_STATE_NAME));
    NameParseState* msg_name_parse_state = dynamic_cast<NameParseState*>(sm_->GetStatePtr(MESSAGE_NAME_PARSE_STATE_NAME));
    if (msg_state == nullptr || msg_name_parse_state == nullptr) {
        throw std::exception();
    }
    std::string pre_name = msg_state->GetPreName().size() ? msg_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + msg_name_parse_state->GetName() : msg_name_parse_state->GetName();
    // IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("---------------------------------------prename is %s\n", pre_name.c_str());
    if (sm->GetContent() == KEYWORD_MESSAGE) {
        msg_state->SetPreName(pre_name);
        msg_name_parse_state->SetName("");
        sm_->EventExecute(PARSE_SUB_MESSAGE_EVENT_NAME);
    } else {
        EnumState* enum_state = dynamic_cast<EnumState*>(sm_->GetStatePtr(ENUM_STATE_NAME));
        if (enum_state == nullptr) {
            throw std::exception();
        }
        enum_state->SetPreName(pre_name);
        sm_->EventExecute(PARSE_SUB_ENUM_EVENT_NAME);
    }
    
    return true;
}

bool MessageParsePreState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() == "}") {
        sm_->EventExecute(MESSAGE_PARSE_COMPLETE_EVENT_NAME);
        sm_->EventExecute(PARSE_SYMBOL_EVENT_NAME);
    } else if (sm->GetContent() != ";") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

StateMachineState* MessageParsePreState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("This is %s\n", GetStateName().c_str());

    return this;
}

StateMachineState* MessageParsePreState::onExit()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("exit!\n");
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
