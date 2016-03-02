#include "ProxyServer.hh"
#include "ProxyConfig.hh"
#include "ProxyLog.hh"

#include "zmq.h"
#include <cassert>

namespace proxy
{

ProxyServer::ProxyServer(ProxyOptions* options):
    options_(options),
    context_(nullptr),
    xsub_(nullptr),
    xpub_(nullptr)
{
  PROXY_TRACE <<"ProxyServer::ProxyServer()";
  
  context_ = zmq_ctx_new();
  assert( context_ );
  
  xsub_ = zmq_socket(context_, ZMQ_XSUB);
  assert( xsub_ );
  
  xpub_ = zmq_socket(context_, ZMQ_XPUB);
  assert( xpub_ );

  PROXY_INFO <<"xsub_addr: " <<options_->xsub_addr;
  if( zmq_bind(xsub_, options_->xsub_addr.data())<0 )
  {
    std::string err = "xsub bind error.\n";
    throw std::runtime_error( err+zmq_strerror(zmq_errno()) );
  }
  

  PROXY_INFO <<"xpub_addr: " <<options_->xpub_addr;
  if( zmq_bind(xpub_, options_->xpub_addr.data())<0 )
  {
    std::string err = "xpub bind error.\n";
    throw std::runtime_error( err+zmq_strerror(zmq_errno()) );
  }

  zmq_proxy( xsub_, xpub_, nullptr );
  
}

ProxyServer::~ProxyServer()
{
  PROXY_TRACE <<"ProxyServer::~ProxyServer()";
  
  zmq_close( xsub_ );
  zmq_close( xpub_ );

  zmq_ctx_destroy( context_ );
}

};
