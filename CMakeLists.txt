cmake_minimum_required(VERSION 3.10)
project(BASIC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to get the current tag (if HEAD is tagged)
execute_process(
    COMMAND git describe --tags --exact-match
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_TAG
    RESULT_VARIABLE TAG_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Fallback to "nightly" if no tag is found
if(NOT TAG_RESULT EQUAL 0)
    set(GIT_TAG "<nightly>")
endif()

# Get current Git commit hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    RESULT_VARIABLE COMMIT_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT COMMIT_RESULT EQUAL 0)
    set(GIT_COMMIT_HASH "<unknown>")
endif()

# Get current Git branch name
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    RESULT_VARIABLE BRANCH_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT BRANCH_RESULT EQUAL 0)
    set(GIT_BRANCH "<unknown>")
endif()

# Define macros for use in C++
add_compile_definitions(
    GIT_TAG="${GIT_TAG}"
    GIT_COMMIT_HASH="${GIT_COMMIT_HASH}"
    GIT_BRANCH="${GIT_BRANCH}"
)

# Unity build: compile only Main.cpp
add_executable(basic src/Main.cpp)
target_include_directories(basic PRIVATE include)

# Enable testing
enable_testing()
add_subdirectory(tests)
