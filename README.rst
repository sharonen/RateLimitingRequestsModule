==========================
RateLimitingRequestsModule
==========================

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
* git git clone --recursive https://github.com/sharonen/RateLimitingRequestsModule.git
* cd RateLimitingRequestsModule
* mkdir build && cd build
* conan install ..
* cmake ..
* make

Running unit tests
------------------
* cd RateLimitingRequestsModule/build
* ctest -V


