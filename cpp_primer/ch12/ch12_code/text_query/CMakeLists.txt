project(text_query LANGUAGES CXX)

add_executable(text_query_test text_query_test.cc)
target_link_libraries(text_query_test str_blob)
target_include_directories(text_query_test
                           PRIVATE ${str_blob_SOURCE_DIR}
                           PRIVATE ${CMAKE_BINARY_DIR}/config)

# 手动将 str_blob 的 dll 复制到 text_query_test build 目录中
add_custom_command(TARGET text_query_test POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   "$<TARGET_FILE:str_blob>"
                   $<TARGET_FILE_DIR:text_query_test>)