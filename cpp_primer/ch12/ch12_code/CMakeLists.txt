cmake_minimum_required(VERSION 3.20)
project(ch12 LANGUAGES CXX)

# 编译标准 和 构建类型
set(CMAKE_CXX_STANDARD 11          CACHE INTERNAL ""   FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL ""   FORCE)
set(CMAKE_BUILD_TYPE Debug         CACHE INTERNAL ""   FORCE)

# 读取文件路径
set(StrBlobDataPath   ${CMAKE_SOURCE_DIR}/../ch12_data/str_blob_data)
set(TextQueryDataPath ${CMAKE_SOURCE_DIR}/../ch12_data/)
# 设定配置文件信息
configure_file(str_blob_data.h.in
               ${CMAKE_BINARY_DIR}/config/str_blob_data.h)
configure_file(text_query_data.h.in
               ${CMAKE_BINARY_DIR}/config/text_query_data.h)

# 子目录
add_subdirectory(str_blob)
add_subdirectory(text_query)