#include "ServiceGenerator/RpcServiceMethodState.h"
#include "ServiceGenerator/RpcServiceMethodLabelParseState.h"
#include "ServiceGenerator/RpcServiceMethodNameParseState.h"
#include "ServiceGenerator/RpcServiceMethodTypeParseBeginState.h"
#include "ServiceGenerator/RpcServiceMethodRequestTypeParseState.h"
#include "ServiceGenerator/RpcServiceMethodTypeSeparatorParseState.h"
#include "ServiceGenerator/RpcServiceMethodResponseTypeParseState.h"
#include "ServiceGenerator/RpcServiceMethodTypeParseEndState.h"
#include "ServiceGenerator/RpcServiceMethodParseEndState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceMethodState::RpcServiceMethodState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(RPCSERVICE_METHOD_STATE_NAME, parent_state, sm)
{
    this->AddSubState(new RpcServiceMethodLabelParseState       (this, sm_))->AddSubState(new RpcServiceMethodNameParseState        (this, sm_))->AddSubState(new RpcServiceMethodTypeParseBeginState       (this, sm_))
        ->AddSubState(new RpcServiceMethodRequestTypeParseState (this, sm_))->AddSubState(new RpcServiceMethodRequestTypeParseState (this, sm_))->AddSubState(new RpcServiceMethodTypeSeparatorParseState   (this, sm_))
        ->AddSubState(new RpcServiceMethodResponseTypeParseState(this, sm_))->AddSubState(new RpcServiceMethodTypeParseEndState     (this, sm_))->AddSubState(new RpcServiceMethodParseEndState             (this, sm_));
}

RpcServiceMethodState::~RpcServiceMethodState()
{
}

void RpcServiceMethodState::Init()
{
    this->SetDefaultSubState(sm_->GetStatePtr(RPCSERVICE_METHOD_LABEL_PARSE_STATE_NAME));
}

void RpcServiceMethodState::SetMethodName(const std::string& method_name)
{
    method_name_ = method_name;
}

void RpcServiceMethodState::SetRequestMessage(const std::string& request_msg)
{
    request_msg_ = request_msg;
}

void RpcServiceMethodState::SetResponseMessage(const std::string& response_msg)
{
    response_msg_ = response_msg;
}

std::string RpcServiceMethodState::GetMethodName() const
{
    return method_name_;
}

std::string RpcServiceMethodState::GetRequestMessage() const
{
    return request_msg_;
}

std::string RpcServiceMethodState::GetResponseMessage() const
{
    return response_msg_;
}

StateMachineState* RpcServiceMethodState::onEnter()
{
    method_name_ = request_msg_ = response_msg_ = "";
    
    return this;
}

StateMachineState* RpcServiceMethodState::onExit()
{
    return this;
}

} // namespace ServiceGenerator


} // namespace Imagine_Rp

