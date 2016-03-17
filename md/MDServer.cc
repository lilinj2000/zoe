#include "MDServer.hh"
#include "MDConfig.hh"
#include "MDLog.hh"

#include <cassert>
#include <sstream>

namespace md
{

MDServer::MDServer(MDConfig* config):
    options_(nullptr)
{
  MD_TRACE <<"MDServer::MDServer()";

  options_ = config->mdOptions();

  MD_INFO <<"xsub_addr: " <<options_->xsub_addr;

  pub_service_.reset( zod::PubService::create(options_->xsub_addr, zod::CONNECT) );

  md_service_.reset( cata::MDService::createService(config->cataMDOptions(), this) );
  
  cata::InstrumentSet instrus;
  instrus.insert( options_->instru );
  md_service_->subMarketData( instrus );
}

MDServer::~MDServer()
{
  MD_TRACE <<"MDServer::~MDServer()";
}

void MDServer::onRtnMarketData(const cata::DepthMarketData* data)
{
  MD_TRACE <<"MDServer::onRtnMarketData()";

  std::stringstream ss;
  ss <<*data;

  MD_DEBUG <<"pub msg:\n"
           <<ss.str();

  pub_service_->sendMsg( ss.str() );
}

};
