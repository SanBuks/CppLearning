project(tree LANGUAGES CXX)

add_library(tree SHARED tree.cc)
target_include_directories(tree PUBLIC ${tree_SOURCE_DIR})

add_executable(tree_test tree_test.cc)
target_link_libraries(tree_test PRIVATE tree)
