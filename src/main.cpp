#include <iostream>
#include "lib/requests_handler/requests_handler.hpp"

int main(int argc, char* argv[]) {

  auto pRequestsHandler = new RequestsHadler(100, 60);
  boost::asio::io_service io_s;
  boost::asio::deadline_timer timer(io_s);
  boost::posix_time::seconds interval(pRequestsHandler->timer_rate_in_sec());
  timer.expires_at(timer.expires_at() + interval);
  timer.async_wait(std::bind(&RequestsHadler::updateRequestsLimit,pRequestsHandler, &timer));
  io_s.run();

  return 0;
}

