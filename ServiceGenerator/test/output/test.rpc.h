#ifndef TEST_RPC_H
#define TEST_RPC_H

#include "Imagine_Rpc/Imagine_Rpc.h"

class import_package_request_msg;
class import_package_response_msg;
class import2responsemsg;
class import2requestmsg;

namespace message1
{

class InternalMessage;

} // namespace message1

namespace message1
{

class Import2Service : public ::Imagine_Rpc::Service
{
 public:
	Import2Service();

	~Import2Service();

	void Init();

	::Imagine_Rpc::Status Import2Method(::Imagine_Rpc::Context* context, ::import2requestmsg* request_msg, ::import2responsemsg* response_msg);
};

class FormatService : public ::Imagine_Rpc::Service
{
 public:
	FormatService();

	~FormatService();

	void Init();

	::Imagine_Rpc::Status FormatMethod(::Imagine_Rpc::Context* context, ::message1::InternalMessage* request_msg, ::message1::InternalMessage* response_msg);
};

class ImportService : public ::Imagine_Rpc::Service
{
 public:
	ImportService();

	~ImportService();

	void Init();

	::Imagine_Rpc::Status ImportMethod(::Imagine_Rpc::Context* context, ::import_package_request_msg* request_msg, ::import_package_response_msg* response_msg);
};

} // namespace message1

#endif