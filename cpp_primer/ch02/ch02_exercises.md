# 2.03 有符号与无符号数运算
> 读程序写结果。

见下一题

# 2.04 有符号与无符号数运算
> 编写程序检查你的估计是否正确，如果不正确，请仔细研读本节直到弄明白问题所在。
```c++
// sizeof(u) == sizeof(i) 情况下: 优先转换成无符号数

unsigned u = 10, u2 = 42;  
std::cout << u2 - u << std::endl;  // 32
std::cout << u - u2 << std::endl;  // 2^32 - 32
                   
int i = 10, i2 = 42;         
std::cout << i2 - i << std::endl;  // 32
std::cout << i - i2 << std::endl;  // -32
                   
std::cout << i - u << std::endl;   // 0
std::cout << u - i << std::endl;   // 0
```

# 2.05 字面值常量与类型前后缀
> 指出下述字面值的数据类型并说明每一组内几种字面值的区别：
```c++
// 'a',  L'a',    "a",         L"a" 
// char, wchar_t, const char*, const wchar_t*

// 10,  10u,      10L,  10uL,          012,       0xC 
// int, unsigned, long, unsigned long, int 八进制, int 十六进制

// 3.14,   3.14F, 3.14L 
// double, float, long double

// 10,  10u,      10.,    10e-2 
// int, unsigned, double, double
```

# 2.06 八进制和十六进制字面值
>下面两组定义是否有区别，如果有，请叙述之：
```c++
int month = 9, day = 7;    // 十进制 9 7
int month = 09, day = 07;  // 八进制 前者出错 后者为7
// 改为 int month = 011, day = 07;
```

# 2.07 八进制和十六进制转义字符
> 下述字面值表示何种含义？它们各自的数据类型是什么？
```c++
// "Who goes with F\145rgus?\012"
// "Who goes with Fergus?" const char *

// 3.14e1L
// 31.4 long double

// 1024f
// 1024 float

// 3.14L 
// 3.14 long double
```

# 2.10 默认初始化与静态内存
> 下列变量的初值分别是什么？
```c++
std::string global_str;     // 空串
int global_int;             // 0
int main()
{
    int local_int;          // 未定义
    std::string local_str;  // 空串
}
```

# 2.19 指针与引用
> 说明指针与引用主要区别

1. 指针是对象, 引用是别名
2. 指针可以无需初始化, 可以多次赋值而引用必须初始化绑定
3. 指针通过\*来访问对象, 引用本身即对象

# 2.23 野指针
> 给定指针 p，你能知道它是否指向了一个合法的对象吗？如果能，叙述判断的思路；如果不能，也请说明原因。

1. raw pointer 不行, 要是能轻易做到的话 C语言 就不容易出内存方面的 bug
2. smart pointer可以, shared_ptr 和 weak_ptr 就可以分别用 shared_ptr::operator bool() 和 weak_ptr::expired() 判断

# 2.24 空类型指针
> 在下面这段代码中为什么 p 合法而 lp 非法？
```c++
int i = 42;
void *p = &i;   // 任何类型指针可以转换为 void *
long *lp = &i;  // int * 无法转换为 long *
```

# 2.27 底层 const 和顶层 const
> 下面的哪些初始化是合法的？请说明原因。
```c++
int i = -1, &r = 0;         // 非法, 引用r需绑定到一个左值
int * const p2 = &i2;       // i2 是 const int 非法, 是 int 合法
const int i = -1, &r = 0;   // 合法, 初始化底层引用的对象可以是表达式结果, 非常量对象, 字面值, 可转换类型的对象
const int *const p3 = &i2;  // 合法
const int *p1 = &i2;        // 合法
const int &const r2;        // 非法, 引用非对象没有顶层之说
const int i2 = i, &r = i;   // 合法
```

# 2.28 底层 const 和顶层 const
> 说明下面的这些定义是什么意思，挑出其中不合法的。
```c++
int i, *const cp;       // 非法, cp 是顶层 const 需要初始化
int *p1, *const p2;     // 非法, 同上
const int ic, &r = ic;  // 非法, ic 是顶层 const 需要初始化
const int *const p3;    // 非法, p3 是顶层 const 需要初始化
const int *p;           // 合法, p 是底层 const 可以不初始化
```

# 2.29 底层 const 和顶层 const
> 假设已有上一个练习中定义的那些变量，则下面的哪些语句是合法的？请说明原因。
```c++
i = ic;     // 合法, 顶层被拷贝不需要i是顶层
p1 = p3;    // 非法, p3是底层 const, 被拷贝时需要 p1 也需要是底层 const
p1 = &ic;   // 非法, ic 是 const, 取地址后被拷贝需要 p1 是底层 const
p3 = &ic;   // 非法, p3 是顶层 const, 不可被改变
p2 = p1;    // 非法, 同上
ic = *p3;   // 非法, 同上
```

# 2.30 底层 const 和顶层 const
> 对于下面的这些语句，请说明对象被声明成了顶层const还是底层const？
```c++
const int v2 = 0; int v1 = v2;                  // v2 : 顶层 v1 : 双非
int *p1 = &v1, &r1 = v1;                        // p1 : 双非 r1 : 双非
const int *p2 = &v2, *const p3 = &i, &r2 = v2;  // p2 : 底层 p3 : 双层 r2 : 底层
```

# 2.31 底层 const 和顶层 const
> 假设已有上一个练习中所做的那些声明，则下面的哪些语句是合法的？请说明顶层const和底层const在每个例子中有何体现。
```c++
r1 = v2;  // 合法
p1 = p2;  // 非法, p2 底层需要 p1 也是底层
p2 = p1;  // 合法, p1 双非可以被拷贝给底层 p2
p1 = p3;  // 非法
p2 = p3;  // 合法, p3 是双层可以拷贝给底层 p2
```

# 2.33 auto 推断
> 利用本节定义的变量，判断下列语句的运行结果。

见下一题

# 2.34 auto 推断
> 基于上一个练习中的变量和语句编写一段程序，输出赋值前后变量的内容，你刚才的推断正确吗？如果不对，请反复研读本节的示例直到你明白错在何处为止。
```c++
#include <iostream>
int main() {
  int i = 0, &r = i;
  const int ci = i, &cr = ci;
  auto a = r;
  auto b = ci;
  auto c = cr;
  auto d = &i;
  auto e = &ci;
  auto &g = ci;

  a = 42;  // 正确, a : int
  b = 42;  // 正确, b : int, 乎略顶层const 
  c = 42;  //*正确, c : int, 以引用绑定类型为准, 引用绑定为 const int, 忽略顶层 const
  d = 42;  // 非法, d : int *, int 需要强制类型转化为 int* 
  e = 42;  // 非法, e : const int *, 同上
  g = 42;  // 非法, g : const int &, 指向常量的引用无法改变值
  return 0;
}
```

# 2.38 decltype 与 auto 区别
> 说明由decltype 指定类型和由auto指定类型有何区别。
> 请举一个例子，decltype指定的类型与auto指定的类型一样；再举一个例子，decltype指定的类型与auto指定的类型不一样。

1. auto 忽略顶层const, 忽略& 而 decltype 不忽略
2. decltype 可以用 (), 赋值表达式, 解引用等左值表达式来获得相应的引用类型
3. 数组对象在 auto 推断中会产生退化 (除非用 auto &it = array 指向数组), decltype() 保留数组类型