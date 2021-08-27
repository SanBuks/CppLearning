# 4.01
> 表达式5 + 10 \* 20 / 2的求值结果是多少？

105

# 4.02
> 根据4.12节中的表，在下述表达式的合理位置添加括号，使得添加括号后运算对象的组合顺序与添加括号前一致。
```
*(vec.begin())        // *vec.begin()
(*(vec.begin())) + 1  // *vec.begin()+1
```

# 4.03
> C++语言没有明确规定大多数二元运算符的求值顺序，给编译器优化留下了余地。这种策略实际上是在代码生成效率和程序潜在缺陷之间进行了权衡，你认为这可以接受吗？请说出你的理由。

可以接受, 只要遵守不要在一个表达式中用上超过两次某个可能修改的对象即可避免
将复杂的表达式分解成多个语句有助于增强可读性

# 4.04
> 在下面的表达式中添加括号，说明其求值过程及最终结果。编写程序编译该（不加括号的）表达式并输出结果验证之前的推断。
```c++
auto result = 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2;
// 结果 : 16 + 75 + 0 = 91
```

# 4.05
> 写出下列表达式的求值结果。
```c++
-30 * 3 + 21 / 5  // -86
-30 + 3 * 21 / 5  // -18
30 / 3 * 21 % 5   // 0
-30 / 3 * 21 % 4  // -2
```

# 4.06
> 写出一条表达式用于确定一个整数是奇数还是偶数。
```c++
if(n%2) ... // 是奇数
else ... // 是偶数
```

# 4.10
> 为while 循环写一个条件，使其从标准输入中读取整数，遇到 42 时停止。
```c++
while(std::cin >> a && a != 42){...}
```

# 4.11
> 书写一条表达式用于测试4个值a、b、c、d的关系，确保a大于b、b大于c、c大于d。
```c++
if(a > b && b > c && c > d) ...
```

# 4.12
> 假设i、j 和k 是三个整数，说明表达式 i != j < k 的含义。

首先判断 j \< k , 再判断 i 是否与结果 ( bool ) 相等

# 4.13
> 在下述语句中，当赋值完成后 i 和 d 的值分别是多少？
```c++
int i; double d;
d = i = 3.5; // i = 3, d = 3.0
i = d = 3.5; // d = 3.5, i = 3
```

# 4.15
> 下面的赋值是非法的，为什么？应该如何修改？
```c++
double dval; int ival; int *pi;
dval = ival = pi = 0;
// pi = nullptr;
// ival = 0;
// dval = 0.0;
```

# 4.18
> 如果132页那个输出vector对象元素的while循环使用前置递增运算符，将得到什么结果？

跳过第一个对象

# 4.21
> 编写一段程序，使用条件运算符从vector中找到哪些元素的值是奇数，然后将这些奇数值翻倍。
```c++
std::vector<int> a{1,2,6,498,4,13,26,549,8};
std::for_each(a.begin(), a.end(), [](int &item){
    item % 2 ? item *= 2 : 1 ;
});
for(auto &item : a){
    std::cout<<item<<" ";
}
```

# 4.22
> 本节的示例程序将成绩划分为high pass、pass 和 fail 三种，扩展该程序使其进一步将 60 分到 75 分之间的成绩设定为low pass。要求程序包含两个版本：一个版本只使用条件运算符；另一个版本使用1个或多个if语句。哪个版本的程序更容易理解呢？为什么？
```c++
// switch 最好理解
std::string gradeDiv(unsigned score){
	if(score > 100) throw std::runtime_error("no vaild score");
	switch(score/10){
		case 0: case 1: case 2: case 3: case 4: case 5: 
			return "fail";
			break;
		case 6: case 7:
			if(score < 76)
				return "low pass";
			else return "pass";
			break;
		case 8:
			return "pass";
			break;
		case 9: case 10:
			return "high pass";
			break;
		default:
			throw std::runtime_error("no vaild score");
	}
}
```

# 4.23
> 因为运算符的优先级问题，下面这条表达式无法通过编译。根据4.12节中的表指出它的问题在哪里？应该如何修改？
```c++
string s = "word";
string pl = s + s[s.size() - 1] == 's' ? "" : "s" ;
// "+" 优先级大于 "? :" 造成 string + char 问题出现
string p2 = s + ( s[s.size() - 1] == 's' ? "" : "s" );
```

# 4.24
> 本节的示例程序将成绩划分为high pass、pass、和fail三种，它的依据是条件运算符满足右结合律。假如条件运算符满足的是左结合律，求值的过程将是怎样的？
```c++
finalgrade = (grade > 90) ? "high pass" : (grade < 60) ? "fail" : "pass"; 
// 如果满足左结合律 以上逻辑变为如下
// grade > 90 返回 "fail"
// grade <= 90 && grade <  60 返回 "fail"
// grade <= 90 && grade >= 60 返回 "pass"
```

# 4.25
> 如果一台机器上int占32位、char占8位，用的是Latin-1字符集，其中字符'q' 的二进制形式是01110001，那么表达式~'q' << 6的值是什么？

1. 整型提升后取反 : 低16位为 1111 1110 0011 1000 0000
2. 求反 : 0x FFFFFE380 (-7296)

# 4.26
> 在本节关于测验成绩的例子中，如果使用unsigned int 作为quiz1 的类型会发生什么情况？

unsigned int 仍为 32 位(32位 和 64位机器), 没有发生任何情况

# 4.27
> 下列表达式的结果是什么？
```c++
unsigned long ul1 = 3, ul2 = 7;
(a) ul1 & ul2  // 3UL
(b) ul1 | ul2  // 7UL
(c) ul1 && ul2 // true
(d) ul1 || ul2  // true
```

# 4.28
> 编写一段程序，输出每一种内置类型所占空间的大小。
```c++
void printSize(){
	std::cout<<"char :\t\t"<<sizeof(char)<<std::endl;
	std::cout<<"char16_t :\t"<<sizeof(char16_t)<<std::endl;
	std::cout<<"char32_t :\t"<<sizeof(char32_t)<<std::endl;
	std::cout<<"wchar_t :\t"<<sizeof(wchar_t)<<std::endl;
	std::cout<<"--------------------------"<<std::endl;

	std::cout<<"bool :\t\t"<<sizeof(bool)<<std::endl;
	std::cout<<"short :\t\t"<<sizeof(short)<<std::endl;
	std::cout<<"int :\t\t"<<sizeof(int)<<std::endl;
	std::cout<<"long :\t\t"<<sizeof(long)<<std::endl;
	std::cout<<"long long :\t"<<sizeof(long long)<<std::endl;
	std::cout<<"--------------------------"<<std::endl;

	std::cout<<"float:\t\t"<<sizeof(float)<<std::endl;
	std::cout<<"double:\t\t"<<sizeof(double)<<std::endl;
	std::cout<<"--------------------------"<<std::endl;

	std::cout<<"pointer:\t"<<sizeof((int*)0)<<std::endl;	
}
/*
char :          1
char16_t :      2
char32_t :      4
wchar_t :       4
--------------------------
bool :          1
short :         2
int :           4
long :          8
long long :     8
--------------------------
float:          4
double:         8
--------------------------
pointer:        8
*/
```

# 4.29
> 推断下面代码的输出结果并说明理由。实际运行这段程序，结果和你想象的一样吗？如不一样，为什么？
```c++
int x[10];   int *p = x;
cout << sizeof(x)/sizeof(*x) << endl;  // 40/4 = 10 
cout << sizeof(p)/sizeof(*p) << endl;  // 8/4 = 2 ( 机器字长 : 8B )
```

# 4.31
> 本节的程序使用了前置版本的递增运算符和递减运算符，解释为什么要用前置版本而不用后置版本。要想使用后置版本的递增递减运算符需要做哪些改动？使用后置版本重写本节的程序。

不需要任何改动, 尽量使用前置版本, 减少拷贝副本

# 4.32
> 解释下面这个循环的含义。
```c++
constexpr int size = 5;
int ia[size] = { 1, 2, 3, 4, 5 };
for (int *ptr = ia, ix = 0;
    ix != size && ptr != ia+size;  // 遍历数组
    ++ix, ++ptr) { /* ... */ }

```

# 4.34
> 根据本节给出的变量定义，说明在下面的表达式中将发生什么样的类型转换：
```c++
(a) if (fval)  // float => bool
(b) dval = fval + ival; // int => float => double
(c) dval + ival * cval; // char => int => double
```

# 4.35
> 假设有如下的定义：请回答在下面的表达式中发生了隐式类型转换吗？如果有，指出来。
```c++
char cval;
int ival;
unsigned int ui;
float fval;
double dval;

cval = 'a' + 3;           
// 1. char => int 
// 2. int => char

fval = ui - ival * 1.0;   
// 1. int => double 
// 2. unsigned => double 
// 3. double => float

dval = ui * fval;         
// 1. unsigned => float
// 2. float => double

cval = ival + fval + dval;
// 1. int => float
// 2. float => double
// 3. double => char
```

# 4.36
> 假设 i 是int类型，d 是double类型，书写表达式 i\*=d 使其执行整数类型的乘法而非浮点类型的乘法。
```c++
i *= static_cast<int>(d);
```

# 4.38
> 说明下面这条表达式的含义。
```c++
double slope = static_cast<double>(j/i);
// j/i => double
```