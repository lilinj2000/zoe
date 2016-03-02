#ifndef PROXY_SERVER_HH
#define PROXY_SERVER_HH

namespace proxy
{

class ProxyOptions;

class ProxyServer
{
 public:
  ProxyServer(ProxyOptions* options);

  virtual ~ProxyServer();

 private:

  ProxyOptions* options_;
  
  void* context_;
  void* xsub_;
  void* xpub_;
  
};


};

#endif
