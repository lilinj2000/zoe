#ifndef DB_SERVER_HH
#define DB_SERVER_HH

#include "sqlite3.h"
#include "soil/MsgQueue.hh"
#include "rapidjson/document.h"

#include "zod/SubService.hh"

#include <set>
#include <map>

namespace db
{

class DBOptions;
class MsgCallback;

class DBServer : public zod::MsgCallback
{
 public:
  DBServer(DBOptions* options);

  virtual ~DBServer();

  virtual void msgCallback(const zod::Msg*);

 protected:

  void processMsg(const std::string& msg);

  void createTable(const std::string& tbl_name, rapidjson::Value& mdata);

  void insertData(const std::string& tbl_name, rapidjson::Value& mdata);
  
 private:

  friend class db::MsgCallback;

  DBOptions* options_;

  sqlite3* db_;
  
  std::unique_ptr<zod::SubService> sub_service_;
  
  std::unique_ptr<db::MsgCallback> callback_;
  std::unique_ptr<soil::MsgQueue<std::string, db::MsgCallback> > msg_queue_;

  std::set<size_t> instrus_hash_;

  typedef std::map<size_t, sqlite3_stmt*> InsertSqlMap;
  InsertSqlMap insert_sqls_;
};

class MsgCallback
{
 public:
  MsgCallback(DBServer* server):
      server_(server)
  {
  }

  ~MsgCallback()
  {
  }

  void msgCallback(const std::string* msg)
  {
    server_->processMsg( *msg );
  }

 private:

  DBServer* server_;
};


};

#endif
