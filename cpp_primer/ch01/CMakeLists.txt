project(ch01 LANGUAGES CXX)

# stream_test 设置数据路径
set(StreamTestDataPath "${CMAKE_CURRENT_SOURCE_DIR}/data/stream_test_data")
configure_file(stream_test_data.h.in config/stream_test_data_config.h)
# stream_test 流状态位变化
add_executable(stream_test stream_test.cc)
target_include_directories(stream_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/config)

# 增加 Sales_item 头文件库
add_library(sales_item INTERFACE)
target_include_directories(sales_item INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(exercises)
add_subdirectory(exercises_trivial)
