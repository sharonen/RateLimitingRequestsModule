#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../requests_handler/requests_handler.hpp"
#include "../requests_handler/response.hpp"



TEST_CASE("Checking the limit of requests")
{
  GIVEN("a Requests Handle"){
	  auto pRequestsHandler = new RequestsHadler(100, 60);
	  THEN("the requests limits is as expected")
	  REQUIRE(pRequestsHandler->requests_limit()== 100);
  }
}


TEST_CASE("Checking getter and setter methods")
{
  GIVEN("a Requests Handle"){
	  auto pRequestsHandler = new RequestsHadler(100, 60);
	  pRequestsHandler->requests_limit(200);
	  THEN("the new requests limits is as expected")
	  REQUIRE(pRequestsHandler->requests_limit() == 200);

  }
}

TEST_CASE("checking the limit of requests")
{
  GIVEN("a Requests Handle"){
	  Response reps;
	  std::string url = "www.google.com";
	  RequestsHadler* pRequestsHandler = new RequestsHadler(5, 60);
	  REQUIRE(pRequestsHandler->requests_limit() == 5);
	  for(int i = 0; i < 5; i++){
		  reps = pRequestsHandler->handleNewRequest(url);
		  REQUIRE(reps.code == ErrorCode::ok);
	  }
	  THEN("the method returns false")
	  REQUIRE(pRequestsHandler->requests_limit() == 0);
	  reps = pRequestsHandler->handleNewRequest(url);
	  REQUIRE(reps.code == ErrorCode::TooManyRequests);
  }
}



