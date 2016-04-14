#ifndef MD_SERVER_HH
#define MD_SERVER_HH

#include "cata/MDService.hh"
#include "zod/PubService.hh"

namespace md
{

class Options;
class Config;

class Server : public cata::ServiceCallback
{
 public:
  Server(Config* config);

  virtual ~Server();

  virtual void onRspMessage(const std::string& msg);

  virtual void onRtnMessage(const std::string& msg);

 private:
  Options* options_;
  
  std::unique_ptr<zod::PubService> pub_service_;
  std::unique_ptr<cata::MDService> md_service_;
};


};

#endif
