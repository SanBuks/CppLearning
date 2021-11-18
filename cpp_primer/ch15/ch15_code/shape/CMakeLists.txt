project(shape LANGUAGES CXX)

add_library(shape INTERFACE)
target_include_directories(shape INTERFACE ${shape_SOURCE_DIR})

add_executable(shape_test shape_test.cc)
target_link_libraries(shape_test PRIVATE shape)