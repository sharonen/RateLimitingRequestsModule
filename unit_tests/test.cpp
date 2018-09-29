#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/lib/requests_handler/requests_handler.hpp"
#include "../src/lib/requests_handler/response.hpp"



TEST_CASE("Checking the limit of requests")
{
  GIVEN("a Requests Handle"){
	  auto pRequestsHandler = new RequestsHadler(100, 60);
	  THEN("the requests limits is as expected")
	  REQUIRE(pRequestsHandler->requests_limit()== 100);
  }
}


TEST_CASE("Checking getter and setter methods of requests limits")
{
  GIVEN("a Requests Handle"){
	  auto pRequestsHandler = new RequestsHadler(100, 60);
	  WHEN("setting a new value requests_limit"){
		  pRequestsHandler->requests_limit(200);
		  THEN("the new requests limits is as expected"){
			  REQUIRE(pRequestsHandler->requests_limit() == 200);
		  }
	  }

  }
}


TEST_CASE("Checking getter and setter methods of timer_rate_in_sec")
{
  GIVEN("a Requests Handle"){
	  auto pRequestsHandler = new RequestsHadler(100, 60);
	  WHEN("setting a new value timer_rate_in_sec"){
		  pRequestsHandler->timer_rate_in_sec(10);
		  THEN("the new requests limits is as expected"){
			  REQUIRE(pRequestsHandler->timer_rate_in_sec() == 10);
		  }
	  }

  }
}

TEST_CASE("checking the limit of requests")
{
  GIVEN("a Requests Handle"){
	  Response reps;
	  std::string url = "www.google.com";
	  RequestsHadler* pRequestsHandler = new RequestsHadler(5, 60);
	  REQUIRE(pRequestsHandler->requests_limit() == 5);
	  WHEN("sending 6 HTTP requests"){
		  for(int i = 0; i < 5; i++){
			  reps = pRequestsHandler->handleNewRequest(url);
			  REQUIRE(reps.code == ErrorCode::ok);
		  }
		  reps = pRequestsHandler->handleNewRequest(url);
		  THEN("the method returns an error code too many requests (HTTP error code 429)"){
			  REQUIRE(reps.code == ErrorCode::TooManyRequests);
		  }
	  }
  }
}


TEST_CASE("checking the update requests limit")
{
  GIVEN("a Requests Handle"){
	  Response reps;
	  std::string url = "www.google.com";
	  RequestsHadler* pRequestsHandler = new RequestsHadler(10, 2);
	  REQUIRE(pRequestsHandler->current_requests_limit() == 10);
	  for(int i = 0; i < 5; i++){
		  reps = pRequestsHandler->handleNewRequest(url);
		  REQUIRE(reps.code == ErrorCode::ok);
	  }
	  REQUIRE(pRequestsHandler->current_requests_limit()== 5);
	  WHEN("calling updateRequestsLimit"){
		  boost::asio::io_service io_s;
		  boost::asio::deadline_timer timer(io_s);
		  pRequestsHandler->updateRequestsLimit(&timer);
		  THEN("the current requests limit is restart"){
			  REQUIRE(pRequestsHandler->current_requests_limit()== 10);
		  }
	  }

  }
}


TEST_CASE("checking the url requests ")
{
  GIVEN("a Requests Handle"){
	  Response reps;

	  RequestsHadler* pRequestsHandler = new RequestsHadler(10, 2);
	  REQUIRE(pRequestsHandler->current_requests_limit()== 10);
	  WHEN("requesting a correct URL request"){
		  std::string url = "www.google.com";
		  reps = pRequestsHandler->handleNewRequest(url);
		  THEN("the method returns okay (HTTP code 200)"){
			  REQUIRE(reps.code == ErrorCode::ok);
		  }
	  }
	  WHEN("requesting a worng URL request"){
		  std::string url = "www.no_such_url_fot_testing.com";
		  reps = pRequestsHandler->handleNewRequest(url);
		  THEN("the method returns an error code bad request (HTTP error code 400)"){
			  REQUIRE(reps.code == ErrorCode::BadRequest);
		  }
	  }
  }
}


