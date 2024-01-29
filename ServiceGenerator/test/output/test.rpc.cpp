#include "test.rpc.h"

#include "test.pb.h"
#include "test_import2.a.pb.h"
#include "test_import.a.pb.h"
#include "test_import.pb.h"
#include "test_import2.pb.h"

namespace message1
{

 Import2Service::Import2Service(): ::Imagine_Rpc::Service("message1_Import2Service")
{
	Init();
}

 Import2Service::~Import2Service(){
}

void Import2Service::Init()
{
	REGISTER_MEMBER_FUNCTION("Import2Method", ::import2requestmsg, ::import2responsemsg, &Import2Service::Import2Method);
}

::Imagine_Rpc::Status Import2Service::Import2Method(::Imagine_Rpc::Context* context, ::import2requestmsg* request_msg, ::import2responsemsg* response_msg)
{
	// Write Your Code Here :
}

 FormatService::FormatService(): ::Imagine_Rpc::Service("message1_FormatService")
{
	Init();
}

 FormatService::~FormatService(){
}

void FormatService::Init()
{
	REGISTER_MEMBER_FUNCTION("FormatMethod", ::message1::InternalMessage, ::message1::InternalMessage, &FormatService::FormatMethod);
}

::Imagine_Rpc::Status FormatService::FormatMethod(::Imagine_Rpc::Context* context, ::message1::InternalMessage* request_msg, ::message1::InternalMessage* response_msg)
{
	// Write Your Code Here :
}

 ImportService::ImportService(): ::Imagine_Rpc::Service("message1_ImportService")
{
	Init();
}

 ImportService::~ImportService(){
}

void ImportService::Init()
{
	REGISTER_MEMBER_FUNCTION("ImportMethod", ::import_package_request_msg, ::import_package_response_msg, &ImportService::ImportMethod);
}

::Imagine_Rpc::Status ImportService::ImportMethod(::Imagine_Rpc::Context* context, ::import_package_request_msg* request_msg, ::import_package_response_msg* response_msg)
{
	// Write Your Code Here :
}

} // message1

