cmake_minimum_required(VERSION 3.20)
project(learn_cia)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ch01_hello_concurrency)
add_subdirectory(ch02_managing_threads)
add_subdirectory(ch03_sharing_data_between_threads)

add_subdirectory(example)


add_executable(test test.cc)
