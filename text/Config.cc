// Copyright (c) 2010
// All rights reserved.

#include <fstream>
#include <iostream>
#include "boost/program_options.hpp"
#include "Config.hh"
#include "Log.hh"

namespace text {

Options::Options():
    config_options_("TextConfigOptions") {
  namespace po = boost::program_options;

  config_options_.add_options()
      ("text.proxy_addr", po::value<std::string>(&proxy_addr),
       "proxy address")

      ("text.text_file", po::value<std::string>(&text_file),
       "text file")

      ("text.log_cfg", po::value<std::string>(&log_cfg),
       "log config file");

  return;
}

Options::~Options() {
}

po::options_description* Options::configOptions() {
  return &config_options_;
}

Config::Config(int argc, char* argv[]) {
  text_options_.reset(new Options());

  std::auto_ptr<soil::Config> config(soil::Config::create());
  config->registerOptions(text_options_.get());

  config->configFile() = "text.cfg";
  config->loadConfig(argc, argv);

  // init the log
  TEXT_LOG_INIT(text_options_->log_cfg);

  return;
}

Config::~Config() {
}

};  // namespace text
