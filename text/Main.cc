#include "TextServer.hh"
#include "TextConfig.hh"
#include "soil/STimer.hh"

#include <memory>

int main(int argc, char* argv[])
{
  std::unique_ptr<text::TextConfig> config( new text::TextConfig(argc, argv) );
  
  std::unique_ptr<text::TextServer> text( new text::TextServer(config->textOptions()) );

  std::unique_ptr<soil::STimer> cond( soil::STimer::create() );
  
  while( true )
  {
    cond->wait( 2000 );
  }
}
