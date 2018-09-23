cmake_minimum_required(VERSION 3.0)
project(RateLimitingRequestsModule)

set(CMAKE_CXX_STANDARD 14)
file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(PROJECT_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
add_executable(RateLimitingRequestsModule ${PROJECT_MAIN})
target_link_libraries(RateLimitingRequestsModule ReuestsHandler ${CONAN_LIBS})

add_subdirectory(lib)


