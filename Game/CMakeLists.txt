cmake_minimum_required(VERSION 3.23)

project(SuperMario)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SuperMario_SOURCE_DIR}/bin)
message(STATUS "Mario Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


############################################################
# Create a library
############################################################

# Generate the shared library from the library sources


add_library(Mario_Lib SHARED
            src/Game.cpp
            ../common/Shader.cpp
            ../common/shader.hpp

            Resources/Game/SimpleVertexShader.vertexshader
            Resources/Game/SimpleFragmentShader.fragmentshader
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

# Xcode and Visual working directories
target_link_libraries(Mario PRIVATE
                      mario::lib
                      ${ALL_LIBS}
                      )

set_target_properties(Mario PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${SuperMario_SOURCE_DIR}/bin")
create_target_launcher(Mario WORKING_DIRECTORY "${SuperMario_SOURCE_DIR}/bin")
create_default_target_launcher(Mario WORKING_DIRECTORY "${SuperMario_SOURCE_DIR}/bin")




# link the new hello_library target with the hello_binary target



# Tests
add_subdirectory(tests)
