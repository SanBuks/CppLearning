project(query_base)

add_library(query STATIC query.cc query_base.cc)
target_include_directories(query PUBLIC ${query_SOURCE_DIR})
target_link_libraries(query PUBLIC text_query)