# 1.1 构建过程
- 项目文件生成(Project File Generation): 有多种类型如 Makefiles, VS, Ninja 
  - 配置(Configure): 读取 CMakeList, 构建 CMake 项目文件
  - 生成(Generation): 生成对应项目文件
- 构建(Build)
- 测试(CTest)
- 打包(CPackage)

# 1.2 构建命令
## 1.2.1 源外构建(当前目录是构建目录)
```bash
$camke -G "UnixMakefiles" ../source              # 项目文件生成
$cmake --build . --config Release --target MyApp # 构建对象
```

## 1.2.2 命令相关参数
```bash
$cmake 
-G "UnixMakefiles"   # 指定 生成器类型
-DVar=YES            # 设置 Var 变量
--build /build/path  # 指定 构建路径
--config Debug       # 指定 配置
--target MyApp       # 指定 构建对象
```

# 1.3 一个简单项目
## 1.3.1 基本命令
```cmake
# 注释
cmake_minimum_required(VERSION 3.2.1.1)
project(MyWinGUI VERSION 1.1.1.1 LANGUAGES CXX)
add_executable(MyWinGUI WIN32 EXCLUDE_FROM_ALL main.cpp)
add_library(MyLib SHARED lib.cpp)
target_link_libraries(MyWinGUI PUBLIC MyLib)
```

## 1.3.2 定义库
```cmake
# STATIC 指定为静态库 (targetName.lib / libtargetName.a)
# SHARED 指定动态库  (targetName.dll / libtargetName.so)
# MODULE 插件或可选组件
# BUILD_SHARED_LIBS 变量设置为 TRUE, 则默认都为 SHARED 类型
```

## 1.3.3 链接库
```cmake
target_link_libraries(A PRIVATE/PUBLIC/INTERFACE B)
# PRIVATE   指定 A 库仅自己使用 B 库, 其他链接到 A 库的目标不需要 知道 B 库的存在。
# PUBLIC    指定 A 库不仅在内部使用 B 库，还在其接口中使用 B 库。使用 A 库的目标也会依赖 B 库。
# INTERFACE 用于纯头文件库
```

- 变量
- CMakeCache.txt 缓存加速多次构建

  - set/unset
  - 列表 
  - 引用变量
  - [[ ]]
  - 环境变量
  - 缓存变量
 
- 数值循环 
```cmake
foreach(i RANGE 0 10 1)
  message(STATUS "${i}")
endforeach ()

foreach(i RANGE 10)
  message(STATUS "${i}")
endforeach ()
```

# 2.1 变量
## 2.1.1 基本变量
```cmake
# 内部处理为字符串
set(List a b c)
set(List a;b;c)
set(List "as a whole")

# 源字符串
set(Mul [[
  abc 
  def
]])

# 引用变量
set(A ${List}) 

# 解除变量
set(myVar)
unset(myVar)

# 环境变量, 更改在 Build 阶段不可见
set(ENV{PATH} "$ENV{PATH}:/opt/myDir")
```

## 2.1.2 缓存变量
- 缓存变量的生命周期仅限于 CMakeLists.txt 文件的处理
- 缓存变量存储在名为 CMakeCache.txt 的特殊文件中，并且在 CMake 运行期间持久存在
- 缓存变量名称中的缓存表示了第一次运行和后续运行会产生不同影响
```cmake
set(varName value... CACHE INTERNAL "docstring" [FORCE])
# BOOL 类型缓存变量
option(optVar helpString [initialValue])

# 缓存变量以通过交互式 GUI 工具或脚本进行修改, 不必修改 CMakeLists
# set 缓存变量只会在 FORCE 关键字存在的情况下覆盖缓存变量, 定义缓存变量时, set() 更类似于设置/不设置
```


## 2.1.3 范围
- 缓存变量: 全局作用域
- 非缓存变量: 目录作用域
- 子目录和函数可以使用父作用域来继承变量
- block
```cmake
block()
  # 在进入域块时，可以看到在该时间点周围作用域中定义的所有变量的副本
  # 对域块中变量的修改都在域块的副本上执行，而周围作用域的变量保持不变
  # 在离开块域时，所有复制到块中的变量或在块中创建的变量都将丢弃
endblock()
```

## 2.1.4 PARENT_SCOPE
```cmake
set(x 1)
set(y 3)

block()
  # 改变了父作用域中的变量
  set(x 2 PARENT_SCOPE)
  # 改变了父作用域中的变量
  unset(y PARENT_SCOPE)

  # x still has the value 1 here
  message(STATUS ${x})
  # y still exists and has the value 3
  message(STATUS ${y})
endblock()

# x has the value 2 here 
message(STATUS ${x})
# y is no longer defined
message(STATUS ${y})
```

## 2.1.5 缓存与普通变量之间奇怪的操作
### option (CMP077 3.13)
```cmake
# 3.12 及以下版本
# 1) CACHE 变量不存在 或 CACHE 变量存在但没有类型
#   删除同名普通变量 (这个机制会导致第一次运行和后续运行结果不一致)
# 2) CACHE 变量存在
#   不做任何事

# 3.13 及以上版本
# 如果普通变量存在, 既不创建 CACHE 变量也不删除普通变量, 保持运行一致性
```

### set (CMP0126 3.21)
```cmake
# 3.21 以下版本
# 1) CACHE 变量不存在 或 CACHE 变量存在但没有类型 或 INTERNAL/FORCE 明确指定
#   删除同名普通变量 (这个机制会导致第一次运行和后续运行结果不一致)
# 2) CACHE 变量存在
#   FORCE/FORCE 会覆盖, 否则不做任何事

# 3.21 及以上版本
# 1) 不删除同名普通变量, 保持运行一致性
# 2) 如果 CACHE 变量不存在则会创建 (跟 option 区别的地方)
```


### unset
- 尽量用 `set(Var "")` 来防止暴露缓存变量产生问题

## 2.2.1 定义缓存变量
```bash
$cmake -D foo:BOOL=ON ...
$cmake -D "bar:STRING=This contains spaces" ...
$cmake -D hideMe=mysteryValue ...
$cmake -D helpers:FILEPATH=subdir/helpers.txt ...
$cmake -D helpers:FILEPATH=subdir/helpers.txt ...
$cmake -D helpDir:PATH=/opt/helpThings ...
```


## 2.2.2 输出变量
- `message("The value of myVar = ${myVar}\nAnd this " "appears on the next line")`

## 2.2.3 字符串操作
- string(XXX ...)

## 2.2.4 列表操作
- list(XXX ...)

## 2.2.5 数学操作
- math(XXX ...)
