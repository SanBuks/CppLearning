# add_executable
```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL] [source1] [source2 ...])

# 1. <name> 在整个 project 必须是唯一的, 最终生成可执行文件的名字根据平台实现而不同
#    [source] 可用 生成表达式
#    [source] 可省略, 通过 target_sources() 增加源文件

# 2. 可通过 RUNTIME_OUTPUT_DIRECTORY 和 OUTPUT_NAME 更改 target 输出路径和名称
set(MY_DIR ${CMAKE_SOURCE_DIR}/my_build)
set_target_properties(hello_cmake PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${MY_DIR}
                      OUTPUT_NAME test_name)
# 3. 别名: add_executable(<name> ALIAS <target>) 
#    别名可用于读属性, 作为 custom commands, custom targets 的可运行文件, 通过 if(TARGET) 判断
#    别名不可用于修改属性如: set_property(), set_target_properties(), target_link_libraries()
#    别名不可用于 install, export

# [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL] (*略)
# Imported Executables (*略)
```

# set_target_properties
```cmake
set_target_properties(target1 target2 ...
                      PROPERTIES prop1 value1
                      prop2 value2 ...)
```
# target_sources

# project
- 必须在 top-level 的 CMakeLists 中直接调用, 通过 include() 间接调用是不推荐的
- 在 top-level 的 CMakeLists 中不调用会生成默认调用, 并警告
```cmake
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])

# 1. PROJECT_XXX 一般都有 CMAKE_PROJECT_XXX 对应, 是最顶层 dir 的相关变量

# 2. project 的代码注入
#  1) cmake -DCMAKE_PROJECT_INCLUDE_BEFORE=D:/Project/LEARNING/CppLearning/cmake/xxxx.cmake ..
#  2) INCLUDE_BEFORE 在 <PROJECT-NAME>_INCLUDE_BEFORE 之前
# CMAKE_PROJECT_INCLUDE_BEFORE / CMAKE_PROJECT_<PROJECT-NAME>_INCLUDE_BEFORE
# CMAKE_PROJECT_INCLUDE        / CMAKE_PROJECT_<PROJECT-NAME>_INCLUDE

# 3. 相关变量
# <PROJECT-NAME>
# PROJECT_NAME,          CMAKE_PROJECT_NAME
# PROJECT_SOURCE_DIR,    <PROJECT-NAME>_SOURCE_DIR  
# PROJECT_BINARY_DIR,    <PROJECT-NAME>_BINARY_DIR
# PROJECT_IS_TOP_LEVEL,  <PROJECT-NAME>_IS_TOP_LEVEL

# [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
# PROJECT_VERSION,       <PROJECT-NAME>_VERSION
# PROJECT_VERSION_MAJOR, <PROJECT-NAME>_VERSION_MAJOR
# PROJECT_VERSION_MINOR, <PROJECT-NAME>_VERSION_MINOR
# PROJECT_VERSION_PATCH, <PROJECT-NAME>_VERSION_PATCH
# PROJECT_VERSION_TWEAK, <PROJECT-NAME>_VERSION_TWEAK

# [DESCRIPTION <project-description-string>]
# PROJECT_DESCRIPTION,   <PROJECT-NAME>_DESCRIPTION

# [HOMEPAGE_URL <url-string>]
# PROJECT_HOMEPAGE_URL, <PROJECT-NAME>_HOMEPAGE_URL

# [LANGUAGES <language-name>...]
# languages: C(default), CXX(default), CUDA, OBJC, OBJCXX, Fortran, HIP, ISPC, ASM
# LANGUAGES NONE / LANGUAGES: 关闭任何语言的支持
```