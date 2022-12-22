project(exercises_trivial)

configure_file(data.h.in "${head_path}/data_config.h") # 生成数据头文件
set(path "${CMAKE_CURRENT_SOURCE_DIR}/../data") # 数据路径
set(head_path "${CMAKE_CURRENT_BINARY_DIR}/../config") # 头文件路径

add_executable(0103 0103.cc)
add_executable(0104 0104.cc)
add_executable(0105 0105.cc)
add_executable(0109 0109.cc)
add_executable(0110 0110.cc)
add_executable(0111 0111.cc)
add_executable(0116 0116.cc)
add_executable(0118 0118.cc)

# 增加 Sales_item 头文件 和 数据路径
function(add_exe_data source_name)
  set(${source_name}DataPath "${path}/${source_name}" PARENT_SCOPE)
  target_link_libraries(${source_name} sales_item)
  target_include_directories(${source_name} PRIVATE ${head_path})
endfunction()

add_executable(0120 0120.cc)
add_exe_data(0120)

add_executable(0121 0121.cc)
add_exe_data(0121)

add_executable(0122 0122.cc)
add_exe_data(0122)

add_executable(0123 0123.cc)
add_exe_data(0123)

add_executable(0124 0124.cc)
add_exe_data(0124)