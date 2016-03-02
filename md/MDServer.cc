#include "MDServer.hh"
#include "MDConfig.hh"
#include "MDLog.hh"

#include "zmq.h"
#include <cassert>

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

}

};
