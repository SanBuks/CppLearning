project(query LANGUAGES CXX)

add_subdirectory(str_blob)
add_subdirectory(text_query)
add_subdirectory(query_base)

add_executable(query_test query_test.cc)
target_link_libraries(query_test PRIVATE query)
# 增加数据路径
set(QueryDataPath ${CMAKE_SOURCE_DIR}/../ch15_data/data)
configure_file(query_data.h.in ${CMAKE_BINARY_DIR}/config/query_data.h)
target_include_directories(query_test PRIVATE ${CMAKE_BINARY_DIR}/config)