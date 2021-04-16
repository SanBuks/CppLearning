# 第七章
### 6.01
> 实参和形参的区别是什么?

1. 形参是在调用函数时接受实参值的变量, 由参数列表定义, 作用域仅在函数中, 自动变量
2. 实参是形参的初始值, 在调用时能够求得确切的值, 单项拷贝传递内容给形参, 值传递实参内容不能通过函数改变 (引用传递可以)

### 6.02
> 请指出下列函数哪个有错误，为什么？应该如何修改这些错误呢？
```c++
(a) int f() {
         string s;
         // ...
         return s;  // 返回类型不匹配, string 无法隐式转换为 int
   }
(b) f2(int i) { /* ... */ }  // 没有返回类型
(c) int calc(int v1, int v1) { /* ... */ }  // 没有 返回值
(d) double square (double x)  return x * x;  // 没有 函数体
```

### 6.03
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


### 6.04\*
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

### 6.05
> 编写一个函数输出其实参的绝对值。
```c++
inline long abs(long n){
	return n < 0 ? -n : n;
}
```

### 6.06
> 说明形参、局部变量以及局部静态变量的区别。编写一个函数，同时达到这三种形式。
```c++
long abs(long n){ // n 是参数, 自动变量, 调用时创建结束时销毁
	static int callCount = 0; // callCount 是局部静态变量, 第一次调用时创建, 程序结束时销毁
	++callCount;
	long result = (n < 0) ? -n : n; // result 是 局部变量, 函数结束时销毁
	return result;
}
```

### 6.07
> 编写一个函数，当它第一次被调用时返回0，以后每次被调用返回值加1。
```c++
long callCount(){ 
	static long _callCount = -1; 
	++_callCount;
	return _callCount;
}
```

### 6.08
> 编写一个名为Chapter6.h 的头文件，令其包含6.1节练习中的函数声明。
```c++
inline bool tmult_ok(long x, long y){  // 内联函数定义在头文件中
	long p = x * y;
	return !x || (p / x == y);
}
long abs(long);
unsigned long fact(unsigned long);
```

### 6.09
> 编写你自己的fact.cc 和factMain.cc ，这两个文件都应该包含上一小节的练习中编写的 Chapter6.h 头文件。通过这些文件，理解你的编译器是如何支持分离式编译的。

见 fact.cpp 和 factMain.cpp

### 6.10
> 编写一个函数，使用指针形参交换两个整数的值。 在代码中调用该函数并输出交换后的结果，以此验证函数的正确性。
```c++
void swapByPointer(int *a, int *b){
	if(!a || !b) return;
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}
```

### 6.11
> 编写并验证你自己的reset函数，使其作用于引用类型的参数。
```c++
inline long& reset(long &val){
	val = 0;
	return val;
}
```

### 6.12
> 改写6.2.1节练习中的程序，使其引用而非指针交换两个整数的值。你觉得哪种方法更易于使用呢？为什么？
```c++
// reference 版本更容易使用
void swapByReference(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
	return;
}
```

### 6.13\*
> 假设T是某种类型的名字，说明以下两个函数声明的区别： 一个是void f(T), 另一个是void f(&T)。
```c++
void f(T);  // 1. 形参是 T 类型
void f(&T); // 2. 编译错误 : expected primary-expression before T
void f(T&); // 3. 形参是 T& 类型, 函数类型与 1 不同, 匹配等级相同
```

### 6.14
> 举一个形参应该是引用类型的例子，再举一个形参不能是引用类型的例子。

swap() 应该是引用
test(short a) 不应该是引用, 原因是 sizeof(short) < sizeof(short \*)

### 6.15
> 说明find_char函数中的三个形参为什么是现在的类型，特别说明为什么s是常量引用而occurs是普通引用？ 为什么s和occurs是引用类型而c不是？ 如果令s是普通引用会发生什么情况？ 如果令occurs是常量引用会发生什么情况？
```c++
string::size_type find_char(const string &s, // string 不可更改, 引用传递快
	char c, // sizeof(char) < sizeof(char *)
	string::size_type &occurs // 额外返回值, 通过引用来返回
){...}
```

### 6.16
> 下面的这个函数虽然合法，但是不算特别有用。指出它的局限性并设法改善。
```c++
bool is_empty(string& s) { return s.empty(); }
// 1. 内联 2. 引用传递
inline bool is_empty(const string& s) { return s.empty(); }
```

### 6.17
> 编写一个函数，判断string对象中是否含有大写字母。 编写另一个函数，把string对象全部改写成小写形式。 在这两个函数中你使用的形参类型相同吗？为什么？
```c++
std::for_each(s.begin(), s.end(), [](char &c){ // 修改操作
    if(std::islower(c)) c = std::toupper(c);
});

inline bool hasLower(const string &s){  // 查询操作
	for(const auto &c : s){
		if(islower(c))
			return true;
	}
	return false;
}
```

### 6.18
> 为下面的函数编写函数声明，从给定的名字中推测函数具备的功能。

- 名为compare的函数，返回布尔值，两个参数都是matrix类的引用。
- 名为change_val的函数，返回vector的迭代器，有两个参数：一个是int，另一个是vector的迭代器。
```c++
bool compare(const matrix &m1, const matrix &m2);
vector<int>::iterator change_val(int e, vector<int>::iterator it);
```

### 6.19
>假定有如下声明，判断哪个调用合法、哪个调用不合法。对于不合法的函数调用，说明原因。
```c++
double calc(double);
int count(const string &, char);
int sum(vector<int>::iterator, vector<int>::iterator, int);
vector<int> vec(10);

calc(23.4, 55.1); // (a) 少参数
count("abcda",'a'); // (b) 合法
calc(66);  // (c) 合法
sum(vec.begin(), vec.end(), 3.8); // (d) 合法
```

### 6.20
> 引用形参什么时候应该是常量引用？如果形参应该是常量引用，而我们将其设为了普通引用，会发生什么情况？

- 不改变形参的值且其大小大于等于指针 : 用常量引用
- 设为普通引用 : 存在调用者修改其内容的风险

### 6.21
> 编写一个函数，令其接受两个参数：一个是int型的数，另一个是int指针。 函数比较int的值和指针所指的值，返回较大的那个。 在该函数中指针的类型应该是什么？
```c++
inline int getBigger(int &a, const int *b){
	return a < *b ? *b : a;
}
```

### 6.22
> 编写一个函数，令其交换两个int指针。
```c++
void swapPointer(int **a, int **b){
	int *temp = *a;
	*a = *b;
	*b = temp;
}

int main(int argc, char * argv[]){
	int a = 0; int *pa = &a;
	int b = 1; int *pb = &b;
	swapPointer(&pa, &pb);
	std::cout<< *pa << " " << *pb;
	return EXIT_SUCCESS;
}
```

### 6.23\*
> 参考本节介绍的几个print函数，根据理解编写你自己的版本。 依次调用每个函数使其输入下面定义的 i 和 j :
```c++
int i = 0, j[2] = { 0, 1 };
void print(const int &val){ std::cout<<val<<"\n"; }
void print(const int (&val)[2]){
	for(const auto &it : val){
		std::cout<<it<<" ";
		std::cout<<"\n";
	}
}
int main(int argc, char * argv[]){
	int i = 0, j[2] = { 0, 1 };
	print(i);
	print(j);
	return EXIT_SUCCESS;
}
```

### 6.24
> 描述下面这个函数的行为。如果代码中存在问题，请指出并改正。
```c++
void print(const int ia[10]) 
// 等价 const int *a 如果传递小于10的指针会发生越界
// 可改为 void print(const int *a, int number)
{
	for (size_t i = 0; i != 10; ++i)
		cout << ia[i] << endl;
}
```

### 6.25
> 编写一个main函数，令其接受两个实参。把实参的内容连接成一个string对象并输出出来。

### 6.26
> 编写一个程序，使其接受本节所示的选项；输出传递给main函数的实参内容。
```c++
int main(int argc, char *argv[]){
	std::cout<<argv[0]<<"\n";
    if(argc>2)
       std::cout<<argv[1]<<argv[2]<<"\n";
    else std::cout<<"no enough options!"<<"\n";
    return EXIT_SUCCESS;
}
```

### 6.27
> 编写一个函数，它的参数是initializer_list类型的对象，函数的功能是计算列表中所有元素的和。
```c++
int clac_all(std::initializer_list<int> list){
   int sum=0;
   for(const auto &it:list)
       sum+=it;
   return sum;
}
```

### 6.28
> 在error\_msg函数的第二个版本中包含ErrCode类型的参数，其中循环内的elem是什么类型？

std::const string &

### 6.29
> 在范围for循环中使用initializer_list对象时，应该将循环控制变量声明成引用类型吗？为什么？

`initializer_list<T> list` 中的所有元素皆常量

### 6.30
> 编译第200页的str_subrange函数，看看你的编译器是如何处理函数中的错误的。

return-statement with no value, in function returning ‘bool’ [-fpermissive]


### 6.31
> 什么情况下返回的引用无效？什么情况下返回常量的引用无效？

返回局部非静态对象的引用无效, 作为可修改左值时返回常量的引用无效

### 6.32
> 下面的函数合法吗？如果合法，说明其功能；如果不合法，修改其中的错误并解释原因。
```c++
// 正确
int &get(int *array, int index) { return array[index]; }
int main()
{
    int ia[10];
    for (int i = 0; i != 10; ++i)
        get(ia, i) = i;
}
```

### 6.33
> 编写一个递归函数，输出vector对象的内容。
```C++
void print(std::vector<int> &vec, unsigned i){
	if(i == 0) { 
		std::cout << vec[i] << " ";
		return;
	}else{
		print(vec, i-1);
		std::cout << vec[i] << " ";
	}
}

int main(int argc, char *argv[]){
	std::vector<int> vec{1,2,3,4,5,6};
	print(vec, vec.size() - 1);
    return EXIT_SUCCESS;
}
```

### 6.34
> 如果factorial函数的停止条件如下所示，将发生什么？
```c++
if (val != 0)
// 负数会发超出预期次数的循环, 最终溢出
```


### 6.35
> 在调用factorial函数时，为什么我们传入的值是val-1而非val--？

val 的求值顺序必须先减1, 再求值, 否则会无限递归

### 6.36
> 编写一个函数声明，使其返回数组的引用并且该数组包含10个string对象。 不用使用尾置返回类型、decltype或者类型别名。

### 6.37\*
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

### 6.38\*
> 修改arrPtr函数，使其返回数组的引用。
```c++
int (&arrPtr(int (&ref)[10]))[10]{
	return ref;
}
```

### 6.39
> 说明在下面的每组声明中第二条语句是何含义。 如果有非法的声明，请指出来。 
```c++
(a) int calc(int, int); // 非法, 顶层 const 忽略, 产生二义 
	int calc(const int, const int); 
(b) int get(); // 非法, 函数匹配不考虑返回值类型
	double get();
(c) int *reset(int *); // 合法
	double *reset(double *);
```

### 6.40
> 下面的哪个声明是错误的？为什么？
```c++
int ff(int a, int b = 0, int c = 0);  // 正确
char *init(int ht = 24, int wd, char bckgrnd); // 错误, 默认实参应当靠右	
```

### 6.41
> 下面的哪个调用是非法的？为什么？哪个调用虽然合法但显然与程序员的初衷不符？为什么？
```c++
char *init(int ht, int wd = 80, char bckgrnd = ' ');
init();  // 非法, ht 没有默认实参
init(24,10); // 合法
init(14,'*'); // 初衷不符, 应该调用 init(14, 80, '*');
```

### 6.42
> 给make_plural函数的第三个形参赋予默认实参's', 利用新版本的函数输出单词success和failure的单数和复数形式。
```c++
std::string make_plural(size_t ctr, const std::string &word, const std::string &ending = "s"){
	return ctr > 1 ? word + ending : word;
}
int main(int argc, char *argv[]){
	std::string str("success");
	std::cout<<make_plural(1, str)<<"\n";
	std::cout<<make_plural(2, str)<<"\n";
    return EXIT_SUCCESS;
}
```

### 6.43
> 你会把下面的哪个声明和定义放在头文件中？哪个放在源文件中？为什么？
```c++
inline bool eq(const BigInt&, const BigInt&) {...} // 声明和定义放在头文件中
void putValues(int *arr, int size); // 声明放在头文件中, 定义放在源文件中
```

### 6.44
> 将6.2.2节的isShorter函数改写成内联函数。
```c++
inline bool isShorter(const string &s1, const string &s2){
	return s1.size() < s2.size();
}
```

### 6.45
> 回顾在前面的练习中你编写的那些函数，它们应该是内联函数吗？ 如果是，将它们改写成内联函数；如果不是，说明原因。

内联函数只适用于流程较短, 频繁调用的函数

### 6.46
> 能把isShorter函数定义成constexpr函数吗？ 如果能，将它改写成constxpre函数；如果不能，说明原因。

不可以, 返回值和参数必须是字面值类型

### 6.47
> 改写6.3.2节练习中使用递归输出vector内容的程序，使其有条件地输出与执行过程有关的信息。 例如，每次调用时输出vector对象的大小。 分别在打开和关闭调试器的情况下编译并执行这个程序。
```c++
void print(std::vector<int> &vec, unsigned i){
#ifndef NDEBUG
	std::cout<<"in function "<<__func__<<" : vec size is ";
	std::cout<<vec.size()<<" "<<i<<"\n";
#endif
	if(i == 0) { 
		std::cout << vec[i] << " ";
		return;
	}else{
		print(vec, i-1);
		std::cout << vec[i] << " ";
	}
}

int main(int argc, char *argv[]){
	std::vector<int> vec{1,2,3,4,5,6};
	print(vec, vec.size() - 1);
    return EXIT_SUCCESS;
}
```

### 6.48\*
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

### 6.49
> 什么是候选函数？什么是可行函数？

候选函数, 作用域内函数名相同的函数
可行函数, 候选函数中参数可以匹配或转换调用的函数

### 6.50
> 已知有第217页对函数f的声明，对于下面的每一个调用列出可行函数。 其中哪个函数是最佳匹配？ 如果调用不合法，是因为没有可匹配的函数还是因为调用具有二义性？

### 6.51\*
> 编写函数f的4版本，令其各输出一条可以区分的消息。 验证上一个练习的答案，如果你的回答错了，反复研究本节内容直到你弄清自己错在何处。
```c++
void f(){ std::cout<<"f()\n"; } // 1
void f(int e){ std::cout<<"f(int e)\n"; } // 2
void f(int e, int f){ std::cout<<"f(int e, int f)\n"; } // 3
void f(double e, double f=3.14){ std::cout<<"f(double e, double f)\n"; } // 4

int main(int argc, char *argv[]){
   // f(2.56, 42); // 2.56(字面值类型为double) 42(字面值类型为int) 二异
   f(42); // 调用 2
   f(42, 0); // 调用 3
   f(2.56, 3.14); // 调用4
   return 0;
}
```

### 6.52
> 已知有如下声明：
```c++
void manip(int ,int);
double dobj;
```

### 6.53
> 说明下列每组声明中的第二条语句会产生什么影响，并指出哪些不合法（如果有的话）。
```c++
int calc(int&, int&); 
int calc(const int&, const int&); // 发生重载

int calc(char*, char*);
int calc(const char*, const char*);// 发生重载

int calc(char*, char*);
int calc(char* const, char* const); // 忽略顶层const, 重复声明
```


### 6.54
> 编写函数的声明，令其接受两个int形参并返回类型也是int；然后声明一个vector对象，令其元素是指向该函数的指针。
```c++
std::vector<int (*)(int , int)>vec;
```

### 6.55
> 编写4个函数，分别对两个int值执行加、减、乘、除运算；在上一题创建的vector对象中保存指向这些函数的指针。

### 6.56\*
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
