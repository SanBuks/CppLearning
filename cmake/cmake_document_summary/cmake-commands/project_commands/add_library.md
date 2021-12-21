```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
# <name> 整个项目中必须唯一, 实际的生成名字依赖于平台(lib<name>.a / <name>.lib)
# 可用 generator expressions
# <source> 可省略, 通过 target_sources() 增加

# [STATIC, SHARED, or MODULE] 决定库的类型为: 静态库, 动态库或插件 dlopen-like 类 
```