> 3.22.1 2021/12/09 新增 Build Specification and Usage Requirements

# Build Specification and Usage Requirements
```cmake
# 以下命令对目标设定了 
# 构建设定(build specification), 产生属性 XXX, 表示构建设定为目标所用
# 使用条件(usage requirements), 产生属性 INTERFACE_XXX, 表示使用条件为使用目标者所用
target_include_directories() # 增加寻找头文件的目录 INCLUDE_DIRECTORIES & INTERFACE_INCLUDE_DIRECTORIES
target_compile_definitions() # 增加宏定义 COMPILE_DEFINITIONS & INTERFACE_COMPILE_DEFINITIONS
target_compile_options()     # 增加编译选项 COMPILE_OPTIONS & INTERFACE_COMPILE_OPTIONS
target_link_libraries()      # 增加链接库 LINK_LIBRARIES & INTERFACE_LINK_LIBRARIES

# 每个命令含有三种模式
# PRIVATE: 只产生 XXX, 表示该目标被复用时, 这个构建设定不会被复用
# INTERFACE: 只产生 INTERFACE_XXX, 表示该目标被复用时, 这个构建会被复用, 但是目标本身不会使用这个构建设定
# PUBLIC: 都产生
add_executable(hello_cmake1 hello.cc)
add_executable(hello_cmake2 hello.cc)
add_executable(hello_cmake3 hello.cc)

target_include_directories(hello_cmake1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(hello_cmake2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(hello_cmake3 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

# both
get_target_property(hello_cmake1_pro1 hello_cmake1 INCLUDE_DIRECTORIES)
get_target_property(hello_cmake1_pro2 hello_cmake1 INTERFACE_INCLUDE_DIRECTORIES)

# interface is empty
get_target_property(hello_cmake2_pro1 hello_cmake2 INCLUDE_DIRECTORIES)
get_target_property(hello_cmake2_pro2 hello_cmake2 INTERFACE_INCLUDE_DIRECTORIES)

# non-interface is empty
get_target_property(hello_cmake3_pro1 hello_cmake3 INCLUDE_DIRECTORIES)
get_target_property(hello_cmake3_pro2 hello_cmake3 INTERFACE_INCLUDE_DIRECTORIES)
```

## target properties
```cmake
# DEFINE_SYMBOL: 自动设定 SHARED 和 MODULE 的宏定义, 对其他类型 target 无效
add_library(hello_cmake1 SHARED hello.cc)
set_target_properties(hello_cmake1 PROPERTIES DEFINE_SYMBOL "MY_DEFINE_SYMBOL")

# CMAKE_INCLUDE_CURRENT_DIR: 默认为 OFF
# 设置为 ON 自动将 CMAKE_CURRENT_SOURCE_DIR & CMAKE_CURRENT_BINARY_DIR 加入 target 的 INCLUDE_DIRECTORIES
# (但是打印 target property 没有显示, 似乎是最后阶段再加入)
# CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE
# 同上

# POSITION_INDEPENDENT_CODE: target 是否为 position-independent 
# SHARED, MODULE 默认为 True 其他为 False
```