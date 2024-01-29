#include "ServiceGenerator/ImportPathParseState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

ImportPathParseState::ImportPathParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(IMPORT_PATH_PARSE_STATE_NAME, parent_state, sm), path_("")
{
}

ImportPathParseState::~ImportPathParseState()
{
}

void ImportPathParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&ImportPathParseState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), this, std::bind(&ImportPathParseState::ParseSymbolCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, this, std::bind(&ImportPathParseState::ParseFieldCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, this, std::bind(&ImportPathParseState::ParseFieldCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void ImportPathParseState::ResetPath()
{
    path_ = "";
}

bool ImportPathParseState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    // TODO : linux文件名允许-等字符
    std::string content = sm->GetContent();
    if (content != "/" && content != "\"" && content != "-" && content != ".") {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }

    return true;
}

bool ImportPathParseState::ParseSymbolCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->GetContent() != "\"") {
        return true;
    }
    sm->AddImport(path_);
    sm_->EventExecute(IMPORT_PATH_PARSE_COMPLETE_EVENT_NAME);
    sm_->EventExecute(PARSE_SYMBOL_EVENT_NAME);

    return true;
}

bool ImportPathParseState::ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<const ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    path_ += sm->GetContent();

    return true;
}

std::string ImportPathParseState::GetPath() const
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("this is %s\n", GetStateName().c_str());
    return path_;
}

StateMachineState* ImportPathParseState::onEnter()
{
    return this;
}

StateMachineState* ImportPathParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
