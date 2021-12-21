> 3.22.1 新增 summary

# Set Normal Var
```cmake
# set(<variable> <value>... [PARENT_SCOPE])
set(MY_VAR var1 var2)  # "var1;var2" 多个参数 <value>, 组成一个 list (";"分隔)
set(MY_VAR)            # 空参与 unset 效果相同

# function / dir 作用域中新建变量, 该变量的改变不会影响上一层的变量
# function / dir 作用域中继承变量, 该变量的改变不会影响上一层的变量
# [PARENT_SCOPE] 会改变上一层变量, 包括 set(MY_VAR), unset 情况在内
function(test)
  message(STATUS ${MY_VAR})
  set(MY_VAR "function_var")
# set(MY_VAR "function_var" PARENT_SCOPE)
# set(MY_VAR  PARENT_SCOPE)
endfunction()
set(MY_VAR "my_var")
test()
message(STATUS ${MY_VAR})
``` 

# Set Cache Entry
> 注意演示例子需要要及时删除 CMakeCache.txt 缓存文件, 因为前一次的缓存会影响到新增缓存变量的相关行为

```cmake
# set(<variable> <value>... CACHE <type> <docstring> [FORCE])
# 增加 缓存变量(缓存条例) 默认只增加变量(不会更改变量)
set(MY_CACHE_VAR "xxxx" CACHE STRING "")
set(MY_CACHE_VAR "yyyy" CACHE STRING "")
message(STATUS ${MY_CACHE_VAR})  # 仍然显示 xxxx

# <type> <docstring> 用于 cmake-gui, 一般采用 STRING ""
# <type>: 有 BOOL, FILEPATH, PATH, STRING, INTERNAL, 其中 INTERNAL 表示在 gui 中不显示且蕴含 [FORCE]
# <docstring>: 用短句描述该变量

# [FORCE] 强制 overwrite cache var
set(MY_CACHE_VAR "xxxx" CACHE STRING "")
set(MY_CACHE_VAR "yyyy" CACHE INTERNAL "")
message(STATUS ${MY_CACHE_VAR})

# 增加或修改缓存变量会 unset 作用域内同名的 普通变量
cmake_policy(PUSH)
cmake_policy(SET CMP0126 OLD)               # 3.21: NEW 则不会 unset 同名普通变量

set(MY_CACHE_VAR "zzz")
set(MY_CACHE_VAR "xxxx" CACHE STRING "")    # 新增 显示 xxxx

#set(MY_CACHE_VAR "xxxx" CACHE STRING "")
#set(MY_CACHE_VAR "zzz")
#set(MY_CACHE_VAR "yyyy" CACHE INTERNAL "") # 修改 显示 yyyy

message(STATUS ${MY_CACHE_VAR})
cmake_policy(POP)

# cmake command 中预设 缓存变量`cmake -DMY_COMMAND_CACHE_VAR=command_var ..`, 这里的变量没有 type 信息
# set 同名缓存变量只会增加其 type 信息除非有 [FORCE]
# 如果 type 是 PATH / FILEPATH, 会在前面添加相对路径前缀(构建路径)转换为绝对路径
set(MY_COMMAND_CACHE_VAR "xxxx" CACHE PATH "")       # D:/Project/LEARNING/CppLearning/cmake/build/command_var
set(MY_COMMAND_CACHE_VAR "xxxx" CACHE PATH "" FORCE) # D:/Project/LEARNING/CppLearning/cmake/build/xxxx
```

# Set Environment Var
```cmake
# set(ENV{<variable>} [<value>])
# 设置环境变量, 后续对此变量的引用内容是最新的值
# 只会影响当前的 CMake 进程, 不会影响调用者, 后续 build 和 test 进程和系统的环境变量
set(ENV{MY_ENV_VAR} xxxx)
message(STATUS $ENV{MY_ENV_VAR}) # xxxx
set(ENV{MY_ENV_VAR} yyyy)
message(STATUS $ENV{MY_ENV_VAR}) # yyyy
set(ENV{MY_ENV_VAR})
message(STATUS $ENV{MY_ENV_VAR}) # empty!
```