#ifndef IMAGINE_RPC_SERVICEGENERATOR_FIELDSTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_FIELDSTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class FieldState : public ServiceGeneratorStateMachineState
{
 public:
    FieldState(StateMachineState* const parent_state, StateMachine* sm = nullptr, bool is_msg_field = true);

    ~FieldState();

    void SetAttribute(const std::string& field_attribute);

    std::string GetAttribute();

    void SetDataType(const std::string& field_datatype);

    std::string GetDataType();

    void SetName(const std::string& field_name);

    std::string GetName();

    void SetValue(const std::string& field_value);

    std::string GetValue();

 public:
    void Init() override;

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    std::string field_attribute_;
    std::string filed_datatype_;
    std::string field_name_;
    std::string field_value_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif