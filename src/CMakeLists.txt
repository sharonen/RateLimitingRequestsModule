cmake_minimum_required(VERSION 3.0)
project(rate_limiting_requests_app)

set(CMAKE_CXX_STANDARD 14)
file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(PROJECT_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
add_executable(rate_limiting_requests_app ${PROJECT_MAIN})
target_link_libraries(rate_limiting_requests_app requests_handler ${CONAN_LIBS})


