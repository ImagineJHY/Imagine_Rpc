#include "ServiceGenerator/RootState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/EnumState.h"
#include "ServiceGenerator/ErrorState.h"
#include "ServiceGenerator/ImportState.h"
#include "ServiceGenerator/SyntaxState.h"
#include "ServiceGenerator/PackageState.h"
#include "ServiceGenerator/MessageState.h"
#include "ServiceGenerator/RpcServiceState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RootState::RootState(StateMachine* sm) : ServiceGeneratorStateMachineState(ROOT_STATE_NAME, nullptr, sm)
{
    this->AddSubState(new SyntaxState(this, sm))->AddSubState(new PackageState(this, sm))->AddSubState(new MessageState(this, sm))->AddSubState(new RpcServiceState(this, sm))->AddSubState(new EnumState(this, sm))->AddSubState(new ImportState(this, sm))->AddSubState(new ErrorState(this, sm));
}

RootState::~RootState()
{
    //TODO : 释放资源
}

void RootState::Init()
{
    this->RegisterActorEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelOnePriority), std::bind(&RootState::ClassifyTaskCondition, this, std::placeholders::_1, std::placeholders::_2), std::bind(&RootState::ClassifyTaskActor, this, std::placeholders::_1, std::placeholders::_2));

    this->RegisterTransitionEventCallback(PARSE_SYNTAX_EVENT_NAME,      static_cast<size_t>(StateEventPriority::LevelOnePriority), std::bind(&RootState::ParseSyntaxCondition,      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(SYNTAX_STATE_NAME),        nullptr)
        ->RegisterTransitionEventCallback(PARSE_PACKAGE_EVETN_NAME,     static_cast<size_t>(StateEventPriority::LevelOnePriority), std::bind(&RootState::ParsePackageCondition,     this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(PACKAGE_STATE_NAME),       nullptr)
        ->RegisterTransitionEventCallback(PARSE_MESSAGE_EVENT_NAME,     static_cast<size_t>(StateEventPriority::LevelOnePriority), std::bind(&RootState::ParseMessageCondition,     this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(MESSAGE_STATE_NAME),       nullptr)
        ->RegisterTransitionEventCallback(PARSE_RPCSERVICE_EVENT_NAME,  static_cast<size_t>(StateEventPriority::LevelOnePriority), std::bind(&RootState::ParseRpcServiceCondition,  this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(RPCSERVICE_STATE_NAME),    nullptr)
        ->RegisterTransitionEventCallback(PARSE_ENUM_EVENT_NAME,        static_cast<size_t>(StateEventPriority::LevelOnePriority), std::bind(&RootState::ParseEnumCondition,        this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(ENUM_STATE_NAME),          nullptr)
        ->RegisterTransitionEventCallback(PARSE_IMPORT_EVENT_NAME,      static_cast<size_t>(StateEventPriority::LevelOnePriority), std::bind(&RootState::ParseImportCondition,  this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(IMPORT_STATE_NAME),        nullptr)
        ->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME,      static_cast<size_t>(StateEventPriority::LevelOnePriority), std::bind(&RootState::ParseSymbolCondition,      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), this,                                       nullptr);
    
    this->RegisterTransitionEventCallback(PARSE_SUB_MESSAGE_EVENT_NAME,                             static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(MESSAGE_STATE_NAME),             nullptr)
        ->RegisterTransitionEventCallback(PARSE_SUB_ENUM_EVENT_NAME,                                static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ENUM_STATE_NAME),                nullptr)
        ->RegisterTransitionEventCallback(MESSAGE_PARSE_COMPLETE_TRANSITION_TO_ROOT_EVENT_NAME,     static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, this,                                             std::bind(&RootState::TransitionToRootCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(MESSAGE_PARSE_COMPLETE_TRANSITION_TO_MESSAGE_EVENT_NAME,  static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(MESSAGE_PARSE_PRE_STATE_NAME),   nullptr)
        ->RegisterTransitionEventCallback(ENUM_PARSE_COMPLETE_TRANSITION_TO_ROOT_EVENT_NAME,        static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, this,                                             std::bind(&RootState::TransitionToRootCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(ENUM_PARSE_COMPLETE_TRANSITION_TO_MESSAGE_EVENT_NAME,     static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(MESSAGE_PARSE_PRE_STATE_NAME),   nullptr)
        ->RegisterTransitionEventCallback(SYNTAX_PARSE_COMPLETE_EVENT_NAME,                         static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, this,                                             std::bind(&RootState::TransitionToRootCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(PACKAGE_PARSE_COMPLETE_EVENT_NAME,                        static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, this,                                             std::bind(&RootState::TransitionToRootCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(RPCSERVICE_PARSE_COMPLETE_EVENT_NAME,                     static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, this,                                             std::bind(&RootState::TransitionToRootCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(IMPORT_PARSE_COMPLETE_EVENT_NAME,                         static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, this,                                             std::bind(&RootState::TransitionToRootCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME,   static_cast<size_t>(StateEventPriority::LevelOnePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool RootState::ClassifyTaskCondition(StateMachineState* src, StateMachineEvent evt)
{
    return true;
}

bool RootState::ClassifyTaskActor(StateMachineState* src, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    std::string content = sm->GetContent();
    if (content == KEYWORD_SYNTAX) {
        sm_->EventExecute(PARSE_SYNTAX_EVENT_NAME);
    } else if (content == KEYWORD_PACKAGE) {
        sm_->EventExecute(PARSE_PACKAGE_EVETN_NAME);
    } else if (content == KEYWORD_MESSAGE) {
        MessageState* msg_state = dynamic_cast<MessageState*>(sm_->GetStatePtr(MESSAGE_STATE_NAME));
        if (msg_state == nullptr) {
            throw std::exception();
        }
        msg_state->SetPreName("");
        sm_->EventExecute(PARSE_MESSAGE_EVENT_NAME);
    } else if (content == KEYWORD_RPCSERVICE) {
        sm_->EventExecute(PARSE_RPCSERVICE_EVENT_NAME);
    } else if (content == KEYWORD_ENUM) {
        EnumState* enum_state = dynamic_cast<EnumState*>(sm_->GetStatePtr(ENUM_STATE_NAME));
        if (enum_state == nullptr) {
            throw std::exception();
        }
        enum_state->SetPreName("");
        sm_->EventExecute(PARSE_ENUM_EVENT_NAME);
    } else if (content == KEYWORD_IMPORT) {
        sm_->EventExecute(PARSE_IMPORT_EVENT_NAME);
    } else {
        return false;
    }

    return true;
}

bool RootState::ParseSyntaxCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        throw std::exception();
        return false;
    }
    if (sm->GetContent() == KEYWORD_SYNTAX) {
        return true;
    }

    throw std::exception();
    return false;
}

bool RootState::ParsePackageCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        throw std::exception();
        return false;
    }
    if (sm->GetContent() == KEYWORD_PACKAGE) {
        return true;
    }

    throw std::exception();
    return false;
}

bool RootState::ParseMessageCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        throw std::exception();
        return false;
    }
    if (sm->GetContent() == KEYWORD_MESSAGE) {
        return true;
    }

    throw std::exception();
    return false;
}

bool RootState::ParseRpcServiceCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        throw std::exception();
        return false;
    }
    if (sm->GetContent() == KEYWORD_RPCSERVICE) {
        return true;
    }

    throw std::exception();
    return false;
}

bool RootState::ParseEnumCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        throw std::exception();
        return false;
    }
    if (sm->GetContent() == KEYWORD_ENUM) {
        return true;
    }

    throw std::exception();
    return false;
}

bool RootState::ParseImportCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        throw std::exception();
        return false;
    }
    if (sm->GetContent() == KEYWORD_IMPORT) {
        return true;
    }

    throw std::exception();
    return false;
}

bool RootState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        throw std::exception();
        return false;
    }
    if (sm->GetContent() != ";") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

bool RootState::TransitionToRootCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ExitAllsubState();
}

StateMachineState* RootState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("This is RootState!\n");
    return this;
}

StateMachineState* RootState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
