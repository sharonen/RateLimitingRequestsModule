cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(RateLimitingRequestsModuleTests ${TEST_SOURCE})
target_link_libraries(RateLimitingRequestsModuleTests  ReuestsHandler ${CONAN_LIBS})
add_test(NAME RateLimitingRequestsModuleTests
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
         COMMAND ${CMAKE_BINARY_DIR}/bin/RateLimitingRequestsModuleTests)
