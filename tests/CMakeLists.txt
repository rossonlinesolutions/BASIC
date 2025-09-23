# GoogleTest setup
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ../include)

set(TEST_SOURCES
    test_main.cpp
    BasicEnvTest.cpp
    BasicFileConsoleTest.cpp
    BasicLexerTest.cpp
    BasicTestConsole.cpp
    BasicInputStatementTest.cpp
    BasicUnaryExpressionTest.cpp
)

set(MAIN_SOURCES ../src/MainModule.cpp)

add_executable(runTests ${TEST_SOURCES} ${MAIN_SOURCES})
target_link_libraries(runTests PRIVATE GTest::GTest GTest::Main pthread)
add_test(NAME AllTests COMMAND runTests)
