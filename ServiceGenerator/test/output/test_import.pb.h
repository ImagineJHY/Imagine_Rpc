// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test_import.proto

#ifndef PROTOBUF_test_5fimport_2eproto__INCLUDED
#define PROTOBUF_test_5fimport_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace import_package {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_test_5fimport_2eproto();
void protobuf_AssignDesc_test_5fimport_2eproto();
void protobuf_ShutdownFile_test_5fimport_2eproto();

class request_msg;
class response_msg;

// ===================================================================

class response_msg : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:import_package.response_msg) */ {
 public:
  response_msg();
  virtual ~response_msg();

  response_msg(const response_msg& from);

  inline response_msg& operator=(const response_msg& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const response_msg& default_instance();

  void Swap(response_msg* other);

  // implements Message ----------------------------------------------

  inline response_msg* New() const { return New(NULL); }

  response_msg* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const response_msg& from);
  void MergeFrom(const response_msg& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(response_msg* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:import_package.response_msg)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_test_5fimport_2eproto();
  friend void protobuf_AssignDesc_test_5fimport_2eproto();
  friend void protobuf_ShutdownFile_test_5fimport_2eproto();

  void InitAsDefaultInstance();
  static response_msg* default_instance_;
};
// -------------------------------------------------------------------

class request_msg : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:import_package.request_msg) */ {
 public:
  request_msg();
  virtual ~request_msg();

  request_msg(const request_msg& from);

  inline request_msg& operator=(const request_msg& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const request_msg& default_instance();

  void Swap(request_msg* other);

  // implements Message ----------------------------------------------

  inline request_msg* New() const { return New(NULL); }

  request_msg* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const request_msg& from);
  void MergeFrom(const request_msg& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(request_msg* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:import_package.request_msg)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_test_5fimport_2eproto();
  friend void protobuf_AssignDesc_test_5fimport_2eproto();
  friend void protobuf_ShutdownFile_test_5fimport_2eproto();

  void InitAsDefaultInstance();
  static request_msg* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// response_msg

// -------------------------------------------------------------------

// request_msg

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace import_package

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_5fimport_2eproto__INCLUDED
