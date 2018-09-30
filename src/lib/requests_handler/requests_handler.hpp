#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#pragma once

#include "response.hpp"
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include "curl/curl.h"
#include <mutex>


class RequestsHadler {
public:

	RequestsHadler():requests_limit_(100), timer_rate_in_sec_(60){
		curl_global_init( CURL_GLOBAL_ALL );
		curlHandle_ = curl_easy_init();
	}

	~RequestsHadler(){
		curl_easy_cleanup(curlHandle_);
		curl_global_cleanup();
	}

	RequestsHadler(int requests_limit, int timer_rate_in_sec);
	/*
	 * Getter for requests_limit_
	 * @return the requests limit
	 */
	int requests_limit() {return requests_limit_;}

	/*
	 * Setter for requests_limit_
	 * @param requests_limit - the new value for requests limits
	 */
	void requests_limit(int requests_limit) ;

	/*
	 * Getter for timer_rate_in_sec_
	 * @return the timer rate in seconds
	 */
	int timer_rate_in_sec() {return timer_rate_in_sec_;}

	/*
	 * Setter for timer_rate_in_sec_
	 * @ the new rate in seconds for the timer
	 */
	void timer_rate_in_sec(int timer_rate_in_sec) ;

	/*
	 * Getter for current_requests_limit_
	 * @return the current requests limits
	 */
	int current_requests_limit() {return current_requests_limit_;}


	/*
	 * After the timer expired, update the
	 * current_requests_limit_ to be requests_limit_
	 */
	void updateRequestsLimit(boost::asio::deadline_timer* timer);

	/*
	 * Handles new requests and check if the number of
	 * requests reached the limit.
	 * @param url - the url HTTP request
	 */
	Response handleNewRequest(const string & url);

private:
	/*
	 * Sets a curl option with the url HTTP request.
	 * @param url - the url HTTP request
	 * @return true is the curl library was able to set the url
	 * request. Otherwise, false
	 */
	bool setURL( const string & url );

	int requests_limit_;
	int current_requests_limit_;
	int timer_rate_in_sec_;
	CURL * curlHandle_;
	std::mutex mu_;
};

#endif


