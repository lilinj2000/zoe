// Copyright (c) 2010
// All rights reserved.

#ifndef TEXT_SERVER_HH
#define TEXT_SERVER_HH

#include <string>
#include "soil/DataFile.hh"
#include "zod/SubService.hh"

namespace text {

class MData : public soil::Data {
 public:
  explicit MData(const std::string& data):
      data_(data) {
  }

  virtual ~MData() {
  }

  virtual void writeToFile(std::ofstream* os) const {
    (*os) <<data_;
  }

 private:
  std::string data_;
};

class Options;

class Server : public zod::MsgCallback {
 public:
  explicit Server(Options* options);

  virtual ~Server();

  virtual void msgCallback(const zod::Msg*);

 protected:
  void run();

 private:
  Options* options_;
  std::unique_ptr<soil::DataFile> text_file_;
  std::unique_ptr<zod::SubService> sub_service_;
};

};  // namespace text

#endif
