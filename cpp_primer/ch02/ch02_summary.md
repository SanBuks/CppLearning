# 1. 基本数据类型
## 1.1 类型和大小
- 总体分为算术类型 (布尔, 字符, 整型, 浮点型) 和 void 类型

| 算术类型    |最小字节数/有效位数|实际大小(Linux64) |字面值前后缀|
| ---------- | -------------- | -------------- | --------------- |
|bool        |undefined       |1               |default          |
|char        |1               |1               |^u8 (UTF-8)      |
|wchar\_t    |2               |4               |^L  (Wide Char)  |
|char16\_t   |2               |2               |^u  (UTF-16)     |
|char32\_t   |4               |4               |^U  (UTF-32)     |
|short       |2               |2               |--               |
|int         |2               |4               |default          |
|long        |4               |8               |L$               |
|long long   |8               |8               |LL$              |
|float       |6 sig           |4               |F$               |
|double      |10 sig          |8               |default          |
|long double |10 sig          |16              |L$               |

- 字节: 一般与 char 相同 8bit, 代表最小可寻址内存块 
- 字: 一般与机器字长相同 32/64bit, 代表存储的基本单元
- char: 没有规定 char 是 unsigned 还是 signed, 使用 char 作为小整数需要明确指明是 unsigned char
- 整数类型大小关系: long long >= long >= int >= short
- 确定长度的类型: int64\_t, 保证移植性
- 字面值无符号后缀: 可用 U 为后缀 指定 算术类型为无符号类型
- LLP(Win64) 规范下: int - 4B; long - 4B; wchar_t -2B (代表 UTF-16)
- LP(Unix64) 规范下: int - 4B; long - 8B; wchar_t -4B

## 1.2 类型转换
- 布尔类型和非布尔类型转换: 以0/1为基准
- 浮点与整数转换: 精度会有损失
- 赋予无符号类型超出范围数值: 按模运算处理
- 赋予带符号类型超出范围数值: 未定义
- 同基本类型无符号数与有符号数相运算: 转换成无符号数

> 注意无符号数与有符号数的混用会导致意想不到的结果!

## 1.3 字面值常量
- 字面值常量: 指的是 如 42, nullptr, true, false 一望便知值大小的常量, 类型可由前后缀指定
- 负字面值: "-32" 的字面值是 32, 然后对其取反
- 整型的八, 十六进制: 以 0 和 0x 开头 按 int(unsigned), long(unsigned), long long(unsigned) 最小范围转换
- 整型十进制类型: 按 int, long, long long 最小范围转换
- 浮点数: 可以用 e 或 E 标识, 如 3.15159E10 默认为double类型
- 字符串: "12345" 含有尾 '\0', 是左值, 可取址, "123""321" 等价于 "123321"
```c++
// 字面值后缀只是表示最小类型, 如果超出会赋予更大类型

// 2147483647
std::cout << std::numeric_limits<long>::max() << "\n";
// 9223372036854775808
std::cout << std::numeric_limits<long long>::max() << "\n";

auto it = 2147483648L;            // long long
auto ht = 9223372036854775808UL;  // unsigned long long
```

## 1.4 转义字符
- 转移字符: 不可打印 或 特殊含义的字面值
- 举例: 回车: \r (Carriage Return), 换行: \n (Linefeed), \\\\:  '\'
- \x1324 十六进制数, 代表字符集的码点, 后跟多个数字 
- \123 八进制数, 代表字符集的码点, 后跟至多3个数字 

# 2. 变量
## 2.1 变量或对象
```c++
int a;      // 定义对象, 及开辟一块能存储数据并具有某种类型的内存空间
int a = 3;  // 初始化对象, 开辟的同时赋予一个初始值
a = 4;      // 赋值, 擦除当前值替换为新值
```

## 2.2 初始化
- 内置类型在静态内存中默认初始化为0, 在函数体内不被初始化且值未定义
- 其他类型默认初始化取决于默认构造函数
```c++
int a{3.14};          // 列表初始化, 发生隐式转换会报错
int a(3.14);          // 括号初始化, 发生隐式转换不会报错
int a;                // 默认初始化
vector<int> vec(10);  // 给容器内的 10 个元素进行值初始化
```

## 2.3 声明与定义
- 用到其他编译单元内定义的变量必须包含该变量的声明, 声明可以有多个, 定义只有一次
```c++
extern double pi;         // 声明变量, 规定类型和名字, 让程序所知, 并不申请空间
extern double pi = 3.14;  // 定义变量, 等价为 double pi = 3.14;
int func() {
  extern int a = 3;       // 函数体内使用这种方式定义变量会报错
  return a;
}
```

## 2.4 标识符
- 由字母, 数字和下划线组成, 以字母或下划线开头
- 无长度限制, 大小写敏感, 存在保留关键字
- 除了保留字由于为标准库保留了一些名字 还会存在一些限制: 
```c++
// 用户自定义标识符的限制
int _a = 3;     // 函数体外, 不能以下划线开头, 存在特殊定义的宏
int main() {
  int __A = 0;  // 不能以 __开头, 比如 __FUNCTION__ 表示编译的函数名字
  int _A = 1;   // 不能以 _[A-Z]开头, 存在特殊定义的宏
  int _b = 2;   // 可以 _[a-z]开头
  return 0;
}
```

# 3. 复合类型
## 3.1 左值引用
- int &lref = var; 引用初始化时会与初始值进行 "绑定"
- 引用的性质: 
  - 即别名非对象
  - 引用本身无引用
  - 引用必须初始化, 必须与对象绑定, 不能是字面值或某表达式结果
- 引用必须绑定在同一类型对象上, 除非:
  - const int &a = 3;
  - 基类引用绑定到派生类上

## 3.2 指针
- 指针性质: 
  - 是对象, 无需定义时赋值
  - 包含指向某个对象的地址, 由于引用不是对象故不可指向引用
  - 允许指针拷贝和赋值, 
  - 赋值时类型与所指类型必须一致 (除非void \*)
- 指针的值有:
  - &var
  - (&array)+1
  - nullptr/0/NULL
  - 无效值
- 空指针: NULL 定义在 <cstdlib> 为宏, 值为 0, 尽量用 nullptr
- void 类型指针:
```c++
int *ip = &var;
// 0. void指针可被赋予任何类型的指针值
void *p = anyptr;  
// 1. void指针可被存放任意对象地址
void *q = &anyobj;  
// 2. 作为函数输入输出
void *func(void *pp, void qq) {  
// 3. 比较
  return pp < qq ? pp: qq;  
}
// 4. 但不可访问内存 除非 reinterpret_cast<int *>(pp)
// 总结: void 指针可以理解为丢掉了位模式的指针, 满足值的一切性质
```

## 3.3 复合类型声明
- 复合类型 = 基本数据类型 + 声明符列表 (声明符列表含有修饰符和标识符)
- 注意基本数据类型和局部修饰符的区别
- 解读规则: 从右往左读, 第一个修饰符产生本质影响
```c++
int *p1, *p2;    // p1 p2 均为指针类型
int *pp1, pp2;   // pp1 为指针类型 pp2 为int 类型

// 区别在于 类型修饰符 * 只作用局部变量, 而基础数据类型仍是 int

int * *ppp1;      // 表示指向int指针的指针,且可以扩展
int * &p1 = ptr;  // 表示ptr指针的引用,且指针指向一个整型数 
```

# 4. const 限定符
## 4.1 const 限定类型
- 限定基本数据类型, 作用于定义的所有对象(与局部修饰符不同之处)
- 必须初始化: const 对象不能改变所以必须初始化
- 有效范围: cosnt 对象在编译过程中会被替换成对应值, 只在编译单元内有效
```c++
// a.cpp
#include <iostream>
const int a = 3;
int main() {
  std::cout << a;
  return 0;
}
// b.cpp
const int a = 2;
// g++ a.cpp b.cpp -o test 运行后结果为3

// a.cpp
#include <iostream>
int a = 3;
int main() {
  std::cout << a;
  return 0;
}
// b.cpp
int a = 2;
// g++ a.cpp b.cpp -o test  链接出现错误 multiple definition of `a'
// 把 b.cpp 改为const int a=2; 运行后结果为3

// 最终验证其他文件内的同名 const 对象为独立对象,只在文件内有效
// 非 const 对象在多处定义会出现链接错误(需要extern)
```

- extern const 在某个文件内定义一次, 在其他文件类可以多次声明来使用同一个对象
```c++
// a.cpp
#include <iostream>
extern const int a;      //声名在其他文件中定义的a 或者 #include"b.h"也可
int main() {
    std::cout << a;
    return 0;
}
// b.h
extern const int a;      // 在头文件中只声明a
// b.cpp
#include "b.h"
extern const int a = 2;  // 定义a 其中extern可以省略
// g++ a.cpp b.cpp -o test 运行后结果为 2
// 最终达成了在一个文件中使用在其他文件中定义好的 const 对象
```

## 4.2 对常量的引用
- 对常量的引用表示不能改变所引用对象的值, 而引用对象不必为常量
- const int &r1 = var; 其中 var 可以是:
  - 可转换为 int 的表达式结果
  - 非常量对象
  - 字面值
- 对常量的引用与赋值对象类型不一样时, 上述操作编译时等价为
```c++
// 1. 为了保证 对常量引用的绑定类型 与 被绑定的对象类型 相同需要创建一个临时量
const int temp = var;  // 转换成temp, temp 是临时常量
// 2. 通过对常量引用将临时量保存下来(固化), 临时量不会被立马释放
const int &r1 = temp;
// 3. 如果 temp 不是常量 即等价为
int temp = var;
int &r1 = temp;        // 对于 r1 的更改 只会改变 temp 无法改变 var
                       // 产生了语义的冲突所以 temp 必须为 常量
```

- const int &r1 = var; 转换的验证:
```c++
int a = 0; const int &b = a;       // &a: 0x60fe80      &b: 0x60fe80
const int a = 10;                  // &a: 0x7ffd6662670c  将字面值转换为 const int 类型
double a = 2.3; const int &b = a;  // &a: 0x60fe84      &b: 0x60fe78 类型转化中产生了新临时量, 地址不同
```

## 4.3 指针与 const
- 指向常量的指针: 不能通过指针改变所指对象的值, 可以指向不是常量的同类对象
- 常量指针: 指针是一个const对象, 必须初始化且无法改变内容, 且必须类型一致, 但所指内容可以更改
- 顶层 const: 指针 (和其他任意对象) 本身为常量 
- 底层 const: 指针 (和引用) 所指对象为常量
- 顶层 const 被拷贝时无影响, 底层 const 被拷贝时需要所赋值的对象所指为常量 (简言之, 底层 const 必须相同) 
```c++
int main() {
  int var = 0;                                 // 普通变量
  const int const_var = 0;                     // 顶层 const 作为常量必须初始化
  const int &ref_to_const = var;               // 底层 const 作为引用必须绑定
  const int *ptr_to_const;                     // 底层 const 指针 可以不初始化
  int *const const_ptr = &var;                 // 顶层 const 指针 作为常量必须初始化
  const int *const const_ptr_to_const = &var;  // 顶层 + 底层 const 作为常量必须初始化
  const int *p, *a;                            // 类型限定符与一般修饰符不同 const限定了基础类型
  return 0;
}
```

## 4.4 数组与 const
```c++
const int a[3] = {1, 2, 3};  // 所有数组元素皆为顶层 const
a[0] = 2;                    // error 
auto b = a;                  // a 退化成 const int *
```

# 5. 常量表达式
## 5.1 基本概念
- 常量表达式: 编译过程中可以得到计算结果的表达式, 在语义上提供常量的支持, 主要用于模板编程
- constexpr 说明符: 指定变量或函数的值可以在常量表达式中出现, 一般由类型和初始值决定
- 字面值类型: 在定义时可以被 constexpr 限定的类型, 有: 算术类型, 指针引用, 自定义的字面值常量类和枚举类型

## 5.2 constexpr 算术类型
```c++
// 算术类型变量是否为常量表达式 只看 是否为顶层 const

int static_variable = 1;
const int const_static_variable = 1;
int main() {
  int nostatic_variable = 1;
  const int const_nostatic_variable = 1;

  // constexpr int constexpr_variable1 = static_variable;       // 必须为顶层const
  // constexpr int constexpr_variable2 = nostatic_variable;     // 必须为顶层const
  constexpr int constexpr_variable3 = const_static_variable;    // 不分静态内存
  constexpr int constexpr_variable4 = const_nostatic_variable;  // 不分静态内存

  return EXIT_SUCCESS;
}
```

## 5.3 constexpr 引用
```c++
// 引用是否为常量表达式 看绑定的对象是否是一个静态内存中定义的对象

int static_variable = 1;
const int const_static_variable = 1;
int main() {
  int nostatic_variable = 1;
  const int const_nostatic_variable = 1;

  // constexpr int &constexpr_reference3 = nostatic_variable;         // 必须是静态内存中定义
  // constexpr const int &constexpr_reference4 = const_nostatic_variable;
  constexpr int &constexpr_reference1 = static_variable;
  constexpr const int &constexpr_reference2 = const_static_variable;  // constexpr 不提供引用的底层 const 语义
                                                                      // 仅仅表示是否绑定静态内存对象
                                                                      // 需要 const 提供底层 const 语义
  return EXIT_SUCCESS;
}
```

## 5.4 constexpr 指针
```c++
// 指针是否为常量表达式 看绑定的对象是否是一个静态内存中定义的对象

int static_variable = 1;
const int const_static_variable = 1;
int main() {
  int nostatic_variable = 1;
  const int const_nostatic_variable = 1;

  // constexpr int *constexpr_pointer3 = &nostatic_variable;  // 必须是静态内存中定义
  // constexpr const int &constexpr_pointer4 = &const_nostatic_variable;
  constexpr int *constexpr_pointer1 = &static_variable;       // 必须是静态内存中定义
  constexpr const int *constexpr_pointer2 = &const_static_variable;
  // constexpr_pointer1 = nullptr;                            // constexpr 提供顶层 const 语义
                                                              // 需要 const 提供底层 const 语义
  return EXIT_SUCCESS;
}
```

## 5.5 C++ 内存区域分类(由高到低)
- 栈区: 编译器由高到底分配, 由低到高释放, 存放函数的参数值, 局部变量的值等
- 共享库: 动态链接的内存映射区
- 堆区: 手动由低到高分配, 由高到底释放, 程序结束时由 OS回收
- 全局区(静态区): 非 static 全局变量 和 static 全局变量的存储在一块, 未初始化存放在BSS段, 初始化存放在DATA段
- 文字常量区: 常量字符串存放区(字符串字面值常量是一个左值), 程序结束后由系统释放
- 程序代码区: 存放函数体的二进制代码
```c++
int a = 0;                  // 全局区 已初始化
char *p1;                   // 全局区 未初始化

int main() {                
  int b;                    // 栈区
  char s[] = "abc";         // 栈区
  char *p2;                 // 栈区
  char *p3 = "123456";      // "123456" 在文字常量区, p3 在栈区
  static int c = 0;         // 全局区(静态) 已初始化
  
  p1 = (char *)malloc(10);  // 堆区
  p2 = (char *)malloc(20);
  
  strcpy(p1, "123456");     // "123456\0" 放在常量区
  return 0;
} 
```

- 非 static 全局变量: 静态存储方式, 作用域是整个源程序
- static 全局变量: 静态存储方式, 作用域是该源文件内有效, 对其他源文件隐藏
- static 局部变量: 静态存储方式, 作用域是某个范围内, 但直到程序结束才销毁
- static 大致三种语义: 
  - 编译单元内的全局变量, 对其他源文件不可见
  - 作用域内的不会释放变量, 与自动变量相对 
  - 没有 this 指针的成员函数

# 6. 处理类型与类型推导
## 6.1 类型别名
```c++
// 用 typedef 声明别名
typedef int T1, *T2;  // T1 别名 int, an2 别名为 int *, 注意别名作为整体是一个基础类型
const T2 a1;          // const 限定的是 T2 整体, a1 是指向 int 的常量指针
const T2 *a2;         // a2是一个底层 const 指针, 指向 指向 int 的指针

// 用 using 声明别名
using an1 = int;      // an1 是 int 别名
using an2 = int *;    // an2 是 int * 别名
```

## 6.2 auto 类型说明符
```c++
// auto 推导类型
auto a = 0, *p = &a;       // 基本类型为 int

const int b = 3;
const auto c = 1, &d = b;  // 基本类型必须一致否则出错, 这里基本类型为 const int
                           // 如果不加 const 则前者推断为 int, 后者推断为 const int 而出错

int a = 10; auto b = a; const auto c = a;                // 忽略顶层 const; b 是 int 型; c 是 const int 型
int a = 10, &b = a; auto c = b;                          // 以引用所指类型为准 c 是 int 型
int a = 10; const int b = 10; auto c = &a; auto d = &b;  // 保留底层 const, c 是 int*, d 是const int*
int a = 10; auto &b = a; const auto &c = 100;            // 可以通过引用修饰, b 是 int &, c是 const int &

int a = 10; auto const b = &a;                           // b 是 int * const p 类型
int a = 10; const const b = &a;                          // b 任然是 int * const p 类型
int a = 10; const auto const b = &a;                     // error: 重复 const, 所以 auto 无法对指针额外添加 底层 const 限定
                                                         // 除非对象本身是 const 类型
```

- 数组名在推导中的 "退化" 问题: 
```c++
int c[10];      // c 本身是 int [10] 类型
auto a = c;     // 推导过程中, c 作为右值会退化成 int *

// 防止指针类型退化
int a1[10][2] = {};
auto a2 = a1;   // a2 从 int[10][2] 退化成 int (*)[2]
auto a3 = &a1;  // a1 无法为右值所以作为左值数组, a3 从 int[10][2] 推导出 int (*)[10][2] 类型
auto &a4 = a1;  // a1 无法为右值所以作为左值数组, a4 防止退化 为 int (&)[10][2] 类型
```

## 6.3 decltype 类型指示符
- 返回表达式结果对应的类型, 如果表达式结果为左值则返回引用相关类型, 如果是右值则返回原来类型
```c++
// 表达式是 id-expression(标识符表达式) 则返回结果的具体类型
int a = 0, &b = a; 
decltype(b) c = a;                          // b 是 id-expression, 返回相同的类型, c 是 int&
decltype(b + 0) d = a;                      // b + 0 是一个右值, 返回类型为 int
decltype(a) e = a;                          // a 是 id-expression, 返回相同的类型, a 是 int 
                                            // 如果 a 为 const int 返回结果类型: const int

// 表达式不是 id-expression 则返回结果的 类型 + value-category
int a = 0; decltype((a)) b = a;             // b 是int&, 括号表达式   结果为左值
int a = 0, *b = &a; decltype(*b) c = a;     // b 是int&, 解引用表达式 结果为左值
int a = 0, b = 2;   decltype(b = a) c = a;  // b 是int&  赋值表达式   结果为左值

// 表达式或对象作为数组 则返回结果类型为数组类型
int c[10]; decltype(c) a = {};              // a 是十个整型数的数组
```

# 7. 头文件
- 通常将类, const, constexpr, inline 函数等只能被定义一次的实体放在头文件中
- 通过头文件保护符来避免重复, 注意一定要唯一
```c++
#ifndef FILENAME_H 
#define FILENAME_H 
// .....
#endif
```

# 8. 字符集与编码\*
## 8.1 字符集 
### ASCII 字符集
- 一字节大小, 同时也是编码方式
- 主要字符集: 0x00-0x7F,  拓展字符集: 0x80 - 0xFF

### GB2312 字符集
- 两字节大小, 同时也是编码方式
- 两个拓展字符集连在一块为汉字(宽字符), 其余为ASCII字符
- 高字节 0xA1-0xF7, 低字节 0xA1-0xFE

### GBK 字符集
- 两字节大小, 同时也是编码方式
- 前者为拓展字符后者为任意字符链接一起为汉字(宽字符), 其余为ASCII字符
- 高字节为拓展字符, 低字节为任意编码

### UCS 字符集
- UCS 2: U+0000～U+FFFF
- UCS 4: U+00000000～U+7FFFFFFF 目前只用到了17个 (0x00 - 0x10) 码点平面

## 8.2 编码集
### UTF-8
- UTF-8使 编码单元为 1 字节, 长度是 1-4 个编码单元, 不固定编码长度
```text
0zzzzzzz :
0zzzzzzz 

00000yyy yyzzzzzz :
110yyyyy 10zzzzzz

xxxxyyyy yyzzzzzz :
1110xxxx 10yyyyyy 10zzzzzz 

000wwwxx xxxxyyyy yyzzzzzz :
11110www 10xxxxxx 10yyyyyy 10zzzzzz 
```

### UTF-16
- UTF-16 编码单元为 2 字节, 长度是1-2 个编码单元, 不固定编码长度
- 基本平面中的 U+0000 至 U+D7FF 和 从U+E000 至 U+FFFF 与 UCS 4 码点对应
- 辅助平面需要将码点转换成代理对, 按高低位分有 前导代理和后尾代理
- 缺点: ASCII 编码增加了一倍长度, 同时汉字编码减少了一个字节
```text
转换流程 :
1. 0x10437 减去 0x10000，结果为0x00437，二进制为 0000 0000 0100 0011 0111
2. 分割它的上10位值和下10位值（使用二进制）：0000 0000 01 和 00 0011 0111
3. 添加 0xD800 到上值，以形成高位：0xD800 + 0x0001 = 0xD801
4. 添加 0xDC00 到下值，以形成低位：0xDC00 + 0x0037 = 0xDC37

根据 前缀 和 字符类型 可以快速分辨是否是代理对还是辅助平面 :
也可 根据 前缀自同步
1. 1101 10: 前导代理 定位到下一个字符的代码单元
2. 1101 11: 后导代理 出错或者映射到原来 UCS 2对应的码点
3. 其他: 基本平面中的码点
```

- 编码模式: 存在大小尾序, 为了辨别可以加上BOM(FF FE 小尾) 加以辨别, 故存在四种编码模式

### UTF-32
- UTF-32 编码长度是固定的为四字节
- UTF-32 中的每个编码 与 UCS 4 的码位数值完全一致
- 空间浪费较多, 一般不用

> cmd 设置 UTF-8 编码 chcp(.com) 65001 设置 GBK 编码 chcp 963

### BOM
- 字节顺序标记 (byte-order mark) 是位于码点U+FEFF的统一码字符的名称, 作用如下
  - 表示文字流非常有可能是 Unicode 编码, 且标识是哪一种编码
  - 在 16 位和 32 位的情况下, 文字流的字节顺序

| 编码           | 十六进制编码   |
| -------------- |------------- |
| UTF-8(一般没有) | EF BB BF     |
| UTF-16(大端序)  | FE FF        |
| UTF-16(小端序)  | FF FE        |
| UTF-32(大端序)  | 00 00 FE FF  |
| UTF-32(小端序)  | FF FE 00 00  |