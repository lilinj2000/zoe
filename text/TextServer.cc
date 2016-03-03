#include "TextServer.hh"
#include "TextConfig.hh"
#include "TextLog.hh"

#include "zmq.h"
#include <cassert>

namespace text
{

TextServer::TextServer(TextOptions* options):
    options_(options),
    context_(nullptr),
    sub_(nullptr)
{
  TEXT_TRACE <<"TextServer::TextServer()";

  text_file_.reset( new soil::DataFile(options_->text_file) );
  
  context_ = zmq_ctx_new();
  assert( context_ );
  
  sub_ = zmq_socket(context_, ZMQ_SUB);
  assert( sub_ );
  
  TEXT_INFO <<"xpub_addr: " <<options_->xpub_addr;
  if( zmq_connect(sub_, options_->xpub_addr.data())<0 )
  {
    std::string err = "connect xpub failed.\n";
    throw std::runtime_error( err+zmq_strerror(zmq_errno()) );
  }

  if( zmq_setsockopt(sub_, ZMQ_SUBSCRIBE, "", 0)<0 )
  {
    std::string err = "set subscribe options failed.\n";
    throw std::runtime_error( err+zmq_strerror(zmq_errno()) );
  }

  run();
}

TextServer::~TextServer()
{
  TEXT_TRACE <<"TextServer::~TextServer()";
  
  zmq_close( sub_ );
  
  zmq_ctx_destroy( context_ );

}

void TextServer::run()
{
  TEXT_TRACE <<"TextServer::run()";

  do
  {
    zmq_msg_t msg;
    zmq_msg_init( &msg );

    if( zmq_msg_recv(&msg, sub_, 0)<0 )
    {
      TEXT_ERROR <<"recv msg failed.\n"
                 <<zmq_strerror(zmq_errno());
    }
    else
    {
      TEXT_DEBUG <<"recv msg ...";

      std::string data((char *)zmq_msg_data(&msg));
      
      text_file_->putData( new MData(data) );
    }

    zmq_msg_close( &msg );
    
  }while( true );
}

};
