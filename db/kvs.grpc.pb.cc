// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: kvs.proto

#include "kvs.pb.h"
#include "kvs.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace kvs {

static const char* KVS_method_names[] = {
  "/kvs.KVS/Put",
  "/kvs.KVS/Get",
};

std::unique_ptr< KVS::Stub> KVS::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< KVS::Stub> stub(new KVS::Stub(channel));
  return stub;
}

KVS::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Put_(KVS_method_names[0], ::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  , rpcmethod_Get_(KVS_method_names[1], ::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::kvs::PutRequest, ::kvs::PutResponse>* KVS::Stub::PutRaw(::grpc::ClientContext* context) {
  return ::grpc_impl::internal::ClientReaderWriterFactory< ::kvs::PutRequest, ::kvs::PutResponse>::Create(channel_.get(), rpcmethod_Put_, context);
}

void KVS::Stub::experimental_async::Put(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::kvs::PutRequest,::kvs::PutResponse>* reactor) {
  ::grpc_impl::internal::ClientCallbackReaderWriterFactory< ::kvs::PutRequest,::kvs::PutResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_Put_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::kvs::PutRequest, ::kvs::PutResponse>* KVS::Stub::AsyncPutRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc_impl::internal::ClientAsyncReaderWriterFactory< ::kvs::PutRequest, ::kvs::PutResponse>::Create(channel_.get(), cq, rpcmethod_Put_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::kvs::PutRequest, ::kvs::PutResponse>* KVS::Stub::PrepareAsyncPutRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncReaderWriterFactory< ::kvs::PutRequest, ::kvs::PutResponse>::Create(channel_.get(), cq, rpcmethod_Put_, context, false, nullptr);
}

::grpc::ClientReaderWriter< ::kvs::GetRequest, ::kvs::GetResponse>* KVS::Stub::GetRaw(::grpc::ClientContext* context) {
  return ::grpc_impl::internal::ClientReaderWriterFactory< ::kvs::GetRequest, ::kvs::GetResponse>::Create(channel_.get(), rpcmethod_Get_, context);
}

void KVS::Stub::experimental_async::Get(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::kvs::GetRequest,::kvs::GetResponse>* reactor) {
  ::grpc_impl::internal::ClientCallbackReaderWriterFactory< ::kvs::GetRequest,::kvs::GetResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_Get_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::kvs::GetRequest, ::kvs::GetResponse>* KVS::Stub::AsyncGetRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc_impl::internal::ClientAsyncReaderWriterFactory< ::kvs::GetRequest, ::kvs::GetResponse>::Create(channel_.get(), cq, rpcmethod_Get_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::kvs::GetRequest, ::kvs::GetResponse>* KVS::Stub::PrepareAsyncGetRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncReaderWriterFactory< ::kvs::GetRequest, ::kvs::GetResponse>::Create(channel_.get(), cq, rpcmethod_Get_, context, false, nullptr);
}

KVS::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KVS_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< KVS::Service, ::kvs::PutRequest, ::kvs::PutResponse>(
          [](KVS::Service* service,
             ::grpc_impl::ServerContext* ctx,
             ::grpc_impl::ServerReaderWriter<::kvs::PutResponse,
             ::kvs::PutRequest>* stream) {
               return service->Put(ctx, stream);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KVS_method_names[1],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< KVS::Service, ::kvs::GetRequest, ::kvs::GetResponse>(
          [](KVS::Service* service,
             ::grpc_impl::ServerContext* ctx,
             ::grpc_impl::ServerReaderWriter<::kvs::GetResponse,
             ::kvs::GetRequest>* stream) {
               return service->Get(ctx, stream);
             }, this)));
}

KVS::Service::~Service() {
}

::grpc::Status KVS::Service::Put(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::kvs::PutResponse, ::kvs::PutRequest>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status KVS::Service::Get(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::kvs::GetResponse, ::kvs::GetRequest>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace kvs

