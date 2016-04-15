// Copyright (c) 2010
// All rights reserved.

#include <memory>
#include "Server.hh"
#include "Config.hh"
#include "soil/Pause.hh"

int main(int argc, char* argv[]) {
  std::unique_ptr<text::Config> config(new text::Config(argc, argv));
  std::unique_ptr<text::Server> text(new text::Server(config->textOptions()));

  std::unique_ptr<soil::Pause> pause(soil::Pause::create() );
}
