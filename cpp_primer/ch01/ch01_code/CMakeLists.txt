cmake_minimum_required(VERSION 3.20)
project(ch01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11          CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE Debug         CACHE INTERNAL "" FORCE)

# 设置数据路径变量
set(StreamTestDataPath   ${CMAKE_SOURCE_DIR}/../ch01_data/stream_test_data)
# 将数据变量值转换成头文件 放在 binary_dir/config 下
configure_file(stream_test_data.h.in
               ${CMAKE_BINARY_DIR}/config/stream_test_data_config.h)
add_executable(stream_test stream_test.cc)
# 让生成的头文件被测试源文件可见
target_include_directories(stream_test PRIVATE ${CMAKE_BINARY_DIR}/config)


add_executable(markdown_process markdown_process.cc)