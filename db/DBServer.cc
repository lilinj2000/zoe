#include "DBServer.hh"
#include "DBConfig.hh"
#include "DBLog.hh"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <cassert>
#include <functional>

namespace db
{

DBServer::DBServer(DBOptions* options):
    options_(options),
    db_(nullptr)
{
  DB_TRACE <<"DBServer::DBServer()";

  // open the database
  int rc = sqlite3_open(options_->db_file.data(), &db_);
  if( rc )
  {
    std::string err = "can not open the database:";
    err += options_->db_file + "\n";
    throw std::runtime_error( err+sqlite3_errmsg(db_) );
  }

  callback_.reset( new db::MsgCallback(this) );
  
  msg_queue_.reset(new soil::MsgQueue<std::string, db::MsgCallback>(callback_.get()) );

  DB_INFO <<"xpub_addr: " <<options_->xpub_addr;
  sub_service_.reset( zod::SubService::create(options_->xpub_addr, this) );
}

DBServer::~DBServer()
{
  DB_TRACE <<"DBServer::~DBServer()";
  
  for(InsertSqlMap::iterator itr=insert_sqls_.begin();
      itr!=insert_sqls_.end(); ++itr)
  {
    sqlite3_finalize( itr->second );
  }

  sqlite3_close( db_ );

}

void DBServer::msgCallback(const zod::Msg* msg)
{
  std::string data( (char*)msg->data_.get() );
  
  msg_queue_->pushMsg( new std::string(data) );
}

void DBServer::processMsg(const std::string& msg)
{
  DB_TRACE <<"DBServer::processMsg()";

  namespace json=rapidjson;
  json::Document doc;
  doc.Parse( msg.data() );

  json::Value& mdata = doc["DepthMarketDataField"];

  json::Value& tradingDay = mdata["TradingDay"];
  json::Value& instruID = mdata["InstrumentID"];
  
  DB_INFO <<"InstrumentID: " <<instruID.GetString() <<" "
          <<"TradingDay: " <<tradingDay.GetString() ;

  std::string tbl_name = instruID.GetString();
  tbl_name += "_";
  tbl_name += tradingDay.GetString();
  
  std::hash<std::string> str_hash;

  if( instrus_hash_.count(str_hash(tbl_name)) )
  {
    insertData(tbl_name, mdata);
    
    return ;
  }

  createTable(tbl_name, mdata);

  instrus_hash_.insert( str_hash(tbl_name) );

  insertData(tbl_name, mdata);

}

void DBServer::createTable(const std::string& tbl_name, rapidjson::Value& mdata)
{
  DB_TRACE <<"DBServer::createTable()";

  std::string create_table_sql = "CREATE TABLE IF NOT EXISTS " + tbl_name + " (";

  for (rapidjson::Value::ConstMemberIterator itr = mdata.MemberBegin();
       itr != mdata.MemberEnd(); ++itr)
  {
    create_table_sql += itr->name.GetString();
    create_table_sql += " varchar(50)";

    if( itr+1==mdata.MemberEnd() )
    {
      create_table_sql += ");";
    }
    else
    {
      create_table_sql += ",";
    }
  }

  DB_INFO <<create_table_sql;


  char* err_msg = 0;
  int rc = sqlite3_exec(db_, create_table_sql.data(), 0, 0, &err_msg);

  if( rc!=SQLITE_OK )
  {
    std::string err = "create table failed.\n";
    err += "SQL ERROR: ";
    err += err_msg;

    sqlite3_free(err_msg);

    throw std::runtime_error( err );
  }
  
}

void DBServer::insertData(const std::string& tbl_name, rapidjson::Value& mdata)
{
  DB_TRACE <<"DBServer::insertData()";

  std::hash<std::string> str_hash;

  sqlite3_stmt *insert_stmt = 0;

  InsertSqlMap::iterator itr = insert_sqls_.find( str_hash(tbl_name) );
  if( itr==insert_sqls_.end() )
  {
    std::string insert_table_sql = "INSERT INTO " + tbl_name + " VALUES(";
    
    for (rapidjson::Value::ConstMemberIterator itr = mdata.MemberBegin();
         itr != mdata.MemberEnd(); ++itr)
    {
      insert_table_sql += "@";
      insert_table_sql += itr->name.GetString();

      if( itr+1==mdata.MemberEnd() )
      {
        insert_table_sql += ");";
      }
      else
      {
        insert_table_sql += ",";
      }
    }

    DB_INFO <<insert_table_sql;

    char *err_msg = 0;
    sqlite3_stmt *res;
  
    int rc = sqlite3_prepare_v2(db_, insert_table_sql.data(), -1, &res, 0);

    if( rc!=SQLITE_OK )
    {
      std::string err_msg = "Failed to insert table.\n";
      err_msg += "SQL ERROR: ";
      err_msg += sqlite3_errmsg(db_);

      throw std::runtime_error(err_msg);
    }

    insert_sqls_[str_hash(tbl_name)] = res;

    insert_stmt = res;
  }
  else
  {
    insert_stmt = itr->second;
  }

  assert( insert_stmt );

  sqlite3_reset( insert_stmt );
  
  for (rapidjson::Value::ConstMemberIterator itr = mdata.MemberBegin();
       itr != mdata.MemberEnd(); ++itr)
  {
    std::string name = "@";
    name += itr->name.GetString();
    int idx = sqlite3_bind_parameter_index(insert_stmt, name.data());
    std::string value(itr->value.GetString());
    
    // DB_DEBUG <<"idx: " <<idx <<" name: " <<name
    //          <<" value: " <<value;
    int rc = sqlite3_bind_text(insert_stmt, idx, value.data(), value.length(), SQLITE_TRANSIENT);
    if( rc!=SQLITE_OK )
    {
      std::string err_msg = "Failed to bind data.\n";
      err_msg += "SQL ERROR: ";
      err_msg += sqlite3_errmsg(db_);

      throw std::runtime_error(err_msg);
    }

  }

  int rc = sqlite3_step( insert_stmt );
  if( rc!=SQLITE_DONE )
  {
    std::string err_msg = "Failed to insert data into table.\n";
    err_msg += "SQL ERROR: ";
    err_msg += sqlite3_errmsg(db_);

    throw std::runtime_error(err_msg);
  }
  
}

};
