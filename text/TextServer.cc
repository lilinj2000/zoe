#include "TextServer.hh"
#include "TextConfig.hh"
#include "TextLog.hh"

#include <cassert>

namespace text
{

TextServer::TextServer(TextOptions* options):
    options_(options)
{
  TEXT_TRACE <<"TextServer::TextServer()";

  text_file_.reset( new soil::DataFile(options_->text_file) );

  TEXT_INFO <<"xpub_addr: " <<options_->xpub_addr;
  sub_service_.reset( zod::SubService::create(options_->xpub_addr, this) );
}

TextServer::~TextServer()
{
  TEXT_TRACE <<"TextServer::~TextServer()";
  
}

void TextServer::msgCallback(const zod::Msg* msg)
{
  std::string data( (char*)msg->data_.get() );
  
  text_file_->putData( new MData(data) );
}

};
