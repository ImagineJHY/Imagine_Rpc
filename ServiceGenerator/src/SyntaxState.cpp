#include "ServiceGenerator/SyntaxState.h"
#include "ServiceGenerator/SyntaxParsePrepareState.h"
#include "ServiceGenerator/SyntaxParseBeginState.h"
#include "ServiceGenerator/SyntaxNameParseState.h"
#include "ServiceGenerator/SyntaxParseEndState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

SyntaxState::SyntaxState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(SYNTAX_STATE_NAME, parent_state, sm), is_parsed_(false)
{
    this->AddSubState(new SyntaxParsePrepareState(this, sm_))->AddSubState(new SyntaxParseBeginState(this, sm_))->AddSubState(new SyntaxNameParseState(this, sm_))->AddSubState(new SyntaxParseEndState(this, sm_));
}

SyntaxState::~SyntaxState()
{
}

void SyntaxState::Init()
{
    this->SetDefaultSubState(sm_->GetStatePtr(SYNTAX_PARSE_PREPARE_STATE_NAME));
}

StateMachineState* SyntaxState::onEnter()
{
    if (is_parsed_) {
        // syntax唯一
        sm_->EventExecute(PARSE_ERROR_EVENT_NAME);
    }
    is_parsed_ = true;

    return this;
}

StateMachineState* SyntaxState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
