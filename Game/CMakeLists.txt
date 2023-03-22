cmake_minimum_required(VERSION 3.23)

project(MarioLib)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
message(STATUS "Mario Lib Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


############################################################
# Create a library
############################################################

# Generate the shared library from the library sources


add_library(Mario_Lib SHARED
            src/Game.cpp

            )


add_library(mario::lib ALIAS Mario_Lib)

target_include_directories(Mario_Lib
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/include
                           )


# Tests
add_subdirectory(tests)
