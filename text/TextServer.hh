#ifndef TEXT_SERVER_HH
#define TEXT_SERVER_HH

#include <fstream>

namespace text
{

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

  std::ofstream text_file_;
  
};


};

#endif
