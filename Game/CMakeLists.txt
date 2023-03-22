project(MarioTest)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
message(STATUS "Mario TEST Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Tests
add_subdirectory(tests)
