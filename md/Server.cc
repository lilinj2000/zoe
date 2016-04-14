#include "Server.hh"
#include "Config.hh"
#include "Log.hh"

#include <cassert>
#include <sstream>

namespace md
{

Server::Server(Config* config):
    options_(nullptr)
{
  MD_TRACE <<"Server::Server()";

  options_ = config->mdOptions();

  MD_INFO <<"proxy_addr: " <<options_->proxy_addr;

  pub_service_.reset(zod::PubService::create(options_->proxy_addr));
  md_service_.reset(cata::MDService::createService(config->cataMDOptions(), this));
  
  cata::InstrumentSet instrus;
  for (auto& instru : options_->instrus) {
    instrus.insert(instru);
  }
  md_service_->subMarketData( instrus );
}

Server::~Server()
{
  MD_TRACE <<"Server::~Server()";
}

void Server::onRspMessage(const std::string& msg)
{
  MD_TRACE <<"Server::onRspMessage()";

  MD_INFO <<msg;
}

void Server::onRtnMessage(const std::string& msg)
{
  MD_TRACE <<"Server::onRtnMessage()";

  MD_INFO <<"pub msg:\n"
           <<msg;

  pub_service_->sendMsg(msg);
}

};
