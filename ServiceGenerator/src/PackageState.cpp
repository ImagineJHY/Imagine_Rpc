#include "ServiceGenerator/PackageState.h"
#include "ServiceGenerator/PackageNameParseState.h"
#include "ServiceGenerator/PackageParseEndState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

PackageState::PackageState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(PACKAGE_STATE_NAME, parent_state, sm), is_parsed_(false)
{
    this->AddSubState(new PackageNameParseState(this, sm_))->AddSubState(new PackageParseEndState(this, sm_));
}

PackageState::~PackageState()
{
}

void PackageState::Init()
{
    this->SetDefaultSubState(sm_->GetStatePtr(PACKAGE_NAME_PARSE_STATE_NAME));
}

StateMachineState* PackageState::onEnter()
{
    if (is_parsed_) {
        // package唯一
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);
    }
    is_parsed_ = true;

    return this;
}

StateMachineState* PackageState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
