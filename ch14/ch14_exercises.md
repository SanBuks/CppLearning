## 第十四章 习题
### 14.01
> 在什么情况下重载的运算符与内置运算符有所区别？在什么情况下重载的运算符又与内置运算符一样？

不同 :
	- 可以显示调用	
	- 重载运算符的短路求值规则无法保留
	- 重载运算符可能是非成员或成员函数
相同 : 
	- 原优先级用法 
	- 原返回值类型 
	- 操作含义

### 14.02
> 为 Sales_data 编写重载的输入、输出、加法和复合赋值运算符。

参考14.06 14.09 14.20 

### 14.03
> string 和 vector 都定义了重载的\==以比较各自的对象，假设 svec1 和 svec2 是存放 string 的 vector，确定在下面的表达式中分别使用了哪个版本的\==？
```c++
"cobble" == "stone" 	// 非成员函数版本
svec1[0] == svec2[0]  	// string
svec1 == svec2  		// vector
svec1[0] == "stone"		// string
```

### 14.04
> 如何确定下列运算符是否应该是类的成员？
```c++
%		 // 算术, 非成员函数
%=	     // 内置成员函数
++ 		 // 内置成员函数
->		 // 内置成员函数
<<		 // 输出或位运算都为非成员函数
&&		 // 存在对称性, 非成员函数
==		 // 存在对称性, 非成员函数
()		 // 内置成员函数
```

### 14.06
> 为你的 Sales_data 类定义输出运算符。
```c++
std::ostream &operator<<(std::ostream &os, const Sales_data &item){
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
```

### 14.09
> 为你的 Sales_data 类定义输入运算符。
```c++
std::istream &operator>>(std::istream &is, Sales_data &item){
	is>>item.bookNo>>item.units_sold>>item.revenue;
	if(!is) item=Sales_data();
	return is;
}
```

### 14.10
> 对于 Sales_data 的输入运算符来说如果给定了下面的输入将发生什么情况？

(a) 0-201-99999-9 10 24.95  格式正确
(b) 10 24.95 0-210-99999-9  读入double时格式错误, 输入对象被重置为默认构造


### 14.11*
> 下面的 Sales_data 输入运算符存在错误吗？如果有，请指出来。对于这个输入运算符如果仍然给定上个练习的输入将会发生什么情况？
```c++
istream& operator>>(istream& in, Sales_data& s)
{
	double price;
	in >> s.bookNo >> s.units_sold >> price;
	s.revence = s.units_sold * price;
	return in;  // 未检测输入流是否发生错误, 发生错误后没有对s进行恢复
}
```

### 14.20*
> 为你的 Sales_data 类定义加法和复合赋值运算符。
```c++
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs){
	Sales_data sum=lhs;  // 定义一次临时变量
	sum+=rhs;
	return sum;   		 // 拷贝一次到调用点
}
Sales_data& Sales_data::operator+=(const Sales_data &rhs){
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
						// 没有拷贝也没有定义
}
```

### 14.21*
> 编写 Sales_data 类的+ 和+= 运算符，使得 + 执行实际的加法操作而 += 调用+。相比14.3节和14.4节对这两个运算符的定义，本题的定义有何缺点？试讨论之。
```c++
Sales_data operator+(const Sales_data & lhs, const Sales_data &rhs){
	Sales_data sum;		// 定义一次临时变量
	sum.bookNo=lhs.bookNo;
	sum.units_sold=lhs.units_sold+rhs.units_sold;
	sum.revenue=lhs.revenue+rhs.revenue;
	return sum; 		// 拷贝一次到调用点
}
Sales_data& Sales_data::operator+=(const Sales_data &rhs){
	*this=*this+rhs; 	// 调用 + 等价定义一次 拷贝一次 
	return *this;
}
// 缺点: 
// 1. 符合赋值多执行一次定义和拷贝
// 2. 临时变量还要考虑其他数据成员的一致型
```

### 14.22
> 定义赋值运算符的一个新版本，使得我们能把一个表示 ISBN 的 string 赋给一个 Sales_data 对象。
```c++
Sales_data& Sales_data::operator=(const std::string &s){
	bookNo=s;
	units_sold=0;
	revenue=0.0;
	return *this;
}
```

### 14.23
> 为你的StrVec 类定义一个 initializer_list 赋值运算符。
```c++
StrVec &StrVec::operator=(std::initializer_list<std::string> il){
	auto newdata=alloc_n_copy(il.begin(), il.end());
	free();
	elements=newdata.first;
	first_free=cap=newdata.second;
	return *this;
}
```

### 14.27
> 为你的 StrBlobPtr 类添加递增和递减运算符。
```c++
StrBlobPtr & StrBlobPtr::operator++(){
	curr++; // 存在尾后迭代器, 特殊处理
	auto ret=wptr.lock();
	if(!ret) throw std::runtime_error("unbound StrBlobPtr");
	if(curr>ret->size()) throw std::out_of_range("increment pase end of StrBlobPtr");
	return *this;
}
StrBlobPtr StrBlobPtr::operator++(int){
	auto ret=*this;
	++*this;
	return ret;
}

StrBlobPtr& StrBlobPtr::operator--(){
	curr--;
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}
StrBlobPtr StrBlobPtr::operator--(int){
	auto ret=*this;
	--*this;
	return ret;
}
```

### 14.28
> 为你的 StrBlobPtr 类添加加法和减法运算符，使其可以实现指针的算术运算。
```c++
StrBlobPtr StrBlobPtr::operator+(const int &n){
	check(curr+n, n+" increment past end of StrBlobPtr");
	auto ret=*this;
	ret.curr+=n;
	return ret;
}
StrBlobPtr StrBlobPtr::operator-(const int &n){
	check(curr+n, n+" decrement past end of StrBlobPtr");
	auto ret=*this;
	ret.curr-=n;
	return ret;
}
```

### 14.29
> 为什么不定义const 版本的递增和递减运算符？

递增与递减会改变自身内容

### 14.31
> 我们的 StrBlobPtr 类没有定义拷贝构造函数、赋值运算符以及析构函数，为什么？

std::weak_ptr<std::vector<std::string>> wptr;
std::size_t curr;
数据类型决定合成的拷贝构造, 赋值运算符和析构可以正常使用


### 14.32
> 定义一个类令其含有指向 StrBlobPtr 对象的指针，为这个类定义重载的箭头运算符。
```c++
#include <memory>
#include "StrBlob.h"
class SBPP{
private:
	std::shared_ptr<StrBlobPtr> sbpp;
public:
	SBPP()=default;
	SBPP(const StrBlobPtr &sbp):sbpp(std::make_shared<StrBlobPtr>(sbp)){}

	StrBlobPtr &operator*(){
		return *sbpp;
	}

	StrBlobPtr *operator->(){
		return & this->operator*();
	}
};

void SBPP_test(){
	StrBlob str={"123", "234", "345"};
	auto it=str.begin();
	SBPP sbpp(it+1);
	std::cout<<**sbpp<<std::endl;
	std::cout<<sbpp->getcurr()<<std::endl;
}
```

### 14.33
> 一个重载的函数调用运算符应该接受几个运算对象？

等于调用运算符的参数

### 14.34
> 定义一个函数对象类，令其执行if-then-else 的操作：该类的调用运算符接受三个形参，它首先检查第一个形参，如果成功返回第二个形参值；如果不成功返回第三个形参的值。
```c++
class IthenE{
public:
	int operator()(const int &e1, const int &e2, const int &e3){
		return e1 ? e2 : e3;
	}
};
```

### 14.35
> 编写一个类似于 PrintString 的类，令其从 istream 中读取一行输入，然后返回一个表示我们所读内容的string。如果读取失败，返回空string。
```c++
class PrintString{
public:
	PrintString(std::istream &ist):is(ist){}
	std::string operator()(){
		std::string curr;
		if(getline(is,curr)) return curr;
		return curr="";
	}
private:
	std::istream &is;
};
int main(){
	PrintString ps(std::cin);
	std::cout<<ps();
	return 0;
}
```

### 14.36
> 使用前一个练习定义的类读取标准输入，将每一行保存为 vector 的一个元素。 
```c++
int main(){
	std::vector<std::string> vec;
	PrintString ps(std::cin);
	std::string str;
	while((str=ps())!="")
		vec.push_back(str);
	for(const auto &it:vec)
		std::cout<<it<<std::endl;
	return 0;
}
```

### 14.37
> 编写一个类令其检查两个值是否相等。使用该对象及标准库算法编写程序，令其替换某个序列中具有给定值的所有实例。
```c++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class E{
private: 
	std::string str;
public:
	E(const std::string a=""):str(a){} 
	bool operator()(const std::string &s)const{
		return s==str;
	}
};

int main(){
	std::string curr, str1, str2;
	std::cin>>str1>>str2;  // str1 要替换的值  str2 替换成的值
	E e(str1);

	std::vector<std::string> vec;
	while(std::cin>>curr)
		vec.push_back(curr);
	for(const auto &it:vec)
		std::cout<<it<<" ";
	std::cout<<std::endl;

	std::replace_if(vec.begin(), vec.end(), e, str2);

	for(const auto &it:vec)
		std::cout<<it<<" ";
	std::cout<<std::endl;

	return 0;
}
// 14_37_data
```

### 14.38
> 编写一个类令其检查某个给定的 string 对象的长度是否与一个阈值相等。使用该对象编写程序，统计并报告在输入的文件中长度为1的单词有多少个，长度为2的单词有多少个、......、长度为10的单词有多少个。
```c++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
class IsE{
private:
	size_t n=0;
public:
	IsE(const size_t &nn):n(nn){}
	bool operator()(const std::string &str){
		return str.size()==n;
	}
	IsE &operator++(){ n++; return *this; }
	const size_t &get_n()const{ return n; }
};

int main(){
	std::string curr;
	std::vector<std::string> vec;
	while(std::cin>>curr)
		vec.push_back(curr);

	size_t min=0xffffffffffffffff, max=0;
	std::for_each(vec.begin(), vec.end(), 
			[&min, &max](const std::string &str)->void { 
				if(str.size()>=max) max=str.size(); 
				if(str.size()<=min) min=str.size();
			});

	IsE ise(min);
	while(ise.get_n()<=max){
		std::cout<<"word size : "<<ise.get_n()
			     <<" count : "<<std::count_if(vec.begin(), vec.end(), ise)
				 <<std::endl;
		++ise;
	}
	return 0;
}
// 14_38_data
```

### 14.39
> 修改上一题的程序令其报告长度在1到9之间的单词有多少个、长度在10以上的单词有多少个。
```c++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
class IsE{
private:
	size_t min;
	size_t max;
public:
	IsE(const size_t &mi=0, const size_t &ma=0):min(mi), max(ma){}

	bool operator()(const std::string &str){
		return str.size()<=max&&str.size()>=min;
	}

	void setRange(const size_t &mi=0, const size_t &ma=0){ min=mi; max=ma; }
};

int main(){
	std::string curr;
	std::vector<std::string> vec;
	while(std::cin>>curr)
		vec.push_back(curr);
	IsE ise(0,9);
	std::cout<<" size : 00-09  count : "<<std::count_if(vec.begin(), vec.end(), ise)<<std::endl;
	ise.setRange(10, 0xffffffffffffffff);
	std::cout<<" size : 10-max count : "<<std::count_if(vec.begin(), vec.end(), ise)<<std::endl;
	return 0;
}
```

### 14.41
> 你认为 C++ 11 标准为什么要增加 lambda？对于你自己来说，什么情况下会使用 lambda，什么情况下会使用类？

lambda 生成临时的无名类的无名对象, 方便调用, 适合只一次性用到, 处理流程简单的情形

### 14.42*
> 使用标准库函数对象及适配器定义一条表达式，令其

(a) 统计大于1024的值有多少个。 
(b) 找到第一个不等于pooh的字符串。
(c) 将所有的值乘以2。
```c++
std::cout<<std::count_if(vec.begin(), vec.end(), 
	std::bind(std::greater<int>(), _1, 1024));
std::cout<<*std::find_if(vec.begin(), vec.end(),
	std::bind(std::not_equal_to<std::string>(), _1, "pooh"));
std::transform(vec.begin(), vec.end(), 
	vec.begin(), std::bind(std::multiplies<int>(), _1, 2));
```

### 14.43*
> 使用标准库函数对象判断一个给定的int值是否能被 int 容器中的所有元素整除。
```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std::placeholders;
int main(){
	std::vector<int> vec{2,2,6,4,6,6,8,8,10};
	if(vec.end()==std::find_if(vec.begin(), vec.end(), 
						std::bind(std::modulus<int>(), _1, 2)))
		std::cout<<" Yes ";
	else std::cout<<" No ";
	return 0;
}
```

### 14.44*
> 编写一个简单的桌面计算器使其能处理二元运算。
```c++
#include <iostream>
#include <functional>
#include <stdexcept>
#include <map>

int add(const int &a1, const int &a2){ return a1+a2; } 
auto minus=[] (const int &a1, const int &a2)->int { return a1-a2; };

std::multiplies<int> mult; // 类型不能是const int &

class Divide{
public:
	int operator()(const int &a1, const int &a2){
		if(!a2) throw std::runtime_error("class Divide operator() can't divide 0"); 
		return a1/a2; 
	}
};

int main(){
	std::map< std::string, std::function<int(const int &, const int &)> > mp;

	mp.insert( {"+", add} );
	mp.insert( {"-", minus} );
	mp.insert( {"*", mult} );
	mp.insert( {"/", Divide()} );
	
	std::cout<<mp["+"](1,5)<<std::endl;
	std::cout<<mp["-"](1,5)<<std::endl;
	std::cout<<mp["*"](1,5)<<std::endl;
	std::cout<<mp["/"](1,9)<<std::endl;

	return 0;
}
```

### 14.45
> 编写类型转换运算符将一个 Sales_data 对象分别转换成 string 和 double，你认为这些运算符的返回值应该是什么？

### 14.46
> 你认为应该为 Sales_data 类定义上面两种类型转换运算符吗？应该把它们声明成 explicit 的吗？为什么？
```c++
	explicit operator std::string() const { return bookNo; }  
	// 返回 书id, 为了让使用者不发生意外隐式转换声明为explicit
	explicit operator double() const { return revenue; }  
	// 返回值是什么存在歧义, 应该不定义该类型转换
```

### 14.47*
> 说明下面这两个类型转换运算符的区别。
```c++
struct Integral {
	int a=10;
	operator const int(){ std::cout<<"#1 "<<std::endl; return a; }
	operator int() const { std::cout<<"#2 "<<std::endl; return a; }
};
int main(){
	const Integral ci;
	std::cout<<ci<<std::endl; // #2
	Integral i;
	std::cout<<i<<std::endl;  // #1
	return 0;
}
```

- 在需要内置类型时会隐式调用转换运算符, 表面上 #1 #2都没有型参但是根据 this 是否是const会发生参数匹配的优先级比较

### 14.50*
> 在初始化 ex1 和 ex2 的过程中，可能用到哪些类类型的转换序列呢？说明初始化是否正确并解释原因。
```c++
struct LongDouble {
	LongDouble(double = 0.0);
	operator double();
	operator float();
};
LongDouble ldObj;
int ex1 = ldObj;  // 发生歧义 double 和 float 转换为 int 优先级相同
float ex2 = ldObj;  // 调用 float() 进行转换
```

### 14.51*
> 在调用 calc 的过程中，可能用到哪些类型转换序列呢？说明最佳可行函数是如何被选出来的。
```c++
void calc(int);		   // #4
void calc(LongDouble); // #5
double dval;
calc(dval);  // 调用了哪个calc？ 调用 clac(int)
```

最佳可行函数匹配规则如下 :

1. 精确匹配 : 
	1. 类型相同
    2. 数组名函数名转换成对应指针
    3. `const int -> int` 或 `int -> const int`
2. `type [&/*] -> const type [&/*]` (因此存在底层const不同的调用区别)
3. 算数类型提升(函数在匹配前,没有精确匹配的实参会进行类型提升)
4. 算术类型转换(所有的算数类型转换都一样) 或 指针转换 : 
    1. `0/nullptr -> type*;`
    2. `type *(非常量指针) -> void *;`
    3. `type * -> const void *`
5. 类类型转换

### 14.52*
> 在下面的加法表达式中分别选用了哪个operator+？列出候选函数、可行函数及为每个可行函数的实参执行的类型转换：
```c++
// 公共的候选函数有四类如下所示 : 
#include <iostream>
struct SmallInt{
	friend SmallInt operator+(const SmallInt&, const SmallInt&);
	SmallInt(int i=0):val(i){}
	operator int() const { return val; }
	size_t getval() const { return val; }
private:
    std::size_t val;
};
SmallInt operator+(const SmallInt& lhs, const SmallInt& rhs){ // #1
	int a=lhs.val+static_cast<int>(rhs.getval());
	return SmallInt(a);
}

struct LongDouble {
	//用于演示的成员operator+;在通常情况下是个非成员
	LongDouble operator+(const SmallInt &rhs){  // #2
		double a=val+static_cast<double>(rhs.getval());
		return LongDouble(a);	
	}
	LongDouble(double d=0.0):val(d){}
	operator double(){ return val; }
	operator float(){ return static_cast<float>(val); }
	double val;
};

LongDouble operator+(LongDouble &lhs, double rhs){ // #3
	double a=lhs.val+rhs;
	return LongDouble(a);	
}
// 内置算术类型 '+' 法 #4
int main(){
	SmallInt si; 
	LongDouble ld;
	//ld = si + ld;  // 产生歧义
    // #1 ld无法转换为SmallInt
    // #2 si不是SmallInt
    // #3 si无法转换成LongDouble
    // #4 可行 si->int ld->float/double 产生歧义
	ld = ld + si;
    // #1 ld无法转换为SmallInt
    // #2 成员函数精确匹配
    // #3 可行, si->int->double
    // #4 可行, si->int ld->float/double 产生歧义
	return 0;
}
```

### 14.53*
> 假设我们已经定义了如第522页所示的SmallInt，判断下面的加法表达式是否合法。如果合法，使用了哪个加法运算符？如果不合法，应该怎样修改代码才能使其合法？
```c++
SmallInt si;
double d = si + 3.14;  // 产生歧义
// #1 3.14->int->SmallInt
// #4 si->int->double 
/*---------------------修改后---------------------*/
double d = static_cast<int>(si) + 3.14;
double d = si+static_cast<SmallInt>(3.14);
```