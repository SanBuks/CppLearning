cmake_minimum_required(3.20)
project(ch12)

set(CMAKE_CXX_STANDARD 11       CACHE INTERNAL ""   FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED CACHE INTERNAL True FORCE)
set(CMAKE_BUILD_TYPE Debug      CACHE INTERNAL ""   FORCE)

add_subdirectory(str_blob)
add_subdirectory(text_query)