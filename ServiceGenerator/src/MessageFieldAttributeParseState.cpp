#include "ServiceGenerator/MessageFieldAttributeParseState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/FieldState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

MessageFieldAttributeParseState::MessageFieldAttributeParseState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(MESSAGE_FIELD_ATTRIBUTE_PARSE_STATE_NAME, parent_state, sm)
{
}

MessageFieldAttributeParseState::~MessageFieldAttributeParseState()
{
}

void MessageFieldAttributeParseState::Init()
{
    this->RegisterTransitionEventCallback(PARSE_FIELD_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(MESSAGE_FIELD_DATATYPE_PARSE_STATE_NAME), std::bind(&MessageFieldAttributeParseState::ParseFieldCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
        ->RegisterTransitionEventCallback(PARSE_SYMBOL_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), std::bind(&MessageFieldAttributeParseState::ParseSymbolCondition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), this, nullptr);

    this->RegisterTransitionEventCallback(CLASSIFY_TASK_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelFourPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(ERROR_STATE_NAME), nullptr);
}

bool MessageFieldAttributeParseState::ParseFieldCallback(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    const ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->IsAttributeKeyWord(sm->GetContent())) {
        FieldState* field_state = dynamic_cast<FieldState*>(parent_state_);
        if (field_state == nullptr) {
            throw std::exception();
        }
        field_state->SetAttribute(sm->GetContent());

        return true;
    } else {
        sm_->EventExecute(PARSE_FIELD_EVENT_NAME);

        return false;
    }
}

bool MessageFieldAttributeParseState::ParseSymbolCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
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

StateMachineState* MessageFieldAttributeParseState::onEnter()
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("This is %s\n", GetStateName().c_str());

    return this;
}

StateMachineState* MessageFieldAttributeParseState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
