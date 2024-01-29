#ifndef IMAGINE_RPC_SERVICEGENERATOR_MESSAGESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_MESSAGESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class MessageState : public ServiceGeneratorStateMachineState
{
 public:
    MessageState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~MessageState();

    void SetPreName(const std::string& pre_name);

    std::string GetPreName() const;

 public:
    void Init() override;

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    std::string pre_name_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc

#endif