project(str_blob LANGUAGES CXX)

add_library(str_blob SHARED str_blob.cc)
# add_library(str_blob_ptr SHARED str_blob_ptr.cc)

add_executable(str_blob_test str_blob_test.cc)
target_link_libraries(str_blob_test
                      PRIVATE str_blob)
#                      PRIVATE str_blob_ptr)
target_include_directories(str_blob_test
                           PRIVATE ../../ch12_data)