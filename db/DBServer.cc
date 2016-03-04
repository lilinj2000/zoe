#include "DBServer.hh"
#include "DBConfig.hh"
#include "DBLog.hh"

#include "zmq.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <cassert>
#include <functional>

namespace db
{

DBServer::DBServer(DBOptions* options):
    options_(options),
    context_(nullptr),
    sub_(nullptr),
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

  callback_.reset( new MsgCallback(this) );
  msg_queue_.reset(new soil::MsgQueue<std::string, MsgCallback>(callback_.get()) );
  
  context_ = zmq_ctx_new();
  assert( context_ );
  
  sub_ = zmq_socket(context_, ZMQ_SUB);
  assert( sub_ );
  
  DB_INFO <<"xpub_addr: " <<options_->xpub_addr;
  if( zmq_connect(sub_, options_->xpub_addr.data())<0 )
  {
    std::string err = "connect xpub failed.\n";
    throw std::runtime_error( err+zmq_strerror(zmq_errno()) );
  }

  if( zmq_setsockopt(sub_, ZMQ_SUBSCRIBE, "", 0)<0 )
  {
    std::string err = "set subscribe options failed.\n";
    throw std::runtime_error( err+zmq_strerror(zmq_errno()) );
  }

  run();
}

DBServer::~DBServer()
{
  DB_TRACE <<"DBServer::~DBServer()";
  
  zmq_close( sub_ );
  
  zmq_ctx_destroy( context_ );

  sqlite3_close( db_ );

}

void DBServer::run()
{
  DB_TRACE <<"DBServer::run()";

  do
  {
    zmq_msg_t msg;
    zmq_msg_init( &msg );

    if( zmq_msg_recv(&msg, sub_, 0)<0 )
    {
      DB_ERROR <<"recv msg failed.\n"
                 <<zmq_strerror(zmq_errno());
    }
    else
    {
      DB_DEBUG <<"recv msg ...";

      msg_queue_->pushMsg( new std::string((char*)zmq_msg_data(&msg)) );
    }

    zmq_msg_close( &msg );
    
  }while( true );
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
    // just do insert table
    return ;
  }

  // instrus_hash_.insert( str_hash(tbl_name) );
  std::string create_sql = "CREATE TABLE ";
  create_sql += tbl_name ;
  create_sql += "( "
      "TradingDay varchar(10), "
      "InstrumentID varchar(10), "
      "ExchangeID varchar(10), "
      "ExchangeInstID varchar(10), "
      "LastPrice double, "
      "PreSettlementPrice double, "
      "PreClosePrice double, "
      "PreOpenInterest double, "
      "OpenPrice double, "
      "HighestPrice double, "
      "LowestPrice double, "
      "Volume int, "
      "Turnover int, "
      "OpenInterest double, "
      "ClosePrice double, "
      "SettlementPrice double, "
      "UpperLimitPrice double, "
      "LowerLimitPrice double, "
      "PreDelta double, "
      "CurrDelta double, "
      "UpdateTime varchar(10), "
      "UpdateMillisec int, "
      "BidPrice1 double, "
      "BidVolume1 double, "
      "AskPrice1 double, "
      "AskVolume1 double, "
      "BidPrice2 double, "
      "BidVolume2 double, "
      "AskPrice2 double, "
      "AskVolume2 double, "
      "BidPrice3 double, "
      "BidVolume3 double, "
      "AskPrice3 double, "
      "AskVolume3 double, "
      "BidPrice4 double, "
      "BidVolume4 double, "
      "AskPrice4 double, "
      "AskVolume4 double, "
      "BidPrice5 double, "
      "BidVolume5 double, "
      "AskPrice5 double, "
      "AskVolume5 double, "
      "AveragePrice double, "
      "ActionDay varchar(10), "
      "time_stamp varchar(50) );";

  DB_INFO <<create_sql;

  json::StringBuffer buf;
  json::Writer<json::StringBuffer> writer( buf );

  doc.Accept( writer );

  DB_INFO <<buf.GetString();
}

};
