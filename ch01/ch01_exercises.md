## 第一章 习题
### 1.01*
> 查阅你使用的编译器文档，确定它所使用的文件命名约定。编译并运行第2页的main程序

|拓展名|文件|
|---|---|
|.cpp/.cc/.C|源文件 -E 只预处理|
|.ii|预处理后的文件 -S 只编译|
|.s| 编译过得汇编代码 -c 编译并翻译成机器代码|
|.o| 机器代码 -o file 生成可执行程序<br />(完成上述任意步骤的文件) |

`g++ man.cpp -o atest -g -Wall -std=c++11`  ( g++ 8.3.0 )

### 1.02*
> 返回值-1通常被当作程序错误的标识，观察你的系统如何处理main返回的错误标识。

`$ echo $?` 打印返回值

| 返回值 | 一般意义                                              |
| ------ | ----------------------------------------------------- |
| 1      | 通常的错误                                            |
| 2      | Shell 编程错误                                        |
| 126    | 命令无法执行                                          |
| 127    | 命令不存在                                            |
| 128    | 非法返回值如浮点返回值, 返回值范围为1-255(整型mod256) |
| 128+n  | 通过信号杀死进程 kill -# (exit 128+#)                 |
| 130    | 被 ^ + C 终止                                         |
| 255    | 返回值超出范围如 exit -1;                             |

- 其他值用户可自定义
- c/c++ 程序员可通过/usr/include/sysexits.h 查看返回值意义

### 1.03
> 编写程序，在标准输出上打印Hello, World。
```c++
#include <iostream>
int main(int argc, char * argv[]){
	std::cout<<"hello world\n";
	return 0;
}
```

### 1.04
> 我们的程序使用加法运算符+来将两个数相加。编写程序使用乘法运算符*，来打印两个数的积。
```c++
#include <iostream>
int main(int argc, char * argv[]){
	std::cout<<" Please Enter two number! \n";
	int v1, v2; v1=v2=0;
	std::cin>>v1>>v2;
	std::cout<<"The product is : "<<v1*v2<<"\n";
	return 0;
}
```

### 1.05
> 我们将所有的输出操作放在一条很长的语句中，重写程序，将每个运算对象的打印操作放在一条独立的语句中。
```c++
#include <iostream>
int main(int argc, char * argv[]){
	std::cout<<" Please Enter two number! \n";
	int v1, v2; v1=v2=0;
	std::cin>>v1>>v2;
	std::cout<<"The product is : ";
	std::cout<<v1*v2;
	std::cout<<"\n";
	return 0;
}
```

### 1.06
> 解释下面程序片段是否合法。如果程序是合法的，它的输出是什么？如果程序不合法，原因何在？应该如何修正？
```c++
std::cout << "The sum of " << v1;
          << " and " << v2;
          << " is " << v1 + v2 << std::endl;
```

第二行与第三行修改为 : 
```c++
std::cout<< " and " << v2;
std::cout<< " is " << v1 + v2 << std::endl;
```

### 1.07
> 编译一个包含不正确的嵌套注释的程序，观察编译器返回的错误信息。
```c++
#include <iostream>
int main(int argc, char * argv[]){
	std::cout<<" Please Enter two number! \n";
	/*
	/**/
	*/
	return 0;
}

// test.cpp:6:3: error: expected primary-expression before ‘/’ token
//   */
//    ^
// test.cpp:7:2: error: expected primary-expression before ‘return’
// return 0;

```

### 1.08*
> 指出下列哪些输出语句是合法的（如果有的话），预测编译这些语句会产生什么样的结果，实际编译这些语句来验证你的答案(编写一个小程序，每次将上述一条语句作为其主体)，改正每个编译错误。
```c++
std::cout << "/*";
std::cout << "*/";
std::cout << /* "*/" */;
std::cout << /* "*/" /* "/*" */;
/* --------------更改后---------------*/
std::cout << "/*";  // 正确
std::cout << "*/";  // 正确
std::cout << /* "*/" */";  
// 末尾多增加一个 " , 注意第一个 /* 在不在引号内
std::cout << /* "*/" /* "/*" */;  
// 正确, 只要 /* 不在字符串内则与后出现的第一个 */ 构成注释段落不管第二个在不在字符串内
// 打印结果为 : /**/ */ /*
```

### 1.09 
> 编写程序，使用while循环将50到100整数相加。
```c++
#include <iostream>
int main(int argc, char * argv[]){
	int sum=0, n=50;
	while(n!=101) sum+=n++;
	std::cout<<sum;  // 3825
	/*
	for(; n<101; n++)
		sum+n;
	*/
	return 0;
}
```

### 1.10
> 除了++运算符将运算对象的值增加1之外，还有一个递减运算符--实现将值减少1 。编写程序，使用递减运算符在循环中按递减顺序打印出10到0之间的整数。
```c++
#include <iostream>
int main(int argc, char * argv[]){
	int n=10;
	while(n!=-1) std::cout<<n--<<" ";
	/*
	for(; n>-1; n--)
		std::cout<<n<<" ";
	*/
	return 0;
}
```

### 1.11
> 编写程序，提示用户输入两个整数，打印出这两个整数所指定的范围内的所有整数。
```c++
#include <iostream>
#include <utility>
int main(int argc, char * argv[]){
	int lo, hi;
	std::cout<<"Please Enter two number: \n";
	std::cin>>lo>>hi;
	if(lo>hi) std::swap(lo,hi);
	for(; lo<=hi; ++lo)
		std::cout<<lo<<" ";
	return 0;
}
```

### 1.12
> 下面的for循环完成了什么功能？sum的终值是多少？
```c++
int sum = 0;
for (int i = -100; i <= 100; ++i)
	sum += i;
```

完成 -100~100 求和, 最终值为0

### 1.13
> 使用for循环重做1.4.1节中的所有练习

参见1.09 - 1.11

### 1.14*
> 对比for循环和while循环，两种形式的优缺点各是什么？

1. for 循环 :  
	- 优点 : 控制变量的初始化和修改都放在头部分, 形式较简洁, 且特别适用于循环次数已知的情况 
	- 缺点 : 控制变量在循环结束后自动释放, 无法跟踪
2. while 循环 : 
	- 优点 :  控制变量的初始化一般放在语句之前, 修改一般放在循环体中, 适用于循环次数不知的情况 
	- 缺点 : 循环控制变量需要额外设立, 自己释放, 形式上不如for语句简洁

### 1.15
> 编写程序，包含第14页“再探编译”中讨论的常见错误。熟悉编译器生成的错误信息。

- 语法错误(syntax error)
- 类型错误(type error)
- 声明错误(declaration error)

### 1.16
> 编写程序，从cin读取一组数，输出其和。

```c++
#include <iostream>
int main(){
	long long sum=0; int n;
	while(std::cin>>n) sum+=n;
	std::cout<<sum;
	return 0;
}
```

### 1.17
> 如果输入的所有值都是相等的，本节的程序会输出什么？如果没有重复值，输出又会是怎样的？ 

### 1.18
> 编译并运行本节的程序，给它输入全都相等的值。再次运行程序，输入没有重复的值。
```c++
#include <iostream>
int main(){
	int currVal=0, val=0;
	if(std::cin>>currVal){  // 第一个数判断
		int cnt=1;
		while(std::cin>>val){
			if(val==currVal) cnt++;
			else {
				std::cout<<" Value : "<<currVal
					<<" occurs "<<cnt<<" times\n";
				currVal=val;
				cnt=1;
			}
		}
		std::cout<<" Value : "<<currVal  // 输出最后一个数
			<<" occurs "<<cnt<<" times\n";
	}
	return 0;
}
```

input :
6 6 6 6 6 6 6
output :
Value : 6 occurs 7 times

input :
1 2 3 4 5 6
output :
Value : 1 occurs 1 times
Value : 2 occurs 1 times
Value : 3 occurs 1 times
Value : 4 occurs 1 times
Value : 5 occurs 1 times
Value : 6 occurs 1 times

### 1.19
> 修改你为1.4.1节练习1.11（第11页）所编写的程序（打印一个范围内的数），使其能处理用户输入的第一个数比第二个数小的情况。

参考1.11

### 1.20
> 在网站http://www.informit.com/title/032174113 上，第1章的代码目录包含了头文件 Sales_item.h。将它拷贝到你自己的工作目录中。用它编写一个程序，读取一组书籍销售记录，将每条记录打印到标准输出上。



### 1.21
> 编写程序，读取两个 ISBN 相同的 Sales_item 对象，输出他们的和。
```c++
#include<iostream>
#include"../Sales_item.h"
using namespace std;
int main(){
    Sales_item a,b;
    cin>>a>>b;
    if(a.isbn()==b.isbn())
        cout<<a+b<<endl;
        return 0;
    else{
        cerr<<"no same books"<<endl;
        return -1;
    }
}
```

### 1.22
> 编写程序，读取多个具有相同 ISBN 的销售记录，输出所有记录的和。

### 1.23
> 读取多条聚在一起的纪录,统计结果并输出

```c++
#include<iostream>
#include"../Sales_item.h"
using namespace std;
int main(){
    Sales_item cur;
    if(cin>>cur){
        Sales_item val;
        while(cin>>val){
            if(cur.isbn()==val.isbn())
                cur+=val;
            else{
                cout<<"the book's id is "<<cur.isbn()<<
                    " average price is "<<cur.avg_price()<<endl;
                cur=val;
            }
        }
        cout<<"the book's id is "<<cur.isbn()<<
        "average price is "<<cur.avg_price()<<endl;
        return 0;
    }
    cerr<<"no books!"<<endl;
    return -1;
}
```