# Set Normal Var
```cmake
# set(<variable> <value>... [PARENT_SCOPE])
set(MY_VAR var1 var2)  # 组成 list 
set(MY_VAR)            # 空参与 unset 一致

# function / dir 作用域中新建变量, 该变量的改变不会影响上一层的变量
# function / dir 作用域中继承变量, 该变量的改变不会影响上一层的变量
# [PARENT_SCOPE] 会改变上一层变量, set, unset 情况在内
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
```cmake
# set(<variable> <value>... CACHE <type> <docstring> [FORCE])

# 增加 缓存变量, 默认只增加变量(不会更改变量)
set(MY_CACHE_VAR "xxxx" CACHE STRING "")
set(MY_CACHE_VAR "yyyy" CACHE STRING "")
message(STATUS ${MY_CACHE_VAR})  # 仍然显示 xxxx

# <type> <docstring> 用于 cmake-gui, 一般采用 STRING "" 或 INTERNAL "" (蕴含 [FORCE])

# [FORCE] 强制 overwrite cache var
set(MY_CACHE_VAR "xxxx" CACHE STRING "")
set(MY_CACHE_VAR "yyyy" CACHE INTERNAL "")
message(STATUS ${MY_CACHE_VAR})

# VERSION 3.21 之前, 增加或修改缓存变量会 unset 作用域内同名的 普通变量
cmake_policy(PUSH)
cmake_policy(SET CMP0126 OLD)               

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

# 修改
set(ENV{MY_ENV_VAR} yyyy)
message(STATUS $ENV{MY_ENV_VAR}) # yyyy

# 清空
set(ENV{MY_ENV_VAR})
message(STATUS $ENV{MY_ENV_VAR}) # empty!
```