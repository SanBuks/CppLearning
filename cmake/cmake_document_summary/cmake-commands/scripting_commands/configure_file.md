```cmake
configure_file(<input> <output> [@ONLY])

# 1. 将 @VAR@ or ${VAR} 替换为变量值, @ONLY 只替换 @VAR@
# 2. 改变宏定义:
# #cmakedefine01 VAR
# #define VAR 0
# #define VAR 1

# #cmakedefine VAR ...
# #define VAR ...
# #/* #undef VAR */

# 3. input 和 output 的相对路径为
# CMAKE_CURRENT_SOURCE_DIR
# CMAKE_CURRENT_BINARY_DIR
```

