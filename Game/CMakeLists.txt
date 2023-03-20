cmake_minimum_required(VERSION 3.23)

project(SuperMario)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SuperMario_SOURCE_DIR}/bin)
message(STATUS "Mario Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


############################################################
# Create a library
############################################################

#Generate the shared library from the library sources

add_library(Mario_Lib SHARED
            src/Game.cpp
            )


add_library(mario::lib ALIAS Mario_Lib)

target_include_directories(Mario_Lib
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/include
                           )


############################################################
# Create an executable
############################################################

# Add an executable with the above sources

add_executable(Mario App/main.cpp)

# link the new hello_library target with the hello_binary target

target_link_libraries(Mario PRIVATE
                      mario::lib
                      )

# Tests
add_subdirectory(tests)
