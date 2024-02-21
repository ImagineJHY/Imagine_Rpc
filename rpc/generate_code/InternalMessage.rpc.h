#ifndef INTERNALMESSAGE_RPC_H
#define INTERNALMESSAGE_RPC_H

#include "Imagine_Rpc/Imagine_Rpc.h"


namespace Imagine_Rpc
{


namespace Internal
{

class InternalMessage;

} // namespace Internal

} // namespace Imagine_Rpc

namespace Imagine_Rpc
{

namespace Internal
{

class FormatService : public ::Imagine_Rpc::Service
{
 public:
	FormatService();

	~FormatService();

	void Init();

	::Imagine_Rpc::Status FormatMethod(::Imagine_Rpc::Context* context, ::Imagine_Rpc::Internal::InternalMessage* request_msg, ::Imagine_Rpc::Internal::InternalMessage* response_msg);
};

} // namespace Internal

} // namespace Imagine_Rpc

#endif