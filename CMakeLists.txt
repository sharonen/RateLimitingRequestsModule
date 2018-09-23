cmake_minimum_required(VERSION 3.0)
project(RateLimitingRequestsModule_app)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(${CONAN_INCLUDE_DIRS})

add_subdirectory(src)

enable_testing()
add_subdirectory(unit_tests)

