// Copyright (c) 2010
// All rights reserved.

#ifndef MD_SERVER_HH
#define MD_SERVER_HH

#include <string>
#include "cata/MDService.hh"
#include "zod/PubService.hh"
#include "zod/PullService.hh"

namespace md {

class Options;
class Config;

class Server : public cata::ServiceCallback, public zod::MsgCallback {
 public:
  explicit Server(Config* config);

  virtual ~Server();

  virtual void onRspMessage(const std::string& msg);

  virtual void onRtnMessage(const std::string& msg);

  virtual void msgCallback(const zod::Msg*);

 protected:
  void subMarketData(const cata::InstrumentSet&);

  void unsubMarketData(const cata::InstrumentSet&);
  
 private:
  Options* options_;

  std::unique_ptr<zod::PubService> pub_service_;
  std::unique_ptr<cata::MDService> md_service_;
  std::unique_ptr<zod::PullService> pull_service_;
};


};  // namespace md

#endif
