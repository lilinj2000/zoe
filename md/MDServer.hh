#ifndef MD_SERVER_HH
#define MD_SERVER_HH

#include "cata/MDService.hh"

namespace md
{

class MDOptions;
class MDConfig;

class MDServer : public cata::MDServiceCallback
{
 public:
  MDServer(MDConfig* config);

  virtual ~MDServer();

  virtual void onRspSubMarketData(const std::string& instru, bool success)
  {
  }

  virtual void onRspSubQuoteData(const std::string& instru, bool success)
  {
  }
  
  virtual void onRspUnsubMarketData(const std::string& instru, bool success)
  {
  }

  virtual void onRspUnsubQuoteData(const std::string& instru, bool success)
  {
  }
  
  virtual void onRtnMarketData(const cata::DepthMarketData* data);

  virtual void onRtnQuoteData() {}
  
  virtual void onRspError(int errord_id, const std::string& error_msg)
  {
  }

 private:

  MDOptions* options_;

  std::unique_ptr<cata::MDService> md_service_;
  
  void* context_;
  void* pub_;
  
};


};

#endif
