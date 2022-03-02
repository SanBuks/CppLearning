# 2.01
> 类型 int，long，long long 和 short 的区别是什么？无符号类型和带符号类型的区别是什么？float 和 double的区别是什么？

- short 规定最小为 2B, int 为 2B, long 为 4B, long long 为 8B
- 无符号类型表达非负数, 带符号类型可表达负数但是正数范围要比无符号类型小
- float 规定最少有 6 位有效数字, double 为 10 位, 其中 float 和 double 一般用 IEEE754 标准实现, 前者占 4B, 后者占 8B

# 2.02
> 计算按揭贷款时，对于利率、本金和付款分别应选择何种数据类型？说明你的理由。

double, 需要进行浮点运算, 其中 double 在实际计算过程中要比 float 快

# 2.08
> 请利用转义序列编写一段程序，要求先输出 2M，然后转到新一行。修改程序使其先输出 2，然后输出制表符，再输出 M，最后转到新一行。
```c++
std::cout << "2M\n";
std::cout << "2\tM\n";
```

# 2.09
> 解释下列定义的含义，对于非法的定义，请说明错在何处并将其改正。

(a) std::cin >> int input_value;
(b) int i = { 3.14 };
(c) double salary = wage = 9999.99;
(d) int i = 3.14;
```c++
int input_value;
std::cin >> input_value;

double i = {3.14};

double salary, wage;
salary = wage = 9999.99; 

double i = 3.14;
```

# 2.11
> 指出下面的语句是声明还是定义：
```c++
extern int ix = 1024; // 定义
int iy;               // 定义
extern int iz;        // 声明
```

# 2.12
> 请指出下面的名字中哪些是非法的？
```c++
int double = 3.14;    // 非法, 保留字
int _;                // 函数体外非法, 不能以 _ 开头
int catch-22;         // 非法, 没有 - 特殊字符
int 1_or_2 = 1;       // 非法, 不能以数字开头
double Double = 3.14; // 合法
```

# 2.13
> 下面程序中j的值是多少？
```c++
int i = 42;
int main() {
  int i = 100;
  int j = i;  // 100
}
```

# 2.14
> 下面的程序合法吗？如果合法，它将输出什么？
```c++
int i = 100, sum = 0;
for (int i = 0; i != 10; ++i) {
  sum += i;
}
std::cout << i << " " << sum << std::endl;  // 合法 输出 : 100 55
```

# 2.15
> 下面的哪个定义是不合法的？为什么？
```c++
int ival = 1.01;  
int &rval1 = 1.01;  // 不合法, 不能绑定到字面值上
int &rval2 = ival;
int &rval3;         // 不合法, 没有初始化
```

# 2.16
> 考察下面的所有赋值然后回答：哪些赋值是不合法的？为什么？哪些赋值是合法的？它们执行了哪些操作？
```c++
int i = 0, &r1 = i;
double d = 0, &r2 = d;
/* ---------------------------------*/
r2 = 3.14159;  // 合法 d = 3.14159
r2 = r1;       // 合法 d = 0, int=>double
i = r2;        // 合法 double=>int
r1 = d;        // 合法 double=>int
```

# 2.17
> 执行下面的代码段将输出什么结果？
```c++
int i, &ri = i;
i = 5; ri = 10;
std::cout << i << " " << ri << std::endl;  // 10 10
```

# 2.18
> 编写代码分别改变指针的值以及指针所指对象的值。
```c++
#include <iostream>
int a[10] = {};
int main() {
  int *p = a;
  std::cout << p << " " << *p << std::endl;
  *(p + 1) = 2;
  std::cout << p + 1 << " " << *(p + 1) << std::endl;
  return 0;
}
//0x4041a0 0
//0x4041a4 2
```

# 2.20
> 请叙述下面这段代码的作用。
```c++
int i = 42;
int *p1 = &i; 
*p1 = *p1 * *p1;  // i = 42 * 42
```

# 2.21
> 请解释下述定义。在这些定义中有非法的吗？如果有，为什么？
```c++
int i = 0;
double *dp = &i;  // 非法, 无法将 int * 转化为 double *
int *ip = i;      // 非法, 无法将 int 转化为 int *
int *p = &i;      // 合法
```

# 2.22
> 假设 p 是一个 int 型指针，请说明下述代码的含义。
```c++
if (p)  // 如果 p 不是一个空指针则执行
if (*p) // 如果 p 指向的int数非零则执行
```

# 2.25
> 说明下列变量的类型和值。
```c++
int *ip, i, &r = i;  // ip: int* | i  : int  | r: i 的引用
int i, *ip = 0;      // i : int  | ip : int*
int *ip, ip2;        // ip: int* | ip2: int
```

# 2.26
> 下面哪些语句是合法的？如果不合法，请说明为什么？
```c++
const int buf;      // 非法, 需要初始化
int cnt = 0;        // 合法
const int sz = cnt; // 合法
++cnt; ++sz;        // 非法, const 对象不可改变
```

# 2.32
> 下面的代码是否合法？如果非法，请设法将其修改正确。
```c++
int null = 0, *p = null;  // 非法 
// int null = 0, *p = nullptr;
```

# 2.35
> 判断下列定义推断出的类型是什么，然后编写程序进行验证。
```c++
const int i = 42;    
auto j = i; const auto &k = i; auto *p = &i;
// j : int | k : const int & | p : const int * 

const auto j2 = i, &k2 = i;
// j2 : const int | k2 : const int &
```

# 2.36
> 关于下面的代码，请指出每一个变量的类型以及程序结束时它们各自的值。
```c++
int a = 3, b = 4;
decltype(a) c = a;    // c : int   | c = 3
decltype((b)) d = a;  // d : int & | a = 3
++c;                  // c = 4
++d;                  // d = 4
// a = 4
```

# 2.37
> 赋值是会产生引用的一类典型表达式，引用的类型就是左值的类型。也就是说，如果 i 是 int，则表达式 i=x 的类型是 int&。
> 根据这一特点，请指出下面的代码中每一个变量的类型和值。
```c++
int a = 3, b = 4;
decltype(a) c = a;      // c : int   | c = 3
decltype(a = b) d = a;  // d : int & | d = a = b = 4
```

# 2.39
> 编译下面的程序观察其运行结果，注意，如果忘记写类定义体后面的分号会发生什么情况？记录下相关的信息，以后可能会有用。
```c++
struct Foo { /* 此处为空  */ } // 注意：没有分号
int main() {
  return 0;
}
/*
error: expected ‘;’ after struct definition
 struct Foo { /* 此处为空  */ } 
*/
```

# 2.40
> 根据自己的理解写出 Sales_data 类，最好与书中的例子有所区别。

见 sales_data.cc

# 2.41
> 使用你自己的Sale_data类重写1.5.1节（第20页）、1.5.2节（第21页）和1.6节（第22页）的练习。
> 眼下先把Sales_data类的定义和main函数放在一个文件里。

略

# 2.42
> 根据你自己的理解重写一个Sales_data.h头文件，并以此为基础重做2.6.2节（第67页）的练习。

见 sales_data.cc