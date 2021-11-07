project(str_blob LANGUAGES CXX)

add_library(str_blob SHARED str_blob.cc str_blob_ptr.cc)
target_include_directories(str_blob PUBLIC ${str_blob_SOURCE_DIR})

add_executable(str_blob_test str_blob_test.cc)
target_link_libraries(str_blob_test PRIVATE str_blob)
target_include_directories(str_blob_test PRIVATE ${CMAKE_BINARY_DIR}/config)