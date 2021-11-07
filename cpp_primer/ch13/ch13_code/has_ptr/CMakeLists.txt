project(has_ptr LANGUAGES CXX)

add_library(has_ptr_value SHARED has_ptr_value.cc)
target_include_directories(has_ptr_value PUBLIC ${has_ptr_SOURCE_DIR})

add_library(has_ptr_pointer SHARED has_ptr_pointer.cc)
target_include_directories(has_ptr_pointer PUBLIC ${has_ptr_SOURCE_DIR})

add_executable(has_ptr_test has_ptr_test.cc)
target_link_libraries(has_ptr_test
                      PRIVATE has_ptr_value
                      PRIVATE has_ptr_pointer)
