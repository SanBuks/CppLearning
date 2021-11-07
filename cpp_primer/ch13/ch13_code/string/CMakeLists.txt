project(string LANGUAGES CXX)

add_executable(string_test string_test.cc)
target_include_directories(string_test PUBLIC ${string_SOURCE_DIR})
