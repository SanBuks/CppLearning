cmake_minimum_required(VERSION 3.27)
project(net)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

if (MSVC)
  set(CMAKE_CXX_FLAGS "/EHsc /utf-8")
endif()

include(cmake/tool.cmake)

find_package(spdlog REQUIRED)
find_package(asio   REQUIRED)
find_package(Iconv  REQUIRED)

add_subdirectory(ch01_sync)
add_subdirectory(ch02_async)
add_subdirectory(io_context)

add_executable(test main.cpp)
