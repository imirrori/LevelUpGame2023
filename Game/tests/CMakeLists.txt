### Add Tests

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../include)


add_executable(Mario_test

               src/Game_test.cpp

               )

target_include_directories(Mario_test PRIVATE
                           ${CMAKE_SOURCE_DIR}/src
                           )

target_link_libraries(Mario_test
                      GTest::gtest_main
                      mario::lib
                      )

include(GoogleTest)

gtest_discover_tests(Mario_test)