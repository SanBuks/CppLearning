project(text_query LANGUAGES CXX)

add_executable(text_query_test text_query_test.cc)
target_link_libraries(text_query_test str_blob)
target_include_directories(text_query_test
                           PRIVATE ${str_blob_SOURCE_DIR}
                           PRIVATE ${CMAKE_BINARY_DIR}/config)

# 如何将 分散在不同文件夹下的二进制文件 (SHARED) 链接到一起
# 1. 设置 target/library 的输出路径 2. 设置全局输出路径 3. 手动拷贝
# https://stackoverflow.com/questions/39807664/how-to-best-tell-cmake-where-to-find-dll
# 手动将 str_blob 的 dll 复制到 text_query_test build 目录中
add_custom_command(TARGET text_query_test POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   "$<TARGET_FILE:str_blob>"
                   $<TARGET_FILE_DIR:text_query_test>)