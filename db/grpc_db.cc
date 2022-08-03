//
//  grpc_db.cc
//  Implements the "db" interface by making a connection to a gRPC server
//
//  Created by Gabriel Rosenhouse on 8/1/2022.
//  Copyright (c) 2022 VMware.
//

#include <string>
#include <vector>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "grpc_db.h"

using std::string;
using std::vector;

namespace ycsbc {

GrpcDB::GrpcDB(utils::Properties &props, bool preloaded) {
  this->addr = props.GetProperty("grpc.addr");
  std::cerr << "# Will connect to gRPC server at " << this->addr << std::endl;
}

// used to retreive the thread-exclusive GrpcClient for a given GrpcDB
static thread_local int thread_id = 0;

void GrpcDB::Init()
{
  thread_id = this->thread_counter++;
  this->clients_map[thread_id] = std::make_unique<GrpcClient>(GrpcClient(addr));
}

void GrpcDB::Close()
{
  this->clients_map.erase(thread_id);
}

int GrpcDB::Read(const string &table,
                     const string &key,
                     const vector<string> *fields,
                     vector<KVPair> &result) {
  this->clients_map[thread_id]->Get(key, result[0].second);
  return DB::kOK;
}

int GrpcDB::Scan(const string &table,
                     const string &key, int len,
                     const vector<string> *fields,
                     vector<vector<KVPair>> &result) {
  assert(fields == NULL);

  return DB::kOK;
}

int GrpcDB::Update(const string &table,
                       const string &key,
                       vector<KVPair> &values) {
  return Insert(table, key, values);
}

int GrpcDB::Insert(const string &table, const string &key, vector<KVPair> &values) {
  assert(values.size() == 1);

  std::string val = values[0].second;
  this->clients_map[thread_id]->Put(key, val);

  return DB::kOK;
}

int GrpcDB::Delete(const string &table, const string &key) {

  return DB::kOK;
}


GrpcClient::GrpcClient(std::string& addr) {
    auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    this->stub = kvs::KVS::NewStub(channel);
    this->puts_context = std::unique_ptr<grpc::ClientContext>(new grpc::ClientContext());
    this->puts = this->stub->Put(puts_context.get());
    this->gets_context = std::unique_ptr<grpc::ClientContext>(new grpc::ClientContext());
    this->gets = this->stub->Get(gets_context.get());
}

void GrpcClient::Close() {
  this->puts->WritesDone();
  this->puts->Finish();
  this->puts_context->TryCancel();
  this->gets->WritesDone();
  this->gets->Finish();
  this->gets_context->TryCancel();
}

void GrpcClient::Get(const std::string& key, std::string& out_value) {
  kvs::GetRequest req;
  req.set_key(key);
  req.set_nonce(this->nonce++);
  bool success = this->gets->Write(req);
  if (!success) {
    auto status = this->gets->Finish();
    assert(!status.ok()); // we only got here because of a write failure!
    std::cerr << "sending a get request failed:" << std::endl;
    std::cerr << status.error_message() << std::endl;
    assert(false);
  }

  kvs::GetResponse resp;
  success = this->gets->Read(&resp);
  if (!success) {
    auto status = this->gets->Finish();
    assert(!status.ok()); // we only got here because of a read failure!
    std::cerr << "receiving the get confirmation failed:" << std::endl;
    std::cerr << status.error_message() << std::endl;
    assert(false);
  }
}

void GrpcClient::Put(const std::string& key, const std::string& value) {
  kvs::PutRequest req;
  req.set_key(key);
  req.set_value(value);
  req.set_nonce(this->nonce++);
  bool success = this->puts->Write(req);
  if (!success) {
    auto status = this->puts->Finish();
    assert(!status.ok()); // we only got here because of a write failure!
    std::cerr << "sending a put request failed:" << std::endl;
    std::cerr << status.error_message() << std::endl;
    assert(false);
  }

  kvs::PutResponse resp;
  success = this->puts->Read(&resp);
  if (!success) {
    auto status = this->puts->Finish();
    assert(!status.ok()); // we only got here because of a read failure!
    std::cerr << "receiving the put confirmation failed:" << std::endl;
    std::cerr << status.error_message() << std::endl;
    assert(false);
  }
}

} // ycsbc
