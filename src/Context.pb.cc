// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Context.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Imagine_Rpc/Context.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Imagine_Rpc {

namespace {

const ::google::protobuf::Descriptor* Context_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Context_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Context_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_Context_2eproto() {
  protobuf_AddDesc_Context_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Context.proto");
  GOOGLE_CHECK(file != NULL);
  Context_descriptor_ = file->message_type(0);
  static const int Context_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, service_name__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, method_name__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, message_size__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, send_ip__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, send_port__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, recv_ip__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, recv_port__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, sockfd__),
  };
  Context_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Context_descriptor_,
      Context::default_instance_,
      Context_offsets_,
      -1,
      -1,
      -1,
      sizeof(Context),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Context, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Context_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Context_descriptor_, &Context::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Context_2eproto() {
  delete Context::default_instance_;
  delete Context_reflection_;
}

void protobuf_AddDesc_Context_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_Context_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rContext.proto\022\013Imagine_Rpc\"\252\001\n\007Context"
    "\022\025\n\rservice_name_\030\001 \001(\t\022\024\n\014method_name_\030"
    "\002 \001(\t\022\025\n\rmessage_size_\030\003 \001(\004\022\020\n\010send_ip_"
    "\030\004 \001(\t\022\022\n\nsend_port_\030\005 \001(\t\022\020\n\010recv_ip_\030\006"
    " \001(\t\022\022\n\nrecv_port_\030\007 \001(\t\022\017\n\007sockfd_\030\010 \001("
    "\005b\006proto3", 209);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Context.proto", &protobuf_RegisterTypes);
  Context::default_instance_ = new Context();
  Context::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Context_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Context_2eproto {
  StaticDescriptorInitializer_Context_2eproto() {
    protobuf_AddDesc_Context_2eproto();
  }
} static_descriptor_initializer_Context_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Context::kServiceNameFieldNumber;
const int Context::kMethodNameFieldNumber;
const int Context::kMessageSizeFieldNumber;
const int Context::kSendIpFieldNumber;
const int Context::kSendPortFieldNumber;
const int Context::kRecvIpFieldNumber;
const int Context::kRecvPortFieldNumber;
const int Context::kSockfdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Context::Context()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Imagine_Rpc.Context)
}

void Context::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

Context::Context(const Context& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Imagine_Rpc.Context)
}

void Context::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  service_name__.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name__.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  message_size__ = GOOGLE_ULONGLONG(0);
  send_ip__.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  send_port__.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  recv_ip__.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  recv_port__.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  sockfd__ = 0;
}

Context::~Context() {
  // @@protoc_insertion_point(destructor:Imagine_Rpc.Context)
  SharedDtor();
}

void Context::SharedDtor() {
  service_name__.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name__.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  send_ip__.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  send_port__.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  recv_ip__.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  recv_port__.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void Context::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Context::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Context_descriptor_;
}

const Context& Context::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Context_2eproto();
  return *default_instance_;
}

Context* Context::default_instance_ = NULL;

Context* Context::New(::google::protobuf::Arena* arena) const {
  Context* n = new Context;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Context::Clear() {
// @@protoc_insertion_point(message_clear_start:Imagine_Rpc.Context)
  service_name__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  message_size__ = GOOGLE_ULONGLONG(0);
  send_ip__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  send_port__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  recv_ip__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  recv_port__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  sockfd__ = 0;
}

bool Context::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Imagine_Rpc.Context)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string service_name_ = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_service_name_()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->service_name_().data(), this->service_name_().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "Imagine_Rpc.Context.service_name_"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_method_name_;
        break;
      }

      // optional string method_name_ = 2;
      case 2: {
        if (tag == 18) {
         parse_method_name_:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_method_name_()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->method_name_().data(), this->method_name_().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "Imagine_Rpc.Context.method_name_"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_message_size_;
        break;
      }

      // optional uint64 message_size_ = 3;
      case 3: {
        if (tag == 24) {
         parse_message_size_:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &message_size__)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_send_ip_;
        break;
      }

      // optional string send_ip_ = 4;
      case 4: {
        if (tag == 34) {
         parse_send_ip_:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_send_ip_()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->send_ip_().data(), this->send_ip_().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "Imagine_Rpc.Context.send_ip_"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_send_port_;
        break;
      }

      // optional string send_port_ = 5;
      case 5: {
        if (tag == 42) {
         parse_send_port_:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_send_port_()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->send_port_().data(), this->send_port_().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "Imagine_Rpc.Context.send_port_"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(50)) goto parse_recv_ip_;
        break;
      }

      // optional string recv_ip_ = 6;
      case 6: {
        if (tag == 50) {
         parse_recv_ip_:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_recv_ip_()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->recv_ip_().data(), this->recv_ip_().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "Imagine_Rpc.Context.recv_ip_"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(58)) goto parse_recv_port_;
        break;
      }

      // optional string recv_port_ = 7;
      case 7: {
        if (tag == 58) {
         parse_recv_port_:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_recv_port_()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->recv_port_().data(), this->recv_port_().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "Imagine_Rpc.Context.recv_port_"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_sockfd_;
        break;
      }

      // optional int32 sockfd_ = 8;
      case 8: {
        if (tag == 64) {
         parse_sockfd_:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &sockfd__)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Imagine_Rpc.Context)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Imagine_Rpc.Context)
  return false;
#undef DO_
}

void Context::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Imagine_Rpc.Context)
  // optional string service_name_ = 1;
  if (this->service_name_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->service_name_().data(), this->service_name_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.service_name_");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->service_name_(), output);
  }

  // optional string method_name_ = 2;
  if (this->method_name_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->method_name_().data(), this->method_name_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.method_name_");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->method_name_(), output);
  }

  // optional uint64 message_size_ = 3;
  if (this->message_size_() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(3, this->message_size_(), output);
  }

  // optional string send_ip_ = 4;
  if (this->send_ip_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->send_ip_().data(), this->send_ip_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.send_ip_");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->send_ip_(), output);
  }

  // optional string send_port_ = 5;
  if (this->send_port_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->send_port_().data(), this->send_port_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.send_port_");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->send_port_(), output);
  }

  // optional string recv_ip_ = 6;
  if (this->recv_ip_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->recv_ip_().data(), this->recv_ip_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.recv_ip_");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      6, this->recv_ip_(), output);
  }

  // optional string recv_port_ = 7;
  if (this->recv_port_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->recv_port_().data(), this->recv_port_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.recv_port_");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      7, this->recv_port_(), output);
  }

  // optional int32 sockfd_ = 8;
  if (this->sockfd_() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(8, this->sockfd_(), output);
  }

  // @@protoc_insertion_point(serialize_end:Imagine_Rpc.Context)
}

::google::protobuf::uint8* Context::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Imagine_Rpc.Context)
  // optional string service_name_ = 1;
  if (this->service_name_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->service_name_().data(), this->service_name_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.service_name_");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->service_name_(), target);
  }

  // optional string method_name_ = 2;
  if (this->method_name_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->method_name_().data(), this->method_name_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.method_name_");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->method_name_(), target);
  }

  // optional uint64 message_size_ = 3;
  if (this->message_size_() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(3, this->message_size_(), target);
  }

  // optional string send_ip_ = 4;
  if (this->send_ip_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->send_ip_().data(), this->send_ip_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.send_ip_");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->send_ip_(), target);
  }

  // optional string send_port_ = 5;
  if (this->send_port_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->send_port_().data(), this->send_port_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.send_port_");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->send_port_(), target);
  }

  // optional string recv_ip_ = 6;
  if (this->recv_ip_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->recv_ip_().data(), this->recv_ip_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.recv_ip_");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        6, this->recv_ip_(), target);
  }

  // optional string recv_port_ = 7;
  if (this->recv_port_().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->recv_port_().data(), this->recv_port_().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Imagine_Rpc.Context.recv_port_");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->recv_port_(), target);
  }

  // optional int32 sockfd_ = 8;
  if (this->sockfd_() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(8, this->sockfd_(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:Imagine_Rpc.Context)
  return target;
}

int Context::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:Imagine_Rpc.Context)
  int total_size = 0;

  // optional string service_name_ = 1;
  if (this->service_name_().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->service_name_());
  }

  // optional string method_name_ = 2;
  if (this->method_name_().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->method_name_());
  }

  // optional uint64 message_size_ = 3;
  if (this->message_size_() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->message_size_());
  }

  // optional string send_ip_ = 4;
  if (this->send_ip_().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->send_ip_());
  }

  // optional string send_port_ = 5;
  if (this->send_port_().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->send_port_());
  }

  // optional string recv_ip_ = 6;
  if (this->recv_ip_().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->recv_ip_());
  }

  // optional string recv_port_ = 7;
  if (this->recv_port_().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->recv_port_());
  }

  // optional int32 sockfd_ = 8;
  if (this->sockfd_() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->sockfd_());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Context::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Imagine_Rpc.Context)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const Context* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const Context>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Imagine_Rpc.Context)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Imagine_Rpc.Context)
    MergeFrom(*source);
  }
}

void Context::MergeFrom(const Context& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Imagine_Rpc.Context)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.service_name_().size() > 0) {

    service_name__.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.service_name__);
  }
  if (from.method_name_().size() > 0) {

    method_name__.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.method_name__);
  }
  if (from.message_size_() != 0) {
    set_message_size_(from.message_size_());
  }
  if (from.send_ip_().size() > 0) {

    send_ip__.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.send_ip__);
  }
  if (from.send_port_().size() > 0) {

    send_port__.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.send_port__);
  }
  if (from.recv_ip_().size() > 0) {

    recv_ip__.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.recv_ip__);
  }
  if (from.recv_port_().size() > 0) {

    recv_port__.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.recv_port__);
  }
  if (from.sockfd_() != 0) {
    set_sockfd_(from.sockfd_());
  }
}

void Context::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Imagine_Rpc.Context)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Context::CopyFrom(const Context& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Imagine_Rpc.Context)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Context::IsInitialized() const {

  return true;
}

void Context::Swap(Context* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Context::InternalSwap(Context* other) {
  service_name__.Swap(&other->service_name__);
  method_name__.Swap(&other->method_name__);
  std::swap(message_size__, other->message_size__);
  send_ip__.Swap(&other->send_ip__);
  send_port__.Swap(&other->send_port__);
  recv_ip__.Swap(&other->recv_ip__);
  recv_port__.Swap(&other->recv_port__);
  std::swap(sockfd__, other->sockfd__);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Context::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Context_descriptor_;
  metadata.reflection = Context_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Context

// optional string service_name_ = 1;
void Context::clear_service_name_() {
  service_name__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& Context::service_name_() const {
  // @@protoc_insertion_point(field_get:Imagine_Rpc.Context.service_name_)
  return service_name__.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_service_name_(const ::std::string& value) {
  
  service_name__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Imagine_Rpc.Context.service_name_)
}
 void Context::set_service_name_(const char* value) {
  
  service_name__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Imagine_Rpc.Context.service_name_)
}
 void Context::set_service_name_(const char* value, size_t size) {
  
  service_name__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Imagine_Rpc.Context.service_name_)
}
 ::std::string* Context::mutable_service_name_() {
  
  // @@protoc_insertion_point(field_mutable:Imagine_Rpc.Context.service_name_)
  return service_name__.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Context::release_service_name_() {
  // @@protoc_insertion_point(field_release:Imagine_Rpc.Context.service_name_)
  
  return service_name__.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_allocated_service_name_(::std::string* service_name_) {
  if (service_name_ != NULL) {
    
  } else {
    
  }
  service_name__.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), service_name_);
  // @@protoc_insertion_point(field_set_allocated:Imagine_Rpc.Context.service_name_)
}

// optional string method_name_ = 2;
void Context::clear_method_name_() {
  method_name__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& Context::method_name_() const {
  // @@protoc_insertion_point(field_get:Imagine_Rpc.Context.method_name_)
  return method_name__.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_method_name_(const ::std::string& value) {
  
  method_name__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Imagine_Rpc.Context.method_name_)
}
 void Context::set_method_name_(const char* value) {
  
  method_name__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Imagine_Rpc.Context.method_name_)
}
 void Context::set_method_name_(const char* value, size_t size) {
  
  method_name__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Imagine_Rpc.Context.method_name_)
}
 ::std::string* Context::mutable_method_name_() {
  
  // @@protoc_insertion_point(field_mutable:Imagine_Rpc.Context.method_name_)
  return method_name__.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Context::release_method_name_() {
  // @@protoc_insertion_point(field_release:Imagine_Rpc.Context.method_name_)
  
  return method_name__.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_allocated_method_name_(::std::string* method_name_) {
  if (method_name_ != NULL) {
    
  } else {
    
  }
  method_name__.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), method_name_);
  // @@protoc_insertion_point(field_set_allocated:Imagine_Rpc.Context.method_name_)
}

// optional uint64 message_size_ = 3;
void Context::clear_message_size_() {
  message_size__ = GOOGLE_ULONGLONG(0);
}
 ::google::protobuf::uint64 Context::message_size_() const {
  // @@protoc_insertion_point(field_get:Imagine_Rpc.Context.message_size_)
  return message_size__;
}
 void Context::set_message_size_(::google::protobuf::uint64 value) {
  
  message_size__ = value;
  // @@protoc_insertion_point(field_set:Imagine_Rpc.Context.message_size_)
}

// optional string send_ip_ = 4;
void Context::clear_send_ip_() {
  send_ip__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& Context::send_ip_() const {
  // @@protoc_insertion_point(field_get:Imagine_Rpc.Context.send_ip_)
  return send_ip__.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_send_ip_(const ::std::string& value) {
  
  send_ip__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Imagine_Rpc.Context.send_ip_)
}
 void Context::set_send_ip_(const char* value) {
  
  send_ip__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Imagine_Rpc.Context.send_ip_)
}
 void Context::set_send_ip_(const char* value, size_t size) {
  
  send_ip__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Imagine_Rpc.Context.send_ip_)
}
 ::std::string* Context::mutable_send_ip_() {
  
  // @@protoc_insertion_point(field_mutable:Imagine_Rpc.Context.send_ip_)
  return send_ip__.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Context::release_send_ip_() {
  // @@protoc_insertion_point(field_release:Imagine_Rpc.Context.send_ip_)
  
  return send_ip__.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_allocated_send_ip_(::std::string* send_ip_) {
  if (send_ip_ != NULL) {
    
  } else {
    
  }
  send_ip__.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), send_ip_);
  // @@protoc_insertion_point(field_set_allocated:Imagine_Rpc.Context.send_ip_)
}

// optional string send_port_ = 5;
void Context::clear_send_port_() {
  send_port__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& Context::send_port_() const {
  // @@protoc_insertion_point(field_get:Imagine_Rpc.Context.send_port_)
  return send_port__.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_send_port_(const ::std::string& value) {
  
  send_port__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Imagine_Rpc.Context.send_port_)
}
 void Context::set_send_port_(const char* value) {
  
  send_port__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Imagine_Rpc.Context.send_port_)
}
 void Context::set_send_port_(const char* value, size_t size) {
  
  send_port__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Imagine_Rpc.Context.send_port_)
}
 ::std::string* Context::mutable_send_port_() {
  
  // @@protoc_insertion_point(field_mutable:Imagine_Rpc.Context.send_port_)
  return send_port__.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Context::release_send_port_() {
  // @@protoc_insertion_point(field_release:Imagine_Rpc.Context.send_port_)
  
  return send_port__.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_allocated_send_port_(::std::string* send_port_) {
  if (send_port_ != NULL) {
    
  } else {
    
  }
  send_port__.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), send_port_);
  // @@protoc_insertion_point(field_set_allocated:Imagine_Rpc.Context.send_port_)
}

// optional string recv_ip_ = 6;
void Context::clear_recv_ip_() {
  recv_ip__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& Context::recv_ip_() const {
  // @@protoc_insertion_point(field_get:Imagine_Rpc.Context.recv_ip_)
  return recv_ip__.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_recv_ip_(const ::std::string& value) {
  
  recv_ip__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Imagine_Rpc.Context.recv_ip_)
}
 void Context::set_recv_ip_(const char* value) {
  
  recv_ip__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Imagine_Rpc.Context.recv_ip_)
}
 void Context::set_recv_ip_(const char* value, size_t size) {
  
  recv_ip__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Imagine_Rpc.Context.recv_ip_)
}
 ::std::string* Context::mutable_recv_ip_() {
  
  // @@protoc_insertion_point(field_mutable:Imagine_Rpc.Context.recv_ip_)
  return recv_ip__.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Context::release_recv_ip_() {
  // @@protoc_insertion_point(field_release:Imagine_Rpc.Context.recv_ip_)
  
  return recv_ip__.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_allocated_recv_ip_(::std::string* recv_ip_) {
  if (recv_ip_ != NULL) {
    
  } else {
    
  }
  recv_ip__.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), recv_ip_);
  // @@protoc_insertion_point(field_set_allocated:Imagine_Rpc.Context.recv_ip_)
}

// optional string recv_port_ = 7;
void Context::clear_recv_port_() {
  recv_port__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& Context::recv_port_() const {
  // @@protoc_insertion_point(field_get:Imagine_Rpc.Context.recv_port_)
  return recv_port__.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_recv_port_(const ::std::string& value) {
  
  recv_port__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Imagine_Rpc.Context.recv_port_)
}
 void Context::set_recv_port_(const char* value) {
  
  recv_port__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Imagine_Rpc.Context.recv_port_)
}
 void Context::set_recv_port_(const char* value, size_t size) {
  
  recv_port__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Imagine_Rpc.Context.recv_port_)
}
 ::std::string* Context::mutable_recv_port_() {
  
  // @@protoc_insertion_point(field_mutable:Imagine_Rpc.Context.recv_port_)
  return recv_port__.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* Context::release_recv_port_() {
  // @@protoc_insertion_point(field_release:Imagine_Rpc.Context.recv_port_)
  
  return recv_port__.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void Context::set_allocated_recv_port_(::std::string* recv_port_) {
  if (recv_port_ != NULL) {
    
  } else {
    
  }
  recv_port__.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), recv_port_);
  // @@protoc_insertion_point(field_set_allocated:Imagine_Rpc.Context.recv_port_)
}

// optional int32 sockfd_ = 8;
void Context::clear_sockfd_() {
  sockfd__ = 0;
}
 ::google::protobuf::int32 Context::sockfd_() const {
  // @@protoc_insertion_point(field_get:Imagine_Rpc.Context.sockfd_)
  return sockfd__;
}
 void Context::set_sockfd_(::google::protobuf::int32 value) {
  
  sockfd__ = value;
  // @@protoc_insertion_point(field_set:Imagine_Rpc.Context.sockfd_)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Imagine_Rpc

// @@protoc_insertion_point(global_scope)
