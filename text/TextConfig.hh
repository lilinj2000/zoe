#ifndef TEXT_CONFIG_HH
#define TEXT_CONFIG_HH

#include <string>
#include <memory>
#include "soil/Config.hh"

namespace text
{

namespace po = boost::program_options;

class TextOptions : public soil::Options
{
 public:

  TextOptions();
  
  virtual ~TextOptions();

  virtual po::options_description* configOptions();

  std::string xpub_addr;

  std::string text_file;
  
  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class TextConfig
{
 public:
  
  TextConfig(int argc=0, char* argv[]=NULL);
  ~TextConfig();

  TextOptions* textOptions()
  {
    return text_options_.get();
  }

 private:
  std::unique_ptr<TextOptions> text_options_;

};

}  


#endif 
