cmake_minimum_required(VERSION 3.23)

project(MarioTest)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
message(STATUS "Mario Lib Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")




# Tests
add_subdirectory(tests)
