project(text_query LANGUAGES CXX)

add_library(text_query text_query.cc)
target_include_directories(text_query PUBLIC ${text_query_SOURCE_DIR})
target_link_libraries(text_query PUBLIC str_blob)