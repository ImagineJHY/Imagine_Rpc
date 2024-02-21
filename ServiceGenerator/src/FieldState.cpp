#include "ServiceGenerator/FieldState.h"
#include "ServiceGenerator/MessageFieldAttributeParseState.h"
#include "ServiceGenerator/MessageFieldDataTypeParseState.h"
#include "ServiceGenerator/FieldNameParseState.h"
#include "ServiceGenerator/FieldSymbolParseState.h"
#include "ServiceGenerator/FieldValueParseState.h"
#include "ServiceGenerator/FieldParseEndState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

FieldState::FieldState(StateMachineState* const parent_state, StateMachine* sm, bool is_msg_field) : ServiceGeneratorStateMachineState(parent_state->GetStateName() == MESSAGE_STATE_NAME ? MESSAGE_FIELD_STATE_NAME : ENUM_FIELD_STATE_NAME, parent_state, sm)
{
    if (parent_state->GetStateName() == MESSAGE_STATE_NAME) {
        this->AddSubState(new MessageFieldAttributeParseState(this, sm_))->AddSubState(new MessageFieldDataTypeParseState(this, sm_));
    }
    this->AddSubState(new FieldNameParseState(this, sm_))->AddSubState(new FieldSymbolParseState(this, sm_))->AddSubState(new FieldValueParseState(this, sm_))->AddSubState(new FieldParseEndState(this, sm_));
}

FieldState::~FieldState()
{
}

void FieldState::Init()
{
    this->SetDefaultSubState(GetSubStatePtr(parent_state_->GetStateName() == MESSAGE_STATE_NAME ? MESSAGE_FIELD_ATTRIBUTE_PARSE_STATE_NAME : ENUM_FIELD_NAME_PARSE_STATE_NAME));
    if (parent_state_->GetStateName() == MESSAGE_STATE_NAME) {

    } else {

    }
}

void FieldState::SetAttribute(const std::string& field_attribute)
{
    field_attribute_ = field_attribute;
}

std::string FieldState::GetAttribute()
{
    return field_attribute_;
}

void FieldState::SetDataType(const std::string& field_datatype)
{
    filed_datatype_ = field_datatype;
}

std::string FieldState::GetDataType()
{
    return filed_datatype_;
}

void FieldState::SetName(const std::string& field_name)
{
    field_name_ = field_name;
}

std::string FieldState::GetName()
{
    return field_name_;
}

void FieldState::SetValue(const std::string& field_value)
{
    field_value_ = field_value;
}

std::string FieldState::GetValue()
{
    return field_value_;
}

StateMachineState* FieldState::onEnter()
{  
    field_attribute_ = filed_datatype_ = field_name_ = field_value_ = "";
    
    return this;
}

StateMachineState* FieldState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
