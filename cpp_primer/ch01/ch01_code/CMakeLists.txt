cmake_minimum_required(VERSION 3.20)
project(ch01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          11    CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "" FORCE)

# 1. 显示 cin 读取时状态位变化
add_executable(stream_test stream_test.cc)
# 设置数据路径变量
set(StreamTestDataPath ${CMAKE_SOURCE_DIR}/../ch01_data/stream_test_data)
# 生成数据路径头文件, 放在 ${CMAKE_BINARY_DIR}/config 下
configure_file(stream_test_data.h.in
               ${CMAKE_BINARY_DIR}/config/stream_test_data_config.h)
# 让生成的头文件可见
target_include_directories(stream_test PRIVATE ${CMAKE_BINARY_DIR}/config)

# 2. 处理 summary 中 code style 程序
add_executable(markdown_process markdown_process.cc)

# 3. 增加 Sales_item 头文件库
add_library(sales_item INTERFACE)
target_include_directories(sales_item INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})