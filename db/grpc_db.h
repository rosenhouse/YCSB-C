//
//  grpc_db.h
//  Implements the "db" interface by making a connection to a gRPC server
//

#ifndef YCSB_C_GRPC_DB_H_
#define YCSB_C_GRPC_DB_H_


#include <iostream>
#include <string>

#include "core/properties.h"
#include "core/db.h"
#include "kvs.grpc.pb.h"

namespace ycsbc {

class GrpcClient {
  public:
    GrpcClient(std::string& addr);

    void Put(const std::string& key, const std::string& value);
    void Get(const std::string& key, std::string& out_value);

    void Close();

  private:
    std::unique_ptr<kvs::KVS::Stub> stub;
    std::unique_ptr< ::grpc::ClientReaderWriter< ::kvs::PutRequest, ::kvs::PutResponse>> puts;
    std::unique_ptr<::grpc::ClientContext> puts_context;
    std::unique_ptr< ::grpc::ClientReaderWriter< ::kvs::GetRequest, ::kvs::GetResponse>> gets;
    std::unique_ptr<::grpc::ClientContext> gets_context;
    int nonce;
};

class GrpcDB : public DB {
public:
  GrpcDB(utils::Properties &props, bool preloaded);

  void Init();
  void Close();

  int Read(const std::string &table, const std::string &key,
           const std::vector<std::string> *fields,
           std::vector<KVPair> &result);

  int Scan(const std::string &table, const std::string &key,
           int len, const std::vector<std::string> *fields,
           std::vector<std::vector<KVPair>> &result);

  int Update(const std::string &table, const std::string &key,
             std::vector<KVPair> &values);

  int Insert(const std::string &table, const std::string &key,
             std::vector<KVPair> &values);

  int Delete(const std::string &table, const std::string &key);

private:
  // TCP address of the gRPC server to connect to, e.g. localhost:50051
  std::string addr;

  // count of how many threads have been Init(), used to assign thread_local thread_id
  std::atomic_int thread_counter;

  // associate thread_id to a gRPC client dedicated to that thread
  std::map<int, std::unique_ptr<GrpcClient>> clients_map;
};

} // ycsbc

#endif // YCSB_C_GRPC_DB_H_

