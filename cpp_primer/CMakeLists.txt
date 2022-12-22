cmake_minimum_required(VERSION 3.21)
project(cpp_primer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          11    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

add_subdirectory(ch01)
#add_subdirectory(ch02)