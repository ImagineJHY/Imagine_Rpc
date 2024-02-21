#include "ServiceGenerator/NameParseState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/EnumState.h"
#include "ServiceGenerator/MessageState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorUtil.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

NameParseState::NameParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(parent_state->GetStateName() == MESSAGE_STATE_NAME ? MESSAGE_NAME_PARSE_STATE_NAME : ENUM_NAME_PARSE_STATE_NAME, parent_state, sm), name_("")
{
}

NameParseState::~NameParseState()
{
}

void NameParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&NameParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(parent_state_->GetStateName() == MESSAGE_STATE_NAME ? MESSAGE_PARSE_BEGIN_STATE_NAME : ENUM_PARSE_BEGIN_STATE_NAME), nullptr);

    // TODO : 这里实际应该能够接收Name为message/enum/package/syntax/RpcService的情况
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

void NameParseState::SetName(const std::string& name)
{
    name_ = name;
}

std::string NameParseState::GetName() const
{
    return name_;
}

bool NameParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    name_ = sm->GetContent();
    if (name_.find(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) != std::string::npos || sm->IsCXXKeyWord(name_)) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    if (!ServiceGeneratorUtil::IsValidName(name_)) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    if (parent_state_->GetStateName() == MESSAGE_STATE_NAME) {
        MessageState* msg_state = dynamic_cast<MessageState*>(parent_state_);
        if (msg_state == nullptr) {
            throw std::exception();
        }
        if (sm->IsCustomKeyWord((msg_state->GetPreName().size() ? msg_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + name_)) {
            sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

            return false;
        }
        sm->AddCustomMessageKeyWord((msg_state->GetPreName().size() ? msg_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + name_);
    } else {
        EnumState* enum_state = dynamic_cast<EnumState*>(parent_state_);
        if (enum_state == nullptr) {
            throw std::exception();
        }
        if (sm->IsCustomKeyWord((enum_state->GetPreName().size() ? enum_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + name_)) {
            sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

            return false;
        }
        sm->AddCustomEnumKeyWord((enum_state->GetPreName().size() ? enum_state->GetPreName() + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + name_);
    }

    return true;
}

StateMachineState* NameParseState::onEnter()
{
    if (GetStateName() == MESSAGE_NAME_PARSE_STATE_NAME) {
        IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("This is %s!\n", MESSAGE_NAME_PARSE_STATE_NAME);
    } else {
        IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("This is %s!\n", ENUM_NAME_PARSE_STATE_NAME);
    }
    return this;
}

StateMachineState* NameParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
