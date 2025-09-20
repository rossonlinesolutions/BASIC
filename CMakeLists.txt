cmake_minimum_required(VERSION 3.10)
project(TinyBasic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Unity build: compile only Main.cpp
add_executable(tinybasic src/Main.cpp)
target_include_directories(tinybasic PRIVATE include)

# Enable testing
enable_testing()
add_subdirectory(tests)
