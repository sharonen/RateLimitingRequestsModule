cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(rate_limiting_requests_module_test ${TEST_SOURCE})
target_link_libraries(rate_limiting_requests_module_test  requests_handler ${CONAN_LIBS})
add_test(NAME rate_limiting_requests_module_tests
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
         COMMAND ${CMAKE_BINARY_DIR}/bin/rate_limiting_requests_module_test)
