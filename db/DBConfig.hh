#ifndef DB_CONFIG_HH
#define DB_CONFIG_HH

#include <string>
#include <memory>
#include "soil/Config.hh"

namespace db
{

namespace po = boost::program_options;

class DBOptions : public soil::Options
{
 public:

  DBOptions();
  
  virtual ~DBOptions();

  virtual po::options_description* configOptions();

  std::string xpub_addr;

  std::string db_file;
  
  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class DBConfig
{
 public:
  
  DBConfig(int argc=0, char* argv[]=NULL);
  ~DBConfig();

  DBOptions* dbOptions()
  {
    return db_options_.get();
  }

 private:
  std::unique_ptr<DBOptions> db_options_;

};

}  


#endif 
