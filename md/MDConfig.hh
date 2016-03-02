#ifndef MD_CONFIG_HH
#define MD_CONFIG_HH

#include <string>
#include <memory>
#include "soil/Config.hh"

namespace md
{

namespace po = boost::program_options;

class MDOptions : public soil::Options
{
 public:

  MDOptions();
  
  virtual ~MDOptions();

  virtual po::options_description* configOptions();

  std::string instru;
  
  std::string xsub_addr;

  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class MDConfig
{
 public:
  
  MDConfig(int argc=0, char* argv[]=NULL);
  ~MDConfig();

  MDOptions* mdOptions()
  {
    return md_options_.get();
  }

  soil::Options* cataMDOptions()
  {
    return cata_md_options_.get();
  }

 private:
  std::unique_ptr<MDOptions> md_options_;

  std::unique_ptr<soil::Options> cata_md_options_;
};

}  


#endif 
