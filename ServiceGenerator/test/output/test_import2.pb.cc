// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test_import2.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "test_import2.pb.h"

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

namespace {

const ::google::protobuf::Descriptor* import2responsemsg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  import2responsemsg_reflection_ = NULL;
const ::google::protobuf::Descriptor* import2requestmsg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  import2requestmsg_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_test_5fimport2_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_test_5fimport2_2eproto() {
  protobuf_AddDesc_test_5fimport2_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "test_import2.proto");
  GOOGLE_CHECK(file != NULL);
  import2responsemsg_descriptor_ = file->message_type(0);
  static const int import2responsemsg_offsets_[1] = {
  };
  import2responsemsg_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      import2responsemsg_descriptor_,
      import2responsemsg::default_instance_,
      import2responsemsg_offsets_,
      -1,
      -1,
      -1,
      sizeof(import2responsemsg),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(import2responsemsg, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(import2responsemsg, _is_default_instance_));
  import2requestmsg_descriptor_ = file->message_type(1);
  static const int import2requestmsg_offsets_[1] = {
  };
  import2requestmsg_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      import2requestmsg_descriptor_,
      import2requestmsg::default_instance_,
      import2requestmsg_offsets_,
      -1,
      -1,
      -1,
      sizeof(import2requestmsg),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(import2requestmsg, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(import2requestmsg, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_test_5fimport2_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      import2responsemsg_descriptor_, &import2responsemsg::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      import2requestmsg_descriptor_, &import2requestmsg::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_test_5fimport2_2eproto() {
  delete import2responsemsg::default_instance_;
  delete import2responsemsg_reflection_;
  delete import2requestmsg::default_instance_;
  delete import2requestmsg_reflection_;
}

void protobuf_AddDesc_test_5fimport2_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_test_5fimport2_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022test_import2.proto\"\024\n\022import2responsem"
    "sg\"\023\n\021import2requestmsgb\006proto3", 71);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "test_import2.proto", &protobuf_RegisterTypes);
  import2responsemsg::default_instance_ = new import2responsemsg();
  import2requestmsg::default_instance_ = new import2requestmsg();
  import2responsemsg::default_instance_->InitAsDefaultInstance();
  import2requestmsg::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_test_5fimport2_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_test_5fimport2_2eproto {
  StaticDescriptorInitializer_test_5fimport2_2eproto() {
    protobuf_AddDesc_test_5fimport2_2eproto();
  }
} static_descriptor_initializer_test_5fimport2_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

import2responsemsg::import2responsemsg()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:import2responsemsg)
}

void import2responsemsg::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

import2responsemsg::import2responsemsg(const import2responsemsg& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:import2responsemsg)
}

void import2responsemsg::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
}

import2responsemsg::~import2responsemsg() {
  // @@protoc_insertion_point(destructor:import2responsemsg)
  SharedDtor();
}

void import2responsemsg::SharedDtor() {
  if (this != default_instance_) {
  }
}

void import2responsemsg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* import2responsemsg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return import2responsemsg_descriptor_;
}

const import2responsemsg& import2responsemsg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_test_5fimport2_2eproto();
  return *default_instance_;
}

import2responsemsg* import2responsemsg::default_instance_ = NULL;

import2responsemsg* import2responsemsg::New(::google::protobuf::Arena* arena) const {
  import2responsemsg* n = new import2responsemsg;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void import2responsemsg::Clear() {
// @@protoc_insertion_point(message_clear_start:import2responsemsg)
}

bool import2responsemsg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:import2responsemsg)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0 ||
        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
  }
success:
  // @@protoc_insertion_point(parse_success:import2responsemsg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:import2responsemsg)
  return false;
#undef DO_
}

void import2responsemsg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:import2responsemsg)
  // @@protoc_insertion_point(serialize_end:import2responsemsg)
}

::google::protobuf::uint8* import2responsemsg::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:import2responsemsg)
  // @@protoc_insertion_point(serialize_to_array_end:import2responsemsg)
  return target;
}

int import2responsemsg::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:import2responsemsg)
  int total_size = 0;

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void import2responsemsg::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:import2responsemsg)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const import2responsemsg* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const import2responsemsg>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:import2responsemsg)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:import2responsemsg)
    MergeFrom(*source);
  }
}

void import2responsemsg::MergeFrom(const import2responsemsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:import2responsemsg)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
}

void import2responsemsg::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:import2responsemsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void import2responsemsg::CopyFrom(const import2responsemsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:import2responsemsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool import2responsemsg::IsInitialized() const {

  return true;
}

void import2responsemsg::Swap(import2responsemsg* other) {
  if (other == this) return;
  InternalSwap(other);
}
void import2responsemsg::InternalSwap(import2responsemsg* other) {
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata import2responsemsg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = import2responsemsg_descriptor_;
  metadata.reflection = import2responsemsg_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// import2responsemsg

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

import2requestmsg::import2requestmsg()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:import2requestmsg)
}

void import2requestmsg::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

import2requestmsg::import2requestmsg(const import2requestmsg& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:import2requestmsg)
}

void import2requestmsg::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
}

import2requestmsg::~import2requestmsg() {
  // @@protoc_insertion_point(destructor:import2requestmsg)
  SharedDtor();
}

void import2requestmsg::SharedDtor() {
  if (this != default_instance_) {
  }
}

void import2requestmsg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* import2requestmsg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return import2requestmsg_descriptor_;
}

const import2requestmsg& import2requestmsg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_test_5fimport2_2eproto();
  return *default_instance_;
}

import2requestmsg* import2requestmsg::default_instance_ = NULL;

import2requestmsg* import2requestmsg::New(::google::protobuf::Arena* arena) const {
  import2requestmsg* n = new import2requestmsg;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void import2requestmsg::Clear() {
// @@protoc_insertion_point(message_clear_start:import2requestmsg)
}

bool import2requestmsg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:import2requestmsg)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0 ||
        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
  }
success:
  // @@protoc_insertion_point(parse_success:import2requestmsg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:import2requestmsg)
  return false;
#undef DO_
}

void import2requestmsg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:import2requestmsg)
  // @@protoc_insertion_point(serialize_end:import2requestmsg)
}

::google::protobuf::uint8* import2requestmsg::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:import2requestmsg)
  // @@protoc_insertion_point(serialize_to_array_end:import2requestmsg)
  return target;
}

int import2requestmsg::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:import2requestmsg)
  int total_size = 0;

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void import2requestmsg::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:import2requestmsg)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const import2requestmsg* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const import2requestmsg>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:import2requestmsg)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:import2requestmsg)
    MergeFrom(*source);
  }
}

void import2requestmsg::MergeFrom(const import2requestmsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:import2requestmsg)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
}

void import2requestmsg::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:import2requestmsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void import2requestmsg::CopyFrom(const import2requestmsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:import2requestmsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool import2requestmsg::IsInitialized() const {

  return true;
}

void import2requestmsg::Swap(import2requestmsg* other) {
  if (other == this) return;
  InternalSwap(other);
}
void import2requestmsg::InternalSwap(import2requestmsg* other) {
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata import2requestmsg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = import2requestmsg_descriptor_;
  metadata.reflection = import2requestmsg_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// import2requestmsg

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
