### 设置顶层 cmake
```cmake
# 设置 是否链接动态库 (作为项目信息, 一定在 configure_file() 前设置)
option(USE_MYMATH "Use tutorial implementation" ON)

#... 

# 根据选项收集 动态库名称, 路径
if (USE_MYMATH)
    # 增加 子文件中的库
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

# ...

# 增加 动态库链接
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})
# 增加 include 目录
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${EXTRA_INCLUDES})
```

### 减少顶层 cmake 条件
```cmake
if (USE_MYMATH)
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
#   list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}")
#                          ${EXTRA_INCLUDES})
```


### 增加 ctest 设置
```cmake
# 开启测试
enable_testing()
# 增加 名为 Runs  命令为 Tutorial 25 的测试用例
add_test(NAME Runs COMMAND Tutorial 25)

# 增加 名为 Runs  命令为 Tutorial 的测试用例
# 期待的输出符合正则表达式 Usage:.*number
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage
        PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# 命名 do_test 函数
#     target : 测试用例程序名称
#     arg : 测试用例程序参数
#     result : 测试用例程序输出结果
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
          PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction(do_test)

do_test(Tutorial 4 "4 Is 2")
do_test(Tutorial 9 "9 Is 3")
do_test(Tutorial 5 "5 Is 2.236")
do_test(Tutorial 7 "7 Is 2.645")
do_test(Tutorial 25 "25 Is 5")
do_test(Tutorial -25 "-25 Is [nan|nan|0]")
do_test(Tutorial 0.0001 "0.0001 Is 0.01")
```

### ctest 命令
> ctest [ -N | -VV | -C \<cfg>] 
> 在 build_dir 下开启测试

- `-N` : 显示测试用例信息, 不测试
- `-VV` : 显示详细信息
- `-C <cfg>` : 设置测试的运行配置为Debug


