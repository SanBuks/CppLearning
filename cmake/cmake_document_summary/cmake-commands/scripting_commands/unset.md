# Unset Normal Var Or Cache Entry
```cmake
# unset(<variable> [CACHE | PARENT_SCOPE])

unset(MY_NORMAL_VAR )                  # undefined 会暴露 Cache Var
set(MY_NORMAL_VAR "")                  # empty string 不会暴露 Cache Var

unset(PARENT_NORMAL_VAR PARENT_SCOPE)  # 将上一层作用域中的变量 undefined
unset(MY_CACHE_VAR CACHE)              # 将缓存变量变为 undefined
```

# Unset Environmental Var
```cmake
# unset(ENV{<variable>})

# 将环境变量移除, 后续的引用会返回 empty string
# 只会影响当前的 CMake 进程, 不会影响调用者, 后续 build 和 test 进程和系统的环境变量
```