project(quote LANGUAGES CXX)

add_library(quote INTERFACE)
target_include_directories(quote INTERFACE ${quote_SOURCE_DIR})

add_executable(quote_test quote_test.cc)
target_link_libraries(quote_test PRIVATE quote)

## 增加 build 下的配置头文件目录
#target_include_directories(quote_test PRIVATE ${CMAKE_BINARY_DIR}/config)