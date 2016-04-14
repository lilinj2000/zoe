#include "DBServer.hh"
#include "DBConfig.hh"
#include "soil/Pause.hh"

#include <memory>

int main(int argc, char* argv[])
{
  std::unique_ptr<db::DBConfig> config( new db::DBConfig(argc, argv) );
  
  std::unique_ptr<db::DBServer> db( new db::DBServer(config->dbOptions()) );

  std::unique_ptr<soil::Pause> cond( soil::Pause::create() );
}
