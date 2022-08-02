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

class GrpcDB : public DB {
public:
  GrpcDB(utils::Properties &props, bool preloaded);
  ~GrpcDB();

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
  std::string server_address;
  std::atomic_int thread_counter;
  std::map<int, std::unique_ptr<kvs::KVS::Stub>> clients_map;
};

static thread_local int thread_id = 0;

} // ycsbc

#endif // YCSB_C_GRPC_DB_H_

