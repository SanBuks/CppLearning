cmake_minimum_required(VERSION 3.20)
project(ch13 LANGUAGES CXX)

# 编译标准 和 构建类型
set(CMAKE_CXX_STANDARD 11          CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE Debug         CACHE INTERNAL "" FORCE)

# 子目录
add_subdirectory(has_ptr)
add_subdirectory(message)
add_subdirectory(tree)
add_subdirectory(str_vec)
add_subdirectory(string)
