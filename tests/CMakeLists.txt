# GoogleTest setup
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCES
    test_main.cpp
)

add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests PRIVATE GTest::GTest GTest::Main pthread)
add_test(NAME AllTests COMMAND runTests)
