# 6.03
> 编写你自己的fact(阶乘)函数，上机检查是否正确。
```c++
#include <cassert>
#include <stdexcept>
#include <iostream>
inline bool tmult_ok(long x, long y){
	long p = x * y;
	return !x || (p / x == y);
}

unsigned long fact(unsigned long n){
	unsigned long fact = 1;
	while(n > 0){
		if(tmult_ok(fact, n)){
			fact *= n;
			--n;
		}else
			throw std::runtime_error("fact over flow!");
	}
	return fact;
}

int main(){
	try{
		std::cout<<fact(100);
	}catch(std::exception &e){
		std::cout<<e.what();
	}
	return 0;
}
```

# 6.04\*
> 编写一个与用户交互的函数，要求用户输入一个数字，计算生成该数字的阶乘。在main函数中调用该函数。
```c++
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <climits>
#include <cstdlib>
#include <limits>

// 判断补码相乘是否溢出
inline bool tmult_ok(long x, long y){
	long p = x * y;
	return !x || (p / x == y);
}

// 阶乘
unsigned long fact(unsigned long n){
	unsigned long fact = 1;
	while(n > 0){
		if(tmult_ok(fact, n)){
			fact *= n;
			--n;
		}else
			throw std::runtime_error("fact over flow!");
	}
	return fact;
}

int main(){
	while(true){
		unsigned long n;
		std::cout << "Please enter a number!" << std::endl;
		if(std::cin >> n){ // !cin.fail()
			try{
				std::cout << "fact of " << n << " is " << fact(n) << std::endl;
			}catch(std::exception &e){
				std::cout << e.what() << std::endl;
			}
		}else{ // 流出错 bad or fail(eof)
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			// numeric_limits<> : return info of type
			// ignore : Extracts and discards characters from the input stream until and including delim. 
			// streamsize : Is a signed integral type used to represent the number of characters transferred in an I/O operation or the size of an I/O buffer.It is used as a signed counterpart of std::size_t, similar to the POSIX type ssize_t. 
			std::cout << "Input number is invalid!" << std::endl;
		}

		char c;
		while(true){
			std::cout << "Try again ? y/n\n";
			if(std::cin >> c){
				if(c == 'y')
					break;
				else if(c == 'n')
					return EXIT_SUCCESS;
				else{
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
			} else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		}

	}
	return EXIT_SUCCESS;
}
```

# 6.08
> 编写一个名为Chapter6.h 的头文件，令其包含6.1节练习中的函数声明。
```c++
inline bool tmult_ok(long x, long y){  // 内联函数定义在头文件中
	long p = x * y;
	return !x || (p / x == y);
}
long abs(long);
unsigned long fact(unsigned long);
```

# 6.09
> 编写你自己的fact.cc 和factMain.cc ，这两个文件都应该包含上一小节的练习中编写的 Chapter6.h 头文件。通过这些文件，理解你的编译器是如何支持分离式编译的。

见 fact.cpp 和 factMain.cpp

# 6.13\*
> 假设T是某种类型的名字，说明以下两个函数声明的区别： 一个是void f(T), 另一个是void f(&T)。
```c++
void f(T);  // 1. 形参是 T 类型
void f(&T); // 2. 编译错误 : expected primary-expression before T
void f(T&); // 3. 形参是 T& 类型, 函数类型与 1 不同, 匹配等级相同
```

# 6.14
> 举一个形参应该是引用类型的例子，再举一个形参不能是引用类型的例子。

swap() 应该是引用
test(short a) 不应该是引用, 原因是 sizeof(short) < sizeof(short \*)

# 6.15
> 说明find_char函数中的三个形参为什么是现在的类型，特别说明为什么s是常量引用而occurs是普通引用？ 为什么s和occurs是引用类型而c不是？ 如果令s是普通引用会发生什么情况？ 如果令occurs是常量引用会发生什么情况？
```c++
string::size_type find_char(const string &s, // string 不可更改, 引用传递快
	char c, // sizeof(char) < sizeof(char *)
	string::size_type &occurs // 额外返回值, 通过引用来返回
){...}
```

# 6.23\*
> 参考本节介绍的几个print函数，根据理解编写你自己的版本。 依次调用每个函数使其输入下面定义的 i 和 j :
```c++
int i = 0, j[2] = { 0, 1 };
void print(const int &val) { std::cout<<val<<"\n"; }
void print(const int (&val)[2]) {
	for(const auto &it : val){
		std::cout<<it<<" ";
		std::cout<<"\n";
	}
}
void print(const int *val, size_t size) {
    for (size_t i = 0; i != size; ++i) {
        std::cout << *(val + i);
    }
}
int main(int argc, char * argv[]){
	int i = 0, j[2] = { 0, 1 };
	print(i);
	print(j);
	return EXIT_SUCCESS;
}
```

# 6.36
> 编写一个函数声明，使其返回数组的引用并且该数组包含10个string对象。 不用使用尾置返回类型、decltype或者类型别名。

# 6.37\*
> 为上一题的函数再写三个声明，一个使用类型别名，另一个使用尾置返回类型，最后一个使用decltype关键字。 你觉得哪种形式最好？为什么？
```c++
using namespace std;
using array10=int [10];
int a[10]={};

int (&return_ref2array1())[10]; // 直接用类型表示
array10 &return_ref2array2(); //类型别名
auto return_ref2array3()->int (&)[10]; //置尾返回类型
decltype(a) &return_ref2array4(); //decltype
```

# 6.38\*
> 修改arrPtr函数，使其返回数组的引用。
```c++
int (&arrPtr(int (&ref)[10]))[10]{
	return ref;
}
```

# 6.48\*
> 说明下面这个循环的含义，它对assert的使用合理吗？
```c++
string s;
while(cin>>s&&s!=sought){}
//反复读入一个字符串直到读入的字符串等于sought
assert(cin);
/*
   对cin的状态进行判断 eofbit failbit badbit good
   其中默认调用operator bool来转换成bool形式,与good()有区别!
   bool()只有在 failbit badbit 都不为真的情况下返回真
   good()只有在 eofbit failbit badbit 都不为真的情况下返回真

   此处通过assert判断cin读入到状态是可以的 : 
   1.没读对string类型cin出错 failbit -> false
   2.没读对string内容,反复读str直到读到^z导致最后没有读到内容 failbit->false
   3.只有在 cin>>s; //输入 str (后接^z或者其他字符都可以) 状态goodbit和eofbit bool为真
*/
```
# 6.55
> 编写4个函数，分别对两个int值执行加、减、乘、除运算；在上一题创建的vector对象中保存指向这些函数的指针。

# 6.56\*
> 调用上述vector对象中的每个元素并输出结果。
```c++
// 注意 std::minus 会和自己定义的minus命名冲突
int add(int e1, int e2){ return e1 + e2; }
int minuss(int e1, int e2){ return e1 - e2; }
int multiply(int e1, int e2){ return e1 * e2; }
int divide(int e1, int e2){ return (e2 != 0) ? e1 / e2 : 0; }
using FuncP=int (*)(int, int);
vector<FuncP> vec;
int main(int argc, char *argv[]){
    vec.push_back(add);
    vec.push_back(minuss);
    vec.push_back(multiply);
    vec.push_back(divide);
    cout<<vec[0](1,2)<<endl; //3
    cout<<vec[1](1,1)<<endl; //0
    cout<<vec[2](2,3)<<endl; //6
    cout<<vec[3](6,3)<<endl; //2
    return 0;
}
```
