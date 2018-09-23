cmake_minimum_required(VERSION 3.0)
project(rate_limiting_requests_app)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(${CONAN_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(requests_handler)

enable_testing()
add_subdirectory(unit_tests)

