#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#pragma once

#include "response.hpp"
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>

using namespace std;



class Timer{
public:
	Timer(boost::asio::steady_timer* pTimer): pTimer_(std::move(pTimer)){}

	boost::asio::steady_timer* pTimer() {return pTimer_;}


private:
	boost::asio::steady_timer* pTimer_;
};


class RequestsHadler {
public:

	RequestsHadler():requests_limit_(100), timer_rate_in_sec_(60){}

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
	Response handleNewRequest(string& url);

private:
	int requests_limit_;
	int current_requests_limit_;
	int timer_rate_in_sec_;
};

#endif


