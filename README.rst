==========================
RateLimitingRequestsModule
==========================
This is a rate-limiting HTTP requests module that stops a priticular 
requestor from making too many http requests within a particular period of time.


Overview
--------
inside src, there is the main.ccp of the application.

Requests Handle
---------------
This module handles the HTTP requests.
Members:

* requests_limit - the limit of the number of requests. Default 100. Can be easily set to a different value by calling the setter of requests_limit.

* current_requests_limit - the current request limit. Every request reduce this limit by 1,

* timer_rate_in_sec  - the rate limiting. Default 60 seconds. After the time reaches the rate, the current_requests_limit is reset and the counting starts from the beginning. Can be easily set to a different value by calling the setter of timer_rate_in_sec.

* handleNewRequest  - this method receives a URL request and checks if the number of requests reached its limit. If not, the method returns a response object with error code 200 (okay) and empty error message. If yes, the method returns a response object with error code 429 (too many requests) and error message "Rate limit exceeded. Try again in #(n) seconds".

* updateRequestsLimit - this method updates current_requests_limit to be requests_limit after the timer expired.


Prerequisites 
-------------
* Cmake (minimal required version 3.2)
* git
* C++ supporting C++14 
* Python 2.7
* Conan installed with the bincrafters remote added

Intalling conan
---------------
* pip install conan
* conan remote add bincrafters 'https://api.bintray.com/conan/bincrafters/public-conan'

Building the Module
---------------------
* git clone --recursive https://github.com/sharonen/RateLimitingRequestsModule.git
* cd RateLimitingRequestsModule
* mkdir build && cd build
* conan install ..
* cmake ..
* make

Running unit tests
------------------
* cd RateLimitingRequestsModule/build
* ctest -V


