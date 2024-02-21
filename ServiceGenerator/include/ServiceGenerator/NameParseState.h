#ifndef IMAGINE_RPC_SERVICEGENERATOR_NAMEPARSESTATE_H
#define IMAGINE_RPC_SERVICEGENERATOR_NAMEPARSESTATE_H

#include "ServiceGeneratorStateMachineState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class NameParseState : public ServiceGeneratorStateMachineState
{
 public:
    NameParseState(StateMachineState* const parent_state, StateMachine* sm = nullptr);

    ~NameParseState();

    void SetName(const std::string& name);

    std::string GetName() const;

 public:
    void Init() override;

 public:
    bool ParseFieldCondition(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt);

 private:
    StateMachineState* onEnter() override;

    StateMachineState* onExit() override;

 private:
    std::string name_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif