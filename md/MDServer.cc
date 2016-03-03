#include "MDServer.hh"
#include "MDConfig.hh"
#include "MDLog.hh"

#include "zmq.h"
#include <cassert>
#include <sstream>

namespace md
{

MDServer::MDServer(MDConfig* config):
    options_(nullptr),
    context_(nullptr),
    pub_(nullptr)
{
  MD_TRACE <<"MDServer::MDServer()";

  context_ = zmq_ctx_new();
  assert( context_ );
  
  pub_ = zmq_socket(context_, ZMQ_PUB);
  assert( pub_ );

  options_ = config->mdOptions();

  MD_INFO <<"xsub_addr: " <<options_->xsub_addr;
  if( zmq_connect(pub_, options_->xsub_addr.data())<0 )
  {
    std::string err = "connect xsub failed.\n";
    throw std::runtime_error( err+zmq_strerror(zmq_errno()) );
  }


  md_service_.reset( cata::MDService::createService(config->cataMDOptions(), this) );
  
  cata::InstrumentSet instrus;
  instrus.insert( options_->instru );
  md_service_->subMarketData( instrus );
}

MDServer::~MDServer()
{
  MD_TRACE <<"MDServer::~MDServer()";
  
  zmq_close( pub_ );

  zmq_ctx_destroy( context_ );
}

void MDServer::onRtnMarketData(const cata::DepthMarketData* data)
{
  MD_TRACE <<"MDServer::onRtnMarketData()";

  std::stringstream ss;
  ss <<*data;

  MD_DEBUG <<"pub msg:\n"
           <<ss.str();
  
  zmq_msg_t msg;
  zmq_msg_init_size(&msg, ss.str().length()+1);

  memset(zmq_msg_data(&msg), 0x0, ss.str().length()+1);
  memcpy(zmq_msg_data(&msg), ss.str().data(), ss.str().length());

  if( zmq_msg_send(&msg, pub_, 0)<0 )
  {
    zmq_msg_close(&msg);

    MD_ERROR <<"msg send failed.\n"
             <<zmq_strerror(zmq_errno());
  }

}

};
