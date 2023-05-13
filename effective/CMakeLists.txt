cmake_minimum_required(VERSION 3.0)
project(effective)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(effective_cpp)

add_executable(test test.cc)