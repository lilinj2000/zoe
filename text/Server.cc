// Copyright (c) 2010
// All rights reserved.

#include <cassert>

#include "Server.hh"
#include "Config.hh"
#include "Log.hh"

namespace text {

Server::Server(Options* options):
    options_(options) {
  TEXT_TRACE <<"Server::Server()";

  text_file_.reset( new soil::DataFile(options_->text_file) );

  TEXT_INFO <<"=== proxy addr - " <<options_->proxy_addr;
  sub_service_.reset(zod::SubService::create(options_->proxy_addr, this));
}

Server::~Server() {
  TEXT_TRACE <<"Server::~Server()";
}

void Server::msgCallback(const zod::Msg* msg) {
  TEXT_TRACE <<"Server::msgCallback()";

  std::string data(reinterpret_cast<const char*>(msg->data_.get()),
               msg->len_);
  data.push_back('\n');

  text_file_->putData( new MData(data) );
}

};  // namespace text
