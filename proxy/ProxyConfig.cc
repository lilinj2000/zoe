#include "ProxyConfig.hh"
#include "ProxyLog.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace proxy
{

ProxyOptions::ProxyOptions():
    config_options_("ProxyConfigOptions")
{

  namespace po = boost::program_options;

  config_options_.add_options()
      ("proxy.xsub_addr", po::value<std::string>(&xsub_addr), 
       "xsub address")
      ("proxy.xpub_addr", po::value<std::string>(&xpub_addr), 
       "xpub address")

      ("proxy.log_cfg", po::value<std::string>(&log_cfg), 
       "log config file")
      ;

  return;
  
}

ProxyOptions::~ProxyOptions()
{
}

po::options_description* ProxyOptions::configOptions()
{
  return &config_options_;
}

ProxyConfig::ProxyConfig(int argc, char* argv[])
{
  proxy_options_.reset(new ProxyOptions());

  std::auto_ptr<soil::Config> config( soil::Config::create() );
  config->registerOptions( proxy_options_.get() );

  config->configFile() = "proxy.cfg";
  config->loadConfig(argc, argv);
  
  // init the log
  PROXY_LOG_INIT( proxy_options_->log_cfg );
  
  return;
}

ProxyConfig::~ProxyConfig()
{
}

};  
