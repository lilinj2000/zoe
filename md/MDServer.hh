#ifndef MD_SERVER_HH
#define MD_SERVER_HH

#include "cata/MDService.hh"
#include "zod/PubService.hh"

namespace md
{

class MDOptions;
class MDConfig;

class MDServer : public cata::ServiceCallback
{
 public:
  MDServer(MDConfig* config);

  virtual ~MDServer();

  virtual void onRspMessage(const std::string& msg);

  virtual void onRtnMessage(const std::string& msg);

 private:

  MDOptions* options_;

  std::unique_ptr<cata::MDService> md_service_;

  std::unique_ptr<zod::PubService> pub_service_;
  
};


};

#endif
