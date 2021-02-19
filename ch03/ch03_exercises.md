# 第三章 习题
### 3.01
> 使用恰当的using 声明重做 1.4.1节和2.6.2节的练习。
```c++
// 1.09
#include <iostream>
using std::cout;
int main(int argc, char * argv[]){
	int sum=0, n=50;
	while(n!=101) sum+=n++;
	cout<<sum;  // 3825
	return 0;
}
//1.10
#include <iostream>
using std::cout;
int main(int argc, char * argv[]){
	int n=10;
	while(n!=-1) std::cout<<n--<<" ";
	return 0;
}
// 其余略
```

### 3.02
> 编写一段程序从标准输入中一次读入一行，然后修改该程序使其一次读入一个词。
```c++
#include <iostream>
#include <string>
int main(){
	std::string str;
	while(getline(std::cin, str)) // while(std::cin>>str)
		std::cout<<str<<std::endl;
	return 0;
}
```

### 3.03
> 请说明string类的输入运算符和getline函数分别是如何处理空白字符的。

1. `is>>str;` 忽略空白符, 读入字符直到遇到空白符为止, 返回 is 
2. `getline(is, str)` 忽略空白符, 读入一行直到换行符为止(包含`\n`), 舍弃`\n`后赋予str, 返回 is

### 3.04
> 编写一段程序读取两个字符串，比较其是否相等并输出结果。如果不相等，输出比较大的那个字符串。改写上述程序，比较输入的两个字符串是否等长，如果不等长，输出长度较大的那个字符串。
```c++
std::string cmp(const std::string &s1, const std::string &s2){
	if(s1==s2) return s1;   // if(s1.size()==s2.size()) return s1;
	else{
		if(s1>s2) return s1; // if(s1.size()>s2.size()) return s1;
		else return s2;
	}
}
```

### 3.05
> 编写一段程序从标准输入中读入多个字符串并将他们连接起来，输出连接成的大字符串。然后修改上述程序，用空格把输入的多个字符串分割开来。
```c++
#include <iostream>
#include <string>
int main(){
	std::string str1, str2;
	while(std::cin>>str2)
		str1+=str2+" ";
	std::cout<<str1;
	return 0;
}
```

### 3.06
> 编写一段程序，使用范围for语句将字符串内所有字符用X代替。

### 3.07
> 就上一题完成的程序而言，如果将循环控制的变量设置为char将发生什么？先估计一下结果，然后实际编程进行验证。
```c++
#include <iostream>
#include <string>
int main(){
	std::string s1("12345");
	std::cout<<s1<<std::endl;
	for(auto &it : s1) // for(char &it : s1)
		it='x';
	std::cout<<s1;
	return 0;
}
```

### 3.08*
> 分别用while循环和传统for循环重写第一题的程序，你觉得哪种形式更好呢？为什么？
```c++
for(decltype(s1.size()) index=0; index<s1.size(); index++)
    s1[index]='x';

decltype(s1.size()) index=0;
while(index<s1.size()){
    s1[index]='x';
	++index;
}

// range-for 更加简洁
```

### 3.09*
> 下面的程序有何作用？它合法吗？如果不合法？为什么？
```c++
string s;
cout << s[0] << endl; // 首先需要判断是否为空, 否则访问未定义
```

### 3.10
> 编写一段程序，读入一个包含标点符号的字符串，将标点符号去除后输出字符串剩余的部分。
```c++
#include <iostream>
#include <string>
#include <cctype>

std::string remove_punct(const std::string &s){
	std::string str;
	for(const auto &it : s)
		if(!ispunct(it))
			str+=it;
	return str;
}
int main(){
	std::string s1("123.2?5/45'+-");
	std::cout<<s1<<std::endl;
	std::cout<<remove_punct(s1);
	return 0;
}
```

### 3.11*
> 下面的范围for语句合法吗？如果合法，c的类型是什么？
```c++
const string s = "Keep out!";
for(auto &c : s){ /* ... */ }
// c 为 const char & 只读操作合法, 写操作非法
```

### 3.12
> 下列vector对象的定义有不正确的吗？如果有，请指出来。对于正确的，描述其执行结果；对于不正确的，说明其错误的原因。
```c++
vector<vector<int>> ivec;         // 合法
vector<string> svec = ivec;       // 非法, 类型不同
vector<string> svec(10, "null");  // 合法
```

### 3.13*
> 下列的vector对象各包含多少个元素？这些元素的值分别是多少？
```c++
vector<int> v1;         // 0个元素 {}
vector<int> v2(10);     // 10个元素 {0,0,...,0}
vector<int> v3(10, 42); // 10个元素 {42,42,...,42}
vector<int> v4{ 10 };   // 1个元素 {10}
vector<int> v5{ 10, 42 }; // 2个元素 {10,42}
vector<string> v6{ 10 };  // 10个元素 {"", ..., ""}
vector<string> v7{ 10, "hi" };  // 10个元素 {"hi", "hi", ..., "hi"}
```

### 3.14
> 编写一段程序，用cin读入一组整数并把它们存入一个vector对象。
```c++
#include <iostream>
#include <vector>
int main(){
	int a;
	std::vector<int> v;
	while(std::cin>>a)
		v.push_back(a);
	for(const auto &it : v)
		std::cout<<it<<" ";
	return 0;
}
```

### 3.15
> 改写上题程序，不过这次读入的是字符串。
```c++
#include <iostream>
#include <string>
#include <vector>

int main(){
	std::string str;
	std::vector<std::string> v;
	while(std::cin>>str)
		v.push_back(str);
	for(const auto &it : v)
		std::cout<<it<<" ";
	return 0;
}
```

### 3.16
> 编写一段程序，把练习3.13中vector对象的容量和具体内容输出出来

参考3.13

### 3.17
> 从cin读入一组词并把它们存入一个vector对象，然后设法把所有词都改为大写形式。输出改变后的结果，每个词占一行。
```c++
#include <iostream>
#include <string>
#include <vector>

int main(){
	std::string str;
	std::vector<std::string> v;
	while(std::cin>>str)
		v.push_back(str);
	for(const auto &it : v)
		std::cout<<it<<" ";

	std::cout<<std::endl<<"--------------"<<std::endl;

	for(auto &word: v)
		for(auto &letter : word)
			letter=toupper(letter);
	for(const auto &it : v)
		std::cout<<it<<std::endl;
	return 0;
}
```

### 3.18
> 下面的程序合法吗？如果不合法，你准备如何修改？
```c++
vector<int> ivec;
ivec[0] = 42; // 非法, 改为 ivec.push_back(42);
```

### 3.19
> 如果想定义一个含有10个元素的vector对象，所有元素的值都是42，请例举三种不同的实现方法，哪种方式更好呢？
```c++
// 最好方式
vector<int> vec(10, 42);  

// 第二种方式
vector<int> vec(10);
for(auto &it : vec)
	it=42;
// 第三种方式
vector<int> vec;
for(int i=0; i!=10; ++i)
	vec.push_back(42);
```

### 3.20
> 读入一组整数并把他们存入一个vector对象，将每对相邻整数的和输出出来。改写你的程序，这次要求先输出第一个和最后一个元素的和，接着输出第二个和倒数第二个元素的和，以此类推。
```c++
#include <iostream>
#include <vector>
int main(){
	int a;
	std::vector<int> v;
	while(std::cin>>a)
		v.push_back(a);
	for(const auto &it : v)
		std::cout<<it<<" ";
	std::cout<<std::endl;
	// 邻接求值
	if(v.size()>1){ // 判断是否有邻接数
		for(decltype(v.size()) index=1; index<v.size(); ++index)
			std::cout<<v[index]+v[index-1]<<" ";
	}
	// 前后求值
	if(!v.empty()){
		if(v.size()>1) // 注意 只有一个元素用<= 会发生错误
			for(decltype(v.size()) b=0, e=v.size()-1; b<=e; ++b, --e) 
				std::cout<<v[b]+v[e]<<" ";
		else std::cout<<2*v[0];
	}
	return 0;
}
```








