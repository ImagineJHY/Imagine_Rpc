#include "InternalMessage.rpc.h"

#include "InternalMessage.pb.h"

namespace Imagine_Rpc
{

namespace Internal
{

 FormatService::FormatService(): ::Imagine_Rpc::Service("Imagine_Rpc.Internal_FormatService")
{
	Init();
}

 FormatService::~FormatService(){
}

void FormatService::Init()
{
	REGISTER_MEMBER_FUNCTION("FormatMethod", ::Imagine_Rpc::Internal::InternalMessage, ::Imagine_Rpc::Internal::InternalMessage, &FormatService::FormatMethod);
}

::Imagine_Rpc::Status FormatService::FormatMethod(::Imagine_Rpc::Context* context, ::Imagine_Rpc::Internal::InternalMessage* request_msg, ::Imagine_Rpc::Internal::InternalMessage* response_msg)
{
	// Write Your Code Here :
}

} // namespace Internal

} // namespace Imagine_Rpc

