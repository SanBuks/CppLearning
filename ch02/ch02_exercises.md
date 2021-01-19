## 第二章 习题
### 2.01
> 类型 int，long，long long 和 short 的区别是什么？无符号类型和带符号类型的区别是什么？float 和 double的区别是什么？

short规定最小为2B, int 为2B, long为4B, long long为8B. 无符号类型表达非负数, 带符号类型可表达负数但是正数范围要比无符号类型小. float规定最少有6位有效数字, double为10位, 其中float和double一般用IEEE754标准实现, 前者占4B, 后者占8B

### 2.02
> 计算按揭贷款时，对于利率、本金和付款分别应选择何种数据类型？说明你的理由。

浮点类型 : double, 需要进行浮点运算, 其中double在实际计算过程中要比float快

### 2.03
> 读程序写结果。

### 2.04
> 编写程序检查你的估计是否正确，如果不正确，请仔细研读本节直到弄明白问题所在。
```c++
unsigned u = 10, u2 = 42;  
std::cout << u2 - u << std::endl; // 32
std::cout << u - u2 << std::endl; // 2^31-32
int i = 10, i2 = 42;
std::cout << i2 - i << std::endl; //32
std::cout << i - i2 << std::endl; //-32
std::cout << i - u << std::endl;  //0
std::cout << u - i << std::endl;  //0
```

### 2.05
> 指出下述字面值的数据类型并说明每一组内几种字面值的区别：
```c++
// 'a', L'a', "a", L"a" 
(char ; wchar_t ; const char* ; const wchar_t*)
// 10, 10u, 10L, 10uL, 012, 0xC 
(int ; unsigned ; long ; unsigned long ; int 八进制 ; int 十六进制)
// 3.14, 3.14f, 3.14L 
(double ; float ; long double)
// 10, 10u, 10., 10e-2 
(int ; unsigned ; double ; double)
```

### 2.06
>下面两组定义是否有区别，如果有，请叙述之：
```c++
int month = 9, day = 7;  // 十进制 9 7
int month = 09, day = 07;  // 八进制 前者出错 后者为7
// 改为 int month=011, day=07;
```

### 2.07
> 下述字面值表示何种含义？它们各自的数据类型是什么？
```c++
// "Who goes with F\145rgus?\012"
Who goes with Fergus? const char *
// 3.14e1L
31.4 long double
// 1024f
1024 float
// 3.14L 
long double
```

### 2.08
> 请利用转义序列编写一段程序，要求先输出 2M，然后转到新一行。修改程序使其先输出 2，然后输出制表符，再输出 M，最后转到新一行。
```c++
std::cout<<"2M\n"; 
std::cout<<"2\tM\n";
```

### 2.09
> 解释下列定义的含义，对于非法的定义，请说明错在何处并将其改正。

(a) std::cin >> int input_value;
(b) int i = { 3.14 };
(c) double salary = wage = 9999.99;
(d) int i = 3.14;
```c++
int input_value; std::cin>>input_value;
double i={3.14};
double salary,wage; salary=wage=9999.99;
double i=3.14;
```

### 2.10
> 下列变量的初值分别是什么？
```c++
std::string global_str;  // 空串
int global_int;  // 0
int main()
{
    int local_int;  // 未定义
    std::string local_str;  // 空串
}
```

### 2.11
> 指出下面的语句是声明还是定义：
```c++
extern int ix = 1024; // 定义
int iy;  // 定义
extern int iz; // 声明
```

### 2.12
> 请指出下面的名字中哪些是非法的？
```c++
int double = 3.14;  // 非法
int _;  // 函数体外非法
int catch-22;   // 非法
int 1_or_2 = 1; // 合法
double Double = 3.14; // 合法
```

### 2.13
> 下面程序中j的值是多少？
```c++
int i = 42;
int main()
{
    int i = 100;
    int j = i;  // 100
}
```

### 2.14
> 下面的程序合法吗？如果合法，它将输出什么？
```c++
int i = 100, sum = 0;
for (int i = 0; i != 10; ++i)
    sum += i;
std::cout << i << " " << sum << std::endl;  // 合法 输出 : 100 55
```

### 2.15
> 下面的哪个定义是不合法的？为什么？
```c++
int ival = 1.01;  
int &rval1 = 1.01;  // 不合法, 不能绑定到字面值上
int &rval2 = ival;
int &rval3;  // 不合法, 没有初始化
```

### 2.16
> 考察下面的所有赋值然后回答：哪些赋值是不合法的？为什么？哪些赋值是合法的？它们执行了哪些操作？
```c++
int i = 0, &r1 = i;
double d = 0, &r2 = d;
/* ---------------------------------*/
r2 = 3.14159;  // 合法 d=3.14159
r2 = r1;  // 合法 d=0 执行了int=>double转化
i = r2;  // 合法 double=>int
r1 = d;  // 合法 double=>int
```

### 2.17
> 执行下面的代码段将输出什么结果？
```c++
int i, &ri = i;
i = 5; ri = 10;
std::cout << i << " " << ri << std::endl;  // 10 10
```

### 2.18
> 编写代码分别改变指针的值以及指针所指对象的值。
```c++
#include <iostream>
int a[10]={};
int main(){
	int *p=a;
	std::cout<<p<<" "<<*p<<std::endl;
	*(p+1)=2;
	std::cout<<p+1<<" "<<*(p+1)<<std::endl;
	return 0;
}
//0x4041a0 0
//0x4041a4 2
```

### 2.19*
> 说明指针与引用主要区别
	
1. 指针是对象, 引用是别名:
2. 指针可以无需初始化, 可以多次赋值 而 引用必须初始化绑定
3. 指针通过\*来访问对象, 引用本身即对象

### 2.20
> 请叙述下面这段代码的作用。
```c++
int i = 42;
int *p1 = &i; 
*p1 = *p1 * *p1; // i=42*42
```

### 2.21
> 请解释下述定义。在这些定义中有非法的吗？如果有，为什么？
```c++
int i = 0;
double* dp = &i;  // 非法, 无法将 int * 转化为 double *
int *ip = i;  // 非法, 无法将 int 转化为 int *
int *p = &i;  // 合法
```

### 2.22
> 假设 p 是一个 int 型指针，请说明下述代码的含义。
```c++
if (p) // 如果p不是一个空指针则执行
if (*p) // 如果p指向的int数非零则执行
```

### 2.23*
> 给定指针 p，你能知道它是否指向了一个合法的对象吗？如果能，叙述判断的思路；如果不能，也请说明原因。

1. raw pointer不行, 要是能轻易做到的话C语言就不容易出内存方面的bug
2. smart pointer可以, shared_ptr和weak_ptr就可以分别用  shared_ptr::operator bool() 和 weak_ptr::expired()判断

### 2.24
> 在下面这段代码中为什么 p 合法而 lp 非法？
```c++
int i = 42;
void *p = &i;  // 任何类型指针可以转换为void *
long *lp = &i;  //int * 无法转换为 long *
```

### 2.25
> 说明下列变量的类型和值。
```c++
int* ip, i, &r = i; // ip:int* 	| i:int 	| r:i的引用
int i, *ip = 0;		// i:int  	| ip:int*
int* ip, ip2;		// ip:int* 	| ip2:int
```
