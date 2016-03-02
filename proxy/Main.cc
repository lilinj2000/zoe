#include "ProxyServer.hh"
#include "ProxyConfig.hh"

#include <memory>

int main(int argc, char* argv[])
{
  std::unique_ptr<proxy::ProxyConfig> config( new proxy::ProxyConfig(argc, argv) );
  
  std::unique_ptr<proxy::ProxyServer> proxy( new proxy::ProxyServer(config->proxyOptions()) );
}
