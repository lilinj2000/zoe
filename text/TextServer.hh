#ifndef TEXT_SERVER_HH
#define TEXT_SERVER_HH

#include "soil/DataFile.hh"

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

  virtual void writeToFile(std::ofstream& os) const
  {
    os <<data_;
  }

 private:
  std::string data_;
};

class TextOptions;

class TextServer
{
 public:
  TextServer(TextOptions* options);

  virtual ~TextServer();

 protected:
  
  void run();
  
 private:

  TextOptions* options_;
  
  void* context_;
  void* sub_;

  std::unique_ptr<soil::DataFile> text_file_;
};


};

#endif
