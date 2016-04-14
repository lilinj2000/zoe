#include "Config.hh"
#include "Log.hh"
#include "cata/MDService.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace md
{

Options::Options():
    config_options_("MDConfigOptions")
{

  namespace po = boost::program_options;

  config_options_.add_options()
      ("md.instru", po::value<std::vector<std::string>>(&instrus), 
       "instruments")
      ("md.proxy_addr", po::value<std::string>(&proxy_addr), 
       "proxy address")

      ("md.log_cfg", po::value<std::string>(&log_cfg), 
       "log config file")
      ;

  return;
  
}

Options::~Options()
{
}

po::options_description* Options::configOptions()
{
  return &config_options_;
}

Config::Config(int argc, char* argv[])
{
  md_options_.reset(new Options());
  cata_md_options_.reset( cata::MDService::createOptions() );

  std::auto_ptr<soil::Config> config( soil::Config::create() );
  config->registerOptions( md_options_.get() );
  config->registerOptions( cata_md_options_.get() );

  config->configFile() = "md.cfg";
  config->loadConfig(argc, argv);
  
  // init the log
  MD_LOG_INIT( md_options_->log_cfg );
  
  return;
}

Config::~Config()
{
}

};  
