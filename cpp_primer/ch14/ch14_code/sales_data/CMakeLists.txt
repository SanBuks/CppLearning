project(sales_data LANGUAGES CXX)

add_library(sales_data SHARED sales_data.cc)
target_include_directories(sales_data PUBLIC ${sales_data_SOURCE_DIR})

add_executable(sales_data_test sales_data_test.cc)
target_link_libraries(sales_data_test PRIVATE sales_data)
# 增加 build 下的配置头文件目录
target_include_directories(sales_data_test PRIVATE ${CMAKE_BINARY_DIR}/config)
