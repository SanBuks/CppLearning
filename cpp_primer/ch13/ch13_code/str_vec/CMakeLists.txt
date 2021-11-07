project(str_vec LANGUAGES CXX)

add_library(str_vec SHARED str_vec.cc)
target_include_directories(str_vec PUBLIC ${str_vec_SOURCE_DIR})

add_executable(str_vec_test str_vec_test.cc)
target_link_libraries(str_vec_test PRIVATE str_vec)
