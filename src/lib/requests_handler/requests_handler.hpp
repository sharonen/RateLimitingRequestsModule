#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#pragma once

#include "response.hpp"
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/error_code.hpp>

using namespace std;



class Timer{
public:
	Timer(std::shared_ptr<boost::asio::steady_timer> pTimer): pTimer_(std::move(pTimer)){}

	boost::asio::steady_timer* pTimer() {return pTimer_.get();}


private:
	std::shared_ptr<boost::asio::steady_timer> pTimer_;
};


class RequestsHadler {
public:

	RequestsHadler();

	RequestsHadler(int requests_limit, int timer_rate_in_sec);


	void printLimit();

	int requests_limit() {return requests_limit_;}

	void requests_limit(int requests_limit) ;

	//void updateRequestsLimit();

	Response handleNewRequest(string& url);
private:
	int requests_limit_;
	int timer_rate_in_sec_;
};

#endif


