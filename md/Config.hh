// Copyright (c) 2010
// All rights reserved.

#ifndef MD_CONFIG_HH
#define MD_CONFIG_HH

#include <string>
#include <memory>
#include <vector>
#include "soil/Config.hh"

namespace md {

namespace po = boost::program_options;

class Options : public soil::Options {
 public:
  Options();

  virtual ~Options();

  virtual po::options_description* configOptions();

  std::vector<std::string> instrus;
  std::string pub_addr;
  std::string pull_addr;

  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class Config {
 public:
  explicit Config(int argc = 0, char* argv[] = nullptr);

  ~Config();

  Options* mdOptions() {
    return md_options_.get();
  }

  soil::Options* cataMDOptions() {
    return cata_md_options_.get();
  }

 private:
  std::unique_ptr<Options> md_options_;

  std::unique_ptr<soil::Options> cata_md_options_;
};

};  // namespace md

#endif
