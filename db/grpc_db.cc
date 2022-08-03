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
  // slice key_slice = slice_create(key.size(), key.c_str());
  // slice val_slice = slice_create(val.size(), val.c_str());

  return DB::kOK;
}

int GrpcDB::Delete(const string &table, const string &key) {

  return DB::kOK;
}


GrpcClient::GrpcClient(std::string& addr) {
    auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    this->stub = kvs::KVS::NewStub(channel);
}

} // ycsbc
