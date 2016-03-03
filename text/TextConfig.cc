#include "TextConfig.hh"
#include "TextLog.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace text
{

TextOptions::TextOptions():
    config_options_("TextConfigOptions")
{

  namespace po = boost::program_options;

  config_options_.add_options()
      ("text.xpub_addr", po::value<std::string>(&xpub_addr), 
       "xpub address")

      ("text.text_file", po::value<std::string>(&text_file), 
       "text file")

      ("text.log_cfg", po::value<std::string>(&log_cfg), 
       "log config file")
      ;

  return;
  
}

TextOptions::~TextOptions()
{
}

po::options_description* TextOptions::configOptions()
{
  return &config_options_;
}

TextConfig::TextConfig(int argc, char* argv[])
{
  text_options_.reset(new TextOptions());

  std::auto_ptr<soil::Config> config( soil::Config::create() );
  config->registerOptions( text_options_.get() );

  config->configFile() = "text.cfg";
  config->loadConfig(argc, argv);
  
  // init the log
  TEXT_LOG_INIT( text_options_->log_cfg );
  
  return;
}

TextConfig::~TextConfig()
{
}

};  
