// Copyright (c) 2010
// All rights reserved.

#include <string>
#include <iostream>
#include <set>
#include "soil/String.hh"
#include "zod/PushService.hh"
#include "json/json.hh"

int main(int argc, char* argv[]) {
  std::string proxy_addr(">tcp://127.0.0.1:18880");
  
  if (argc > 1) {
    proxy_addr = argv[1];
  }

  std::cout <<"=== Proxy addr is " <<proxy_addr <<std::endl;

  std::unique_ptr<zod::PushService> push_service(zod::PushService::create(proxy_addr));

  do {
    int item = -1;
    do {
      std::cout <<"=== 1. sub market data" <<std::endl;
      std::cout <<"=== 2. unsub market data" <<std::endl;
      std::cout <<"=== 0. quit" <<std::endl;
      std::cin >>item;

      std::cin.ignore();
    } while (item < 0 || item > 2);

    if (item == 0) {  // quit.
      return 0;
    }
    
    char instrus[256];
    std::cout <<"Please input instrus: ";
    std::cin.getline(instrus, 256);

    std::set<std::string> set_instrus;
    soil::splitString(&set_instrus, std::string(instrus));
    
    if (set_instrus.empty())
      continue;

    json::Document doc;
    json::Value val_array(json::kArrayType);
    for (auto& instru : set_instrus) {
      json::Value val_instru;
      val_instru.SetString(instru.data(), doc.GetAllocator());
      val_array.PushBack(val_instru, doc.GetAllocator());
    }
    json::Value val_instrus;
    json::addMember<const json::Value&>(&val_instrus, "Instrus", val_array, &doc);

    switch (item) {
      case 1:
        json::addMember<const json::Value&>(&doc, "SubMarketData", val_instrus);
        break;

      case 2:
        json::addMember<const json::Value&>(&doc, "UnsubMarketData", val_instrus);
        break;
    }

    std::string req = json::toString(doc);
    std::cout <<"request:\n"
              <<req <<std::endl;
    
    push_service->sendMsg(req);
    
  } while (true);

  return 0;
}
