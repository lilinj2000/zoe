// Copyright (c) 2010
// All rights reserved.

#include <cassert>
#include <sstream>

#include "Server.hh"
#include "Config.hh"
#include "Log.hh"
#include "json/json.hh"

namespace md {

Server::Server(Config* config):
    options_(nullptr) {
  MD_TRACE <<"Server::Server()";

  options_ = config->mdOptions();

  MD_INFO <<"=== pub_addr: " <<options_->pub_addr;
  pub_service_.reset(zod::PubService::create(options_->pub_addr));
  md_service_.reset(
      cata::MDService::createService(config->cataMDOptions(), this));

  // sub market data by config file
  cata::InstrumentSet instrus;
  for (auto& instru : options_->instrus) {
    instrus.insert(instru);
  }
  subMarketData(instrus);

  MD_INFO <<"=== pull_addr: " <<options_->pull_addr;
  pull_service_.reset(zod::PullService::create(options_->pull_addr, this));
}

Server::~Server() {
  MD_TRACE <<"Server::~Server()";
}

void Server::onRspMessage(const std::string& msg) {
  MD_TRACE <<"Server::onRspMessage()";

  MD_INFO <<msg;
}

void Server::onRtnMessage(const std::string& msg) {
  MD_TRACE <<"Server::onRtnMessage()";

  MD_INFO <<"pub msg:\n"
           <<msg;

  pub_service_->sendMsg(msg);
}

void Server::msgCallback(const zod::Msg* msg) {
  MD_TRACE <<"Server::msgCallback()";

  std::string data((char*)msg->data_.get(), msg->len_);
  MD_INFO <<"md request: \n"
          <<data;

  json::Document doc;
  json::fromString(data, &doc);

  std::string cmd_sub = "SubMarketData";
  std::string cmd_unsub = "UnsubMarketData";
  std::string the_cmd;
  if (doc.HasMember(cmd_sub.data())) {
    the_cmd = cmd_sub;
  } else if (doc.HasMember(cmd_unsub.data())) {
    the_cmd = cmd_unsub;
  }

  if (!the_cmd.empty()) {
    json::Value& req_sub = doc[the_cmd.data()];

    std::string fld_instrus = "Instrus";
    if (req_sub.HasMember(fld_instrus.data())) {
      json::Value& instrus_array = req_sub[fld_instrus.data()];

      if (instrus_array.IsArray()) {
          cata::InstrumentSet instrus;
          for (int i = 0; i < instrus_array.Size(); ++i) {
            instrus.insert(instrus_array[i].GetString());
          }

          if (the_cmd == cmd_sub) {
            subMarketData(instrus);
          } else if (the_cmd == cmd_unsub) {
            unsubMarketData(instrus);
          }
          return;
      }
    }
  }
  
  MD_ERROR <<"Invalid message !!!";
}

void Server::subMarketData(const cata::InstrumentSet& instrus) {
  MD_TRACE <<"Server::subMarketData()";
  
  if (!instrus.empty())
    md_service_->subMarketData(instrus);
}

void Server::unsubMarketData(const cata::InstrumentSet& instrus) {
  MD_TRACE <<"Server::unsubMarketData()";
  
  if (!instrus.empty())
    md_service_->unsubMarketData(instrus);
}

};  // namespace md
