cmake_minimum_required(VERSION 3.20)
project(ch14 LANGUAGES CXX)

# 编译标准 和 构建类型
set(CMAKE_CXX_STANDARD 11          CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE Debug         CACHE INTERNAL "" FORCE)

# 读取文件路径
set(SalesDataPath   ${CMAKE_SOURCE_DIR}/../ch14_data/sales_data)
configure_file(sales_data.h.in
               ${CMAKE_BINARY_DIR}/config/sales_data_config.h)
# 子目录
add_subdirectory(sales_data)
