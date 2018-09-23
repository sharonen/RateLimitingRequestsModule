#include <iostream>
#include "lib/requests_handler/requests_handler.hpp"

int main(int argc, char* argv[]) {

  auto pRequestsHandler = new RequestsHadler();
  pRequestsHandler->printLimit();
  pRequestsHandler->requests_limit(200);
  pRequestsHandler->printLimit();;
  return 0;
}

