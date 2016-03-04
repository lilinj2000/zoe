#ifndef DB_SERVER_HH
#define DB_SERVER_HH

#include "sqlite3.h"
#include "soil/MsgQueue.hh"

namespace db
{

class DBOptions;
class MsgCallback;

class DBServer
{
 public:
  DBServer(DBOptions* options);

  virtual ~DBServer();

 protected:

  void run();

  void processMsg(const std::string& msg);
  
 private:

  friend class MsgCallback;

  DBOptions* options_;

  sqlite3* db_;
  
  void* context_;
  void* sub_;

  std::unique_ptr<MsgCallback> callback_;
  std::unique_ptr<soil::MsgQueue<std::string, MsgCallback> > msg_queue_;

  std::set<size_t> instrus_hash_;
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
