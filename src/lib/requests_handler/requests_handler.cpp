#include <iostream>
#include <sstream>
#include "requests_handler.hpp"

using namespace std;


RequestsHadler::RequestsHadler(int requests_limit, int timer_rate_in_sec) :
		requests_limit_(requests_limit),
		current_requests_limit_(requests_limit),
        timer_rate_in_sec_(timer_rate_in_sec){
	assert(requests_limit > 0);
	assert(timer_rate_in_sec > 0);
	curl_global_init( CURL_GLOBAL_ALL );
	curlHandle_ = curl_easy_init();
	curl_easy_setopt(curlHandle_, CURLOPT_DEFAULT_PROTOCOL, "https");
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

bool RequestsHadler::setURL( const string & url )
{
	CURLcode res = curl_easy_setopt( curlHandle_, CURLOPT_URL, url.c_str());
	return res == CURLE_OK;
}

Response RequestsHadler::handleNewRequest(const string & url){
	ostringstream oss;
	//handles the requests. if the number of requests reached the limit
	// an error code 429 and a an error message will be return
	if(current_requests_limit_ == 0){
		oss << "Rate limit exceeded. Try again in" << timer_rate_in_sec_ << "seconds";
		const string errMsg  = oss.str();
	    return {ErrorCode::TooManyRequests, errMsg};
	}
	//handling the url request
	if(!this->setURL(url)){
		oss << "illegal URL request";
		const string errMsg  = oss.str();
		return {ErrorCode::BadRequest, errMsg};
	}
	CURLcode res = curl_easy_perform(curlHandle_);
	if(res != CURLE_OK){
		oss << "The URL request couldn't be handled";
		const string errMsg  = oss.str();
		return {ErrorCode::BadRequest, errMsg};
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

