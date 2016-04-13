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

  pub_service_.reset(zod::PubService::create(options_->xsub_addr));
  md_service_.reset(cata::MDService::createService(config->cataMDOptions(), this));
  
  cata::InstrumentSet instrus;
  instrus.insert( options_->instru );
  md_service_->subMarketData( instrus );
}

MDServer::~MDServer()
{
  MD_TRACE <<"MDServer::~MDServer()";
}

void MDServer::onRspMessage(const std::string& msg)
{
  MD_TRACE <<"MDServer::onRspMessage()";

  MD_INFO <<msg;
}

void MDServer::onRtnMessage(const std::string& msg)
{
  MD_TRACE <<"MDServer::onRtnMessage()";

  MD_INFO <<"pub msg:\n"
           <<msg;

  pub_service_->sendMsg(msg);
}

};
