#include <memory>
#include "MDConfig.hh"
#include "MDServer.hh"
#include "soil/STimer.hh"

int main(int argc, char* argv[])
{

  std::unique_ptr<md::MDConfig> config;
  config.reset( new md::MDConfig(argc, argv) );

  std::unique_ptr<md::MDServer> server;
  server.reset( new md::MDServer(config.get()) );
  
  std::unique_ptr<soil::STimer> cond;
  cond.reset( soil::STimer::create() );

  do
  {
    cond->wait(2000);
  }while(true);
  
  return 0;
}
