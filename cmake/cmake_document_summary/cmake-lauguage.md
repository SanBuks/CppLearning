# 组织架构
- 目录: CMakeLists.txt, 源文件和生成文件的子目录和顶层目录以此为准
- 脚本: xxx.cmake, 使用 `cmake -P xxx.cmake` 单纯运行脚本, 产生 build system
- 模块: xxx.cmake, 使用 `include` 载入模块

# 三种参数形式
```cmake
# 1. 括号参数
# [===[ ... ]===] 中间的等号要匹配
# 不对 ${} 和 \ 进行特殊处理
# 不可嵌套, 只忽略 opening bracket 后紧跟着的一个换行符
message(STATUS [===[
This is the first line in a bracket argument with bracket length 1.
No \-escape sequences or ${variable} references are evaluated.
This is always one argument even though it contains a ; character.
The text does not end on a closing bracket of length 0 like ]].
It does end in a closing bracket of length 1.
]===])

# 2. 引号参数
# 对 ${} 和 \ 进行特殊处理
# 行尾的 \ 表示 行连接
message("This is a quoted argument containing multiple lines.
This is always one argument even though it contains a ; character.
Both \\-escape sequences and ${variable} references are evaluated.
The text does not end on an escaped double-quote like \".
It does end in an unescaped double quote.\
line continuation
")

# 3. 非引号参数
# 连续的内容中不能包含 whitespace, (, ), #, ", or \, 除非转义
# 对 ${} 和 \ 进行特殊处理
# 可以表示 0个或 多个参数
foreach (arg
         NoSpace
         Escaped\ Space
         This;Divides;Into;Five;Arguments
         Escaped\;Semicolon)
  message("${arg}")
endforeach ()

# 非引号参数的遗留形式(不推荐再使用)
message(-Da="b c") # "-Da=\"b c\""
message(-Da=$(v))  # "-Da=$(v)"
message(a" "b"c"d) # "a\" \"b\"c\"d"
```

# 引用变量
- `${test_${var}}` 引用可嵌套
- `$CACHE{var}` 缓存变量
- `$ENV{var}` 环境变量, 像"随时更新"的缓存变量
- `if(var)` 可省略普通形式变量引用, 但是环境和缓存变量不可省略

# 注释
```cmake
# 单行注释

#[[多
   行
   注
   释]] 
```

# 控制流程
- 判断: if(), elseif(), else(), endif()
- 循环: foreach(), endforeach(), while(), endwhile(), break()
- 命令: macro(), endmacro(), function(), endfunction()

# 变量
- 变量通过字符串形式存储
- 推荐只存储字母, _ 和 -
- 变量名称大小写存在区别
```cmake
# 1. 变量定义 MY_VAR
set(MY_VAR "xxxx")

# 2. 三种作用域
# Function Scope 通过 function() 定义
# Directory Scope 通过 CMakeLists 定义
# Persistent Cache 通过 -D 或 set(CACHE INTERNAL FORCE) 定义

# 注意: 在作用域内新设的变量不会泄露在外层作用域中
function(test)
  set(MY_VAR "In Function Variable")
  message("In Function: ${MY_VAR}")   # In Function Variable
endfunction()
test()
message("Out of Function: ${MY_VAR}") # empty!

# 注意: 在内层作用域中 unset 对象对外层不影响
set(MY_VAR "Directory Variable")
function(test)
  message("In Function: ${MY_VAR}")              # Directory Variable
  unset(MY_VAR)                                  # 这里的对象更像是复制了一份
# unset(MY_VAR PARENT_SCOPE)                     # 会影响上一层作用域对象
  message("In Function(after unset): ${MY_DIR}") # empty!
endfunction()
message("Before Caller: ${MY_VAR}")              # Directory Variable
test()
message("After Caller: ${MY_VAR}")               # Directory Variable

# 3. 变量求值
#  1) 在 Function Scope 中找变量绑定 
#  2) 在 Directory Scope 中找变量绑定
#  3) 在 CACHE 中找到变量, 未找到则为 empty string 

# 注意: 尽量使用$CACHE{VAR} 直接引用 CACHE 变量

# 4. 预留的变量名称
# CMAKE_*
# _CMAKE_*
# _<name of cmake command>
```

# 列表
- 通过非引号参数表示通过 ; 分割
- ; 不能跟在 [][ 这种情况后
- list 不支持含有 ; 的字符
```cmake
# set 会将多个参数转换成 list, 如果引号参数中含有没转义的分号, 会发生意想不到的膨胀
set(srcs a.c b.c c.c) # sets "srcs" to "a.c;b.c;c.c"
set(x a "b;c")        # sets "x" to "a;b;c", not "a;b\;c"

# 细微的差别(";" follow an unequal number of [ and ] characters)
set(x a;x;[][;xxx)    # set "x" to "a;x;[][\;;xxx"
set(x a;x;[];xxx)     # set "x" to "a;x;[];xxx"
```