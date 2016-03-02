#ifndef PROXY_CONFIG_HH
#define PROXY_CONFIG_HH

#include <string>
#include <memory>
#include "soil/Config.hh"

namespace proxy
{

namespace po = boost::program_options;

class ProxyOptions : public soil::Options
{
 public:

  ProxyOptions();
  
  virtual ~ProxyOptions();

  virtual po::options_description* configOptions();

  std::string xsub_addr;

  std::string xpub_addr;
  
  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class ProxyConfig
{
 public:
  
  ProxyConfig(int argc=0, char* argv[]=NULL);
  ~ProxyConfig();

  ProxyOptions* proxyOptions()
  {
    return proxy_options_.get();
  }

 private:
  std::unique_ptr<ProxyOptions> proxy_options_;

};

}  


#endif 
