// Copyright (c) 2010
// All rights reserved.

#ifndef TEXT_CONFIG_HH
#define TEXT_CONFIG_HH

#include <string>
#include <memory>
#include "soil/Config.hh"

namespace text {

namespace po = boost::program_options;

class Options : public soil::Options {
 public:
  Options();

  virtual ~Options();

  virtual po::options_description* configOptions();

  std::string proxy_addr;
  std::string text_file;
  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class Config {
 public:
  explicit Config(int argc = 0, char* argv[] = nullptr);

  ~Config();

  Options* textOptions() {
    return text_options_.get();
  }

 private:
  std::unique_ptr<Options> text_options_;
};

};  // namespace text

#endif
