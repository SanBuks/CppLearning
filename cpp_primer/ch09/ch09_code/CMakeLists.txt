cmake_minimum_required(VERSION 3.20)

# 设置项目文件信息 和 头文件
project(ch09 VERSION 1.0)
configure_file(ch09_config.h.in ch09_config.h)

# 增加其他文件夹下依赖的头文件
# 路径变量
set(COMMON_HEADER "D:/Project/LEARNING/CppLearning/cpp_primer/header")
# 增加子文件夹
include_directories(${COMMON_HEADER})
# 头文件夹增加到 build 路径
add_subdirectory(${COMMON_HEADER} ${PROJECT_BINARY_DIR}/header)
# 记录路径
list(APPEND EXTRA_LIBS ${COMMON_HEADER})

# 将复制 data 文件方式改为 通过 config 头文件注入
# set(CODE_DATA "../ch09_data")
# file(COPY ${CODE_DATA} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# 设置编译标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(date date.cc)
add_executable(simple_expression simple_expression.cc)

target_include_directories(date PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(simple_expression PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS date DESTINATION bin)
install(TARGETS simple_expression DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/ch09_config.h"
        DESTINATION include)

function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg}
            PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction(do_test)