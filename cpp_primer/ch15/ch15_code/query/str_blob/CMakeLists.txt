project(str_blob LANGUAGES CXX)

add_library(str_blob str_blob.cc str_blob_ptr.cc)
target_include_directories(str_blob PUBLIC ${str_blob_SOURCE_DIR})