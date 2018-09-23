cmake_minimum_required(VERSION 3.0)
project(requests_handler)
set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(requests_handler STATIC ${PROJECT_SOURCE})
target_link_libraries(requests_handler  ${CONAN_LIBS})

