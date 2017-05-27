project(runUnitTestSuite)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()

add_executable(runUnitTestSuite
        instruction_cache_test.c)

target_link_libraries(runUnitTestSuite gtest gtest_main)
target_link_libraries(runUnitTestSuite gtest src)