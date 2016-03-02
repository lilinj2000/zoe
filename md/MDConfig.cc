#include "MDConfig.hh"
#include "MDLog.hh"
#include "cata/MDService.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace md
{

MDOptions::MDOptions():
    config_options_("MDConfigOptions")
{

  namespace po = boost::program_options;

  config_options_.add_options()
      ("md.instru", po::value<std::string>(&instru), 
       "instrument")
      ("md.xsub_addr", po::value<std::string>(&xsub_addr), 
       "xsub address")

      ("md.log_cfg", po::value<std::string>(&log_cfg), 
       "log config file")
      ;

  return;
  
}

MDOptions::~MDOptions()
{
}

po::options_description* MDOptions::configOptions()
{
  return &config_options_;
}

MDConfig::MDConfig(int argc, char* argv[])
{
  md_options_.reset(new MDOptions());
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

MDConfig::~MDConfig()
{
}

};  
