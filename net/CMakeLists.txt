cmake_minimum_required(VERSION 3.27)
project(net)

set(CMAKE_CXX_STANDARD 20)

find_package(Iconv REQUIRED)

add_subdirectory(ch01_sync)
add_subdirectory(ch02_async)
add_subdirectory(io_context)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE
#  Iconv::Iconv
#  ws2_3
)
