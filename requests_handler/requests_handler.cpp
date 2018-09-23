#include <iostream>
#include <sstream>
#include "requests_handler.hpp"

using namespace std;

RequestsHadler::RequestsHadler(): requests_limit_(100), timer_rate_in_sec_(60){}

RequestsHadler::RequestsHadler(int requests_limit, int timer_rate_in_sec) :
		requests_limit_(requests_limit),
		timer_rate_in_sec_(timer_rate_in_sec){

	assert(requests_limit > 0);
	assert(timer_rate_in_sec > 0);
}

void RequestsHadler::printLimit() {
	cout << "The requests limit is: " << requests_limit_ << endl;
}

void RequestsHadler::requests_limit(int requests_limit){
	assert(requests_limit > 0);
	requests_limit_ = requests_limit;
}


Response RequestsHadler::handleNewRequest(string& url){
	if(requests_limit_ == 0){
		ostringstream oss;
		oss << "Rate limit exceeded. Try again in" << timer_rate_in_sec_ << "seconds";
		const string errMsg  = oss.str();
	    return {ErrorCode::TooManyRequests, errMsg};
	}
	--requests_limit_;
	return {ErrorCode::ok, ""};
}
