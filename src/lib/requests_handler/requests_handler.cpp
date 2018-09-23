#include <iostream>
#include <sstream>
#include "requests_handler.hpp"

using namespace std;


RequestsHadler::RequestsHadler(int requests_limit, int timer_rate_in_sec) :
		requests_limit_(requests_limit),
		current_requests_limit_(requests_limit)
        timer_rate_in_sec_(timer_rate_in_sec){
	assert(requests_limit > 0);
	assert(timer_rate_in_sec > 0);
}


void RequestsHadler::requests_limit(int requests_limit){
	//requests_limit can't be negative
	assert(requests_limit > 0);
	requests_limit_ = requests_limit;
}

void RequestsHadler::timer_rate_in_sec(int timer_rate_in_sec){
	//timer_rate_in_sec can't be negative
	assert(timer_rate_in_sec > 0);
	timer_rate_in_sec_ = timer_rate_in_sec;
}


Response RequestsHadler::handleNewRequest(string& url){
	//handles the requests. if the number of requests reached the limit
	// an error code 429 and a an error message will be return
	if(current_requests_limit_ == 0){
		ostringstream oss;
		oss << "Rate limit exceeded. Try again in" << timer_rate_in_sec_ << "seconds";
		const string errMsg  = oss.str();
	    return {ErrorCode::TooManyRequests, errMsg};
	}
	--current_requests_limit_;
	return {ErrorCode::ok, ""};
}

void RequestsHadler::updateRequestsLimit(boost::asio::deadline_timer* timer ){
	//After the rate time passed,
	//updating the current requests limit to be the requests limit
	current_requests_limit_ = requests_limit_;
	boost::posix_time::seconds interval(timer_rate_in_sec_);
	timer->expires_at(timer->expires_at() + interval);
	timer->async_wait(std::bind(&RequestsHadler::updateRequestsLimit, this, timer));
	return ;
}

