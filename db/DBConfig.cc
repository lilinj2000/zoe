#include "DBConfig.hh"
#include "DBLog.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace db
{

DBOptions::DBOptions():
    config_options_("DBConfigOptions")
{

  namespace po = boost::program_options;

  config_options_.add_options()
      ("db.xpub_addr", po::value<std::string>(&xpub_addr), 
       "xpub address")

      ("db.db_file", po::value<std::string>(&db_file), 
       "db file")

      ("db.log_cfg", po::value<std::string>(&log_cfg), 
       "log config file")
      ;

  return;
  
}

DBOptions::~DBOptions()
{
}

po::options_description* DBOptions::configOptions()
{
  return &config_options_;
}

DBConfig::DBConfig(int argc, char* argv[])
{
  db_options_.reset(new DBOptions());

  std::auto_ptr<soil::Config> config( soil::Config::create() );
  config->registerOptions( db_options_.get() );

  config->configFile() = "db.cfg";
  config->loadConfig(argc, argv);
  
  // init the log
  DB_LOG_INIT( db_options_->log_cfg );
  
  return;
}

DBConfig::~DBConfig()
{
}

};  
