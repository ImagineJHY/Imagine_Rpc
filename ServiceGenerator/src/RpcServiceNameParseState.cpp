#include "ServiceGenerator/RpcServiceNameParseState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceNameParseState::RpcServiceNameParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(RPCSERVICE_NAME_PARSE_STATE_NAME, parent_state, sm), service_name_("")
{
}

RpcServiceNameParseState::~RpcServiceNameParseState()
{
}

void RpcServiceNameParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), std::bind(&RpcServiceNameParseState::ParseFieldCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), sm_->GetStatePtr(RPCSERVICE_PARSE_BEGIN_STATE_NAME), nullptr);

    // TODO : 这里同样name应可以为message/RpcService/syntax/package
    this->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr)
        ->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelThreePriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool RpcServiceNameParseState::ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    
    service_name_ = sm->GetContent();
    if (sm->IsCustomKeyWord(service_name_) || sm->IsCXXKeyWord(service_name_) || service_name_.find(".") != std::string::npos) {
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);

        return false;
    }
    sm->AddCustomKeyWord(service_name_);
    sm->AddService(service_name_);

    return true;
}

std::string RpcServiceNameParseState::GetServiceName() const
{
    return service_name_;
}

StateMachineState* RpcServiceNameParseState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("this is %s\n", GetStateName().c_str());
    return this;
}

StateMachineState* RpcServiceNameParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator


} // namespace Imagine_Rp

