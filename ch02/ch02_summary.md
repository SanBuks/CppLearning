# 第二章 变量和基本类型

### 1. 基本数据类型
#### 类型和大小
- 总体分为算术类型 (整型, 浮点型, 字符, 布尔) 和 void 类型, 其中详细信息如下所示 :
	
|类型|最小字节数/有效位数|实际大小(64位 g++ 8.30)|字面值常量前后缀(^开头 $结尾)|
| --- | --- | --- | --- |
|bool|未定义|1|-|
|char|1|1|^u8|
|wchar\_t|2|4|^L|
|char16\_t|2|2|^u|
|char32\_t|4|4|^U|
|short|2|2|-|
|int|2|4|-|
|long|4|8|L$|
|long long|8|8|LL$|
|float|6(7)位有效|4|-|
|double|10(16)位有效| 8 |F$|
|long double|10位有效|16|L$|

- 定义一些确定长度的类型保证移植性如int64\_t等, 可用U最为后缀指定无符号类型


#### 类型转换
- 布尔类型和非布尔类型转换 以0/1为基准
- 浮点与整数转换 精度会有损失
- 赋予无符号类型超出范围数值 按模运算处理
- 赋予带符号类型超出范围数值 未定义(一般位级不变)
- 同类型无符号数与有符号数相运算 优先转成无符号数

#### 字面值常量及其类型转换
- 字面值常量指的是 如42, nullptr, true, false 一望便知值大小的常量, 类型可由前后缀指定
- 整型的八, 十六进制以 0 和 0x 开头 按 int(unsigned), long(unsigned), long long(unsigned) 最小范围转换
- 整型十进制类型 按 int, long, long long 最小范围转换
- 浮点数 可以用 e 或 E 标识 如 3.15159E10 默认为double类型
- 两个字符串紧邻由空白符分隔可以当成一个, 如 "123""321" 等价于 "123321"

#### 转义字符
- 转移字符表示不可打印或者特殊含义的字面值
- 回车 : \r （Carriage Return)  换行 : \n （Linefeed）\\\\ :  ' \ '
- \x1324 十六进制数 代表字符集中的字符 后跟多个数字 
- \123 八进制数 代表字符集中的字符 后跟至多3个数字 

### 2. 变量
#### 变量或对象
- int a; 定义对象,开辟一块能存储数据并具有某种类型的内存空间
- int a=3; 初始化对象,开辟的同时赋予一个初始值
- a=4; 赋值, 擦除当前值替换为新值

#### 初始化
- int a{3.14}; 列表初始化会报错
- int a(3.14); 括号初始化不会报错
- int a; 默认初始化 
> 内置类型静态内存中默认初始化为0, 函数体内则未定义, 其他类型取决于默认构造函数

#### 声明与定义
- C++ 支持分离式编译, 用到其他文件中的变量可以声明再使用, 声明有多个, 定义只有一次
- extern double pi; 声明变量, 规定类型和名字, 让程序所知, 并不申请空间
- extern double pi=3.14; 定义变量 等价为 double pi=3.14;
- 函数体内使用`extern int a=3;` 报错

#### 标识符
- 由字母, 数字和下划线组成, 以字母或下划线开头
- 无长度限制, 大小写敏感, 存在保留关键字
- 函数体内不能以 \_\_ 或\_[A-Z] 开头, 函数体外标识符不能以 \_ 开头

### 3. 复合类型
> 复合类型 = 基本数据类型 + 声明符列表 ( 声明符列表含有修饰符和标识符 )

#### 左值引用 &
- `int &lref=var;`
- 引用即别名非对象, 引用本身无引用, 引用必须初始化
- 引用绑定在同一类型对象上, 不能是字面值或某表达式结果 列外如下 :
	- const int &a=3;
	- 基类引用绑定到派生类上

#### 指针 \*
- 指针是对象, 允许指针拷贝和赋值, 无需定义时赋值, 赋值时类型与所指类型必须一致(除非`void *`)
```c++
int *ip=&var; 		// 将var地址赋予指针ip
void *p=anyptr; 	// void指针可被赋予任何类型的指针值
void *q=&anyobj;	// 1. void指针可被存放任意对象地址
void *func(void *pp, void qq){ 		// 2. 作为函数输入输出
	pp<qq ? return pp : return qq;  // 3. 比较
}
// 4. 但不可访问内存 除非reinterpret_cast<int *>(pp)
```

- 指针的值有 : 
	- &var 
	- (&array)+1 , 
	- nullptr/0/NULL 
	- 无效 
> NULL定义在cstdlib 为宏, 值为0, 尽量用nullptr

#### 理解符合类型声明
```c++
int *p1, *p2;  	// p1 p2 均为指针类型
int *pp1, pp2;  // pp1 为指针类型 pp2 为int 类型
// 区别在于类型修饰符*只作用局部变量, 且基础数据类型仍是int
int **ppp1;  	// 表示指向int指针的指针,且可以扩展
int *&p1=ptr; 	// 表示ptr指针的引用,且指针指向一个整型数 
```
> 从右往左读, 第一个修饰符产生本质影响

### 4. const限定符
#### const 限定类型
- 限定基本数据类型, 作用于定义的所有对象(与局部修饰符不同之处)
- const 对象不能改变所以必须初始化, 如`const int a=10; a=11;` 错误 
- cosnt 对象在编译过程中会被替换成对应值, 只在文件内有效
```c++
//a.cpp
#include<iostream>
const int a=3;
int main(){
 std::cout<<a;
 return 0;
}
//b.cpp
const int a=2;
// g++ a.cpp b.cpp -o test 运行后结果为3

//a.cpp
#include<iostream>
int a=3;
int main(){
 std::cout<<a;
 return 0;
}
//b.cpp
int a=2;
// g++ a.cpp b.cpp -o test  链接出现错误 multiple definition of `a'
// 把 b.cpp 改为const int a=2; 运行后结果为3

//最终验证其他文件内的同名const对象为独立对象,只在文件内有效,非const对象在多处定义会出现链接错误(需要extern)
```
- extern const 在某个文件内定义一次,在其他文件类可以多次声明来使用同一个对象
```c++
//a.cpp
#include<iostream>
extern const int a; //声名在其他文件中定义的a 或者 #include"b.h"也可
int main(){
 std::cout<<a;
 return 0;
}
//b.h
extern const int a;  // 在头文件中只声明a
//b.cpp
#include"b.h"
extern const int a=2; // 定义a 其中extern可以省略
// g++ a.cpp b.cpp -o test 运行后结果为2
// 最终达成了在一个文件中使用在其他文件中定义好的const对象
```

#### 对常量的引用
- 对常量的引用表示不能改变所引用对象的值, 而引用对象不必为常量
- const int &r1=var; 其中var可以是 可转换为int的 表达式结果, 非常量对象, 字面值
- 对常量的引用与赋值对象类型不一样时, 上述操作编译时等价为
```c++
const int temp=var; // var可能是字面值所以必须是一个无名临时常量
const int &r1=temp; // 通过对常量引用将临时量保存下来
```

- 假设变为 `const int temp=var; int &r1=temp;` 非法,因为从引用角度说, r1可以改变temp值而所转化的对象是一个常量, 产生矛盾
```c++
    int a=0; const int &b=a; // &a: 0x60fe80 &b: 0x60fe80
	const int a=10; // &a: 0x7ffd6662670c  将字面值转换为const int类型
    double a=2.3; const int &b=a; // &a: 0x60fe84 &b: 0x60fe78 类型转化中产生了新临时量, 地址不同
```

#### 指针与const
- 指向常量的指针不能通过指针改变所指对象的值`const int *ptr=&const_var; *ptr=10; // 错误`
- 指向常量的指针可以指向不是常量的同类对象
- 常量指针 `int *const ptr=&var; *ptr=10; // 正确`  指针是一个const对象,必须初始化且无法改变内容,且必须类型一致,但所指内容可以更改
- 顶层const : 指针(和其他任意对象)本身为常量 
- 底层const: 指针(引用)所指对象为常量
- 顶层const 被拷贝时无影响, 底层const 被拷贝时需要所赋值的对象所指为常量(底层const相同) 
```c++
int main(){
  int var=0;  //普通变量
  const int const_var=0;  //顶层const 作为常量必须初始化
  const int &ref_to_const=var;    //底层const 作为引用必须绑定
  const int *ptr_to_const;    //底层const指针 可以不初始化
  int *const const_ptr=&var;  //顶层const指针 作为常量必须初始化
  const int *const const_ptr_to_const=&var;   //顶层+底层const 作为常量必须初始化
  const int *p,*a; //类型限定符与一般修饰符不同 const限定了基础类型
  return 0;
}
```

#### 常量表达式
- 常量表达式 : 编译过程中可以得到计算结果的表达式, 一般由初始值和数据类型决定(const对象也是常量表达式), 解决难分辨初识值是否为常量的问题
- 字面值类型 : 可以被constexpr限定的类型 如算术类型, 引用, 指针, 自定义的字面值常量类和枚举类型
- 对于算术类型来说, `constexpr int a=b;` a是顶层const, b是常量表达式 
- 对于引用来说 `constexpr int &a=b;` a不是底层const, b是一个静态内存中定义的对象
- 对于指针来说 `constexpr int *a=&b;` a是顶层const, b是一个静态内存中定义的对象或&b=nullptr
- 对于指针来说 `constexpr const int *a=&b;` a是双层const 其中b是一个在静态内存中定义的对象或&b=nullptr

#### 关于c++内存区分类
- 栈区 : 编译器由高到底分配, 由低到高释放, 存放函数的参数值,局部变量的值等
- 共享库 : 动态链接的内存映射区
- 堆区 : 手动由低到高分配, 由高到底释放, 程序结束时由OS回收
- 全局区(静态区) : 全局变量和静态变量的存储是放在一块, 未初始化存放在BSS段, 初始化存放在DATA段
- 文字常量区 : 常量字符串存放区,程序结束后由系统释放
- 程序代码区 : 存放函数体的二进制代码
```c++
int a = 0;          // 全局区 已初始化
char *p1;           // 全局区 未初始化
main(){
 int b;            // 栈区
 char s[] = "abc"; // 栈区
 char *p2;         // 栈区
 char *p3 = "123456";     // "123456"在常量区, p3在栈区
 static int c =0;         // 全局区(静态) 已初始化

 p1 = (char *)malloc(10); // 堆区
 p2 = (char *)malloc(20);

 strcpy(p1, "123456");    // "123456\0" 放在常量区,编译器可将它与p3所指向的"123456"优化成一个地方。
} 
```

- 全局变量, 静态存储方式, 作用域是整个源程序
- 静态全局变量, 静态存储方式, 作用域是该源文件内有效, 对其他源文件隐藏
- 静态局部变量, 静态存储方式, 作用域是某个范围内, 但直到程序结束才销毁

#### 静态变量初始化顺序
- 静态局部变量在 调用函数或执行到该作用域第一次进行初始化
- 静态全局变量(包括类与函数静态数据成员)则根据类型和初始化值分类 :
  - 先进行静态初始化后进行动态初始化
  - 静态初始化(编译链接过程中) : 
    - 如果是内置类型 : 有初识值 (constexpr) 则const init, 没有初识值 (constexpr) 则zero init 
    - 如果是 字面值常量 类 : 对应默认构造或非默认构造
    - 如果是 非字面值常量 类 : 有自己的cto则不进行静态初始化
  - 动态初始化(运行过程中 main函数之前) : 
    - 调用该构造函数或进行初始化的函数 (非constexpr)

> 相同编译单元内, 初始化顺序参照定义顺序, 不同编译单元存在依存关系会出现问题参照Effective C++ Item04


### 5. 处理类型
#### 类型别名
```c++
typedef int T1, *T2;  //T1别名int, an2别名为int * 注意别名是一个整体
const T2 a1;  // const限定的是T2整体, a1是指向int的常量指针
const T2 *a2;  // a2是一个底层const指针, 指向 指向int的指针
using an1=int; using an2=int *; // 别名声明
```

#### auto类型说明符
- 声明 : `auto a=0, *p=&a; // 基本类型为int`  基础类型必须一致否则出错
```c++
int a=10; auto b=a; const auto c=a; // 忽略顶层const b是int型 c是const int型
int a=10, &b=a; auto c=b; 			// 以引用所指类型为准 c是int型
int a=10; const int b=10; auto c=&a; auto d=&b; // 保留底层const c是int* d是const int*
int a=10;  auto &b=a; const auto &c=100; 		// 可以通过引用修饰 b是int & c是const int &
int a=10; const auto const b=&a; 				// b是双层 
```

- 保留数组元素指针的类型 : `int c[10]; auto a=c;` a是指向int的指针 而不是指向数组的指针
- 关于多维数组指针的退化问题 : 
```c++
// 防止指针类型退化
int a1[10][2]={};    
auto a2=a1;  // int (*)[2] 类型        
auto a3=&a1; // int (*)[10][2] 类型    
    
int b1[10][10][2]={};    
auto b2=b1;  // int (*)[10][2] 类型    
auto b3=&b1; // int (*)[10][10][2]类型

// 放止退化成指针 
int c1[10][10][2][2]={};
auto &c2=c1; // int [10][10][2][2] 类型
```

#### decltype类型指示符
```c++
int a=0, &b=a; decltype(b) c=a; // 返回相同的类型 c是int&
/* 表达式或对象作为表达式返回结果是左值 则返回结果类型的引用 */
int a=0; decltype((a)) b=a; // b 是int& 对象+括号结果为左值
int a=0, *b=&a; decltype(*b) c=a // b 是int& 解引用结果为左值
int a=0,b=2; decltype(b=a) c=a; // b 是int&  赋值表达式结果为左值

int c[10]; decltype(c) a={}; // a是十个整型数的数组
```

### 6. 头文件
1. 通常将类, const, constexpr等只能被定义一次的实体放在头文件中
2. 通过头文件保护符来避免重复, 注意一定要唯一
```c++
#ifndef FILENAME_H 
#define FILENAME_H 
// .....
#endif
```

3. `#pragma once` 让编译器提供保证, 同一个文件物理上不会被包含多次

