#ifndef TEXT_SERVER_HH
#define TEXT_SERVER_HH

#include "soil/DataFile.hh"
#include "zod/SubService.hh"

namespace text
{

class MData : public soil::Data
{
 public:
  MData(const std::string& data):
      data_(data)
  {
  }

  virtual ~MData()
  {
  }

  virtual void writeToFile(std::ofstream* os) const
  {
    (*os) <<data_;
  }

 private:
  std::string data_;
};

class TextOptions;

class TextServer : public zod::MsgCallback
{
 public:
  TextServer(TextOptions* options);

  virtual ~TextServer();

  virtual void msgCallback(const zod::Msg*);

 protected:
  
  void run();
  
 private:

  TextOptions* options_;

  std::unique_ptr<zod::SubService> sub_service_;
  
  std::unique_ptr<soil::DataFile> text_file_;
};


};

#endif
