
# 1.01 编译器文档
> 查阅你使用的编译器文档，确定它所使用的文件命名约定。编译并运行第2页的main程序

|拓展名|文件|
|---|---|
|.cpp/.cc/.C|源文件 -E 只预处理|
|.ii|预处理后的文件 -S 只编译|
|.s| 编译过得汇编代码 -c 编译并翻译成机器代码|
|.o| 机器代码 -o file 生成可执行程序<br />(完成上述任意步骤的文件) |

`g++ man.cpp -o atest -g -Wall -std=c++11`  ( g++ 8.3.0 )

# 1.02 main返回的错误标识
> 返回值 -1 通常被当作程序错误的标识，观察你的系统如何处理main返回的错误标识。

`$ echo $?` 打印返回值

| 返回值 | 一般意义                                              |
| ------ | ----------------------------------------------------- |
| 1      | 通常的错误                                            |
| 2      | Shell 编程错误                                        |
| 126    | 命令无法执行                                          |
| 127    | 命令不存在                                            |
| 128    | 非法返回值如浮点返回值, 返回值范围为1-255(整型mod256) |
| 128+n  | 通过信号杀死进程 kill -# (exit 128+#)                 |
| 130    | 被 ^ + C 终止                                         |
| 255    | 返回值超出范围如 exit -1;                             |

- 其他值用户可自定义
```c
/* /usr/include/sysexits.h 
 *  EX_USAGE -- The command was used incorrectly, e.g., with 
 *    the wrong number of arguments, a bad flag, a bad 
 *    syntax in a parameter, or whatever. 
 *  EX_DATAERR -- The input data was incorrect in some way. 
 *    This should only be used for user's data & not 
 *    system files. 
 *  EX_NOINPUT -- An input file (not a system file) did not 
 *    exist or was not readable.  This could also include 
 *    errors like "No message" to a mailer (if it cared 
 *    to catch it). 
 *  EX_NOUSER -- The user specified did not exist.  This might 
 *    be used for mail addresses or remote logins. 
 *  EX_NOHOST -- The host specified did not exist.  This is used 
 *    in mail addresses or network requests. 
 *  EX_UNAVAILABLE -- A service is unavailable.  This can occur 
 *    if a support program or file does not exist.  This 
 *    can also be used as a catchall message when something 
 *    you wanted to do doesn't work, but you don't know 
 *    why. 
 *  EX_SOFTWARE -- An internal software error has been detected. 
 *    This should be limited to non-operating system related 
 *    errors as possible. 
 *  EX_OSERR -- An operating system error has been detected. 
 *    This is intended to be used for such things as "cannot 
 *    fork", "cannot create pipe", or the like.  It includes 
 *    things like getuid returning a user that does not 
 *    exist in the passwd file. 
 *  EX_OSFILE -- Some system file (e.g., /etc/passwd, /etc/utmp, 
 *    etc.) does not exist, cannot be opened, or has some 
 *    sort of error (e.g., syntax error). 
 *  EX_CANTCREAT -- A (user specified) output file cannot be 
 *    created. 
 *  EX_IOERR -- An error occurred while doing I/O on some file. 
 *  EX_TEMPFAIL -- temporary failure, indicating something that 
 *    is not really an error.  In sendmail, this means 
 *    that a mailer (e.g.) could not create a connection, 
 *    and the request should be reattempted later. 
 *  EX_PROTOCOL -- the remote system returned something that 
 *    was "not possible" during a protocol exchange. 
 *  EX_NOPERM -- You did not have sufficient permission to 
 *    perform the operation.  This is not intended for 
 *    file system problems, which should use NOINPUT or 
 *    CANTCREAT, but rather for higher level permissions. 
 */ 
 
#define EX_OK   0 /* successful termination */ 
 
#define EX__BASE  64  /* base value for error messages */ 
 
#define EX_USAGE  64  /* command line usage error */ 
#define EX_DATAERR  65  /* data format error */ 
#define EX_NOINPUT  66  /* cannot open input */ 
#define EX_NOUSER 67  /* addressee unknown */ 
#define EX_NOHOST 68  /* host name unknown */ 
#define EX_UNAVAILABLE  69  /* service unavailable */ 
#define EX_SOFTWARE 70  /* internal software error */ 
#define EX_OSERR  71  /* system error (e.g., can't fork) */ 
#define EX_OSFILE 72  /* critical OS file missing */ 
#define EX_CANTCREAT  73  /* can't create (user) output file */ 
#define EX_IOERR  74  /* input/output error */ 
#define EX_TEMPFAIL 75  /* temp failure; user is invited to retry */ 
#define EX_PROTOCOL 76  /* remote error in protocol */ 
#define EX_NOPERM 77  /* permission denied */ 
#define EX_CONFIG 78  /* configuration error */ 
 
#define EX__MAX 78  /* maximum listed value */ 
```

# 1.08 嵌套注释
> 指出下列哪些输出语句是合法的（如果有的话），预测编译这些语句会产生什么样的结果，实际编译这些语句来验证你的答案(编写一个小程序，每次将上述一条语句作为其主体)，改正每个编译错误。
```c++
std::cout << "/*";
std::cout << "*/";
std::cout << /* "*/" */;
std::cout << /* "*/" /* "/*" */;
/* --------------更改后---------------*/
std::cout << "/*";  // 正确
std::cout << "*/";  // 正确
std::cout << /* "*/" */";  
// 末尾多增加一个 " , 注意第一个 /* 在不在引号内
std::cout << /* "*/" /* "/*" */;  
// 正确, 只要 /* 不在字符串内则与后出现的第一个 */ 构成注释段落不管第二个在不在字符串内
// 打印结果为 : 
// 1. /**/ 
// 2. */ 
// 3. /*
```

# 1.14 for循环和while循环
> 对比for循环和while循环，两种形式的优缺点各是什么？

1. for 循环 :  
	- 优点 : 控制变量的初始化和修改都放在头部分, 形式较简洁, 且特别适用于循环次数已知的情况 
	- 缺点 : 控制变量在循环结束后自动释放, 无法跟踪
2. while 循环 : 
	- 优点 :  控制变量的初始化一般放在语句之前, 修改一般放在循环体中, 适用于循环次数不知的情况 
	- 缺点 : 循环控制变量需要额外设立, 自己释放, 形式上不如for语句简洁

# 1.15 错误信息类别
> 编写程序，包含第14页“再探编译”中讨论的常见错误。熟悉编译器生成的错误信息。

- 语法错误(syntax error)
- 类型错误(type error)
- 声明错误(declaration error)