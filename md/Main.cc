#include <memory>
#include "Config.hh"
#include "Server.hh"
#include "soil/Pause.hh"

int main(int argc, char* argv[])
{

  std::unique_ptr<md::Config> config;
  config.reset( new md::Config(argc, argv) );

  std::unique_ptr<md::Server> server;
  server.reset( new md::Server(config.get()) );
  
  std::unique_ptr<soil::Pause> pause(soil::Pause::create());
  
  return 0;
}
