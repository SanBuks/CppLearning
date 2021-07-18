# 1.03
> 编写程序，在标准输出上打印Hello, World。
```c++
#include <iostream>
int main(int argc, char * argv[]){
	std::cout<<"hello world\n";
	return 0;
}
```

# 1.04
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

# 1.05
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

# 1.06
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

# 1.07
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

# 1.09 
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

# 1.10
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

# 1.11
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

# 1.12
> 下面的for循环完成了什么功能？sum的终值是多少？
```c++
int sum = 0;
for (int i = -100; i <= 100; ++i)
	sum += i;
```

完成 -100~100 求和, 最终值为0

# 1.13
> 使用for循环重做1.4.1节中的所有练习

参见1.09 - 1.11

# 1.16
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

# 1.17
> 如果输入的所有值都是相等的，本节的程序会输出什么？如果没有重复值，输出又会是怎样的？ 

# 1.18
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

# 1.19
> 修改你为1.4.1节练习1.11（第11页）所编写的程序（打印一个范围内的数），使其能处理用户输入的第一个数比第二个数小的情况。

参考1.11

# 1.20
> 在网站http://www.informit.com/title/032174113 上，第1章的代码目录包含了头文件 Sales_item.h。将它拷贝到你自己的工作目录中。用它编写一个程序，读取一组书籍销售记录，将每条记录打印到标准输出上。
```c++
// ./atest < ch01_data/data_1_20
#include <iostream>
#include "Sales_item.h"
int main(){
	Sales_item curr;
	while(std::cin>>curr)
		std::cout<<curr<<"\n";
	return 0;
}
```

# 1.21
> 编写程序，读取两个 ISBN 相同的 Sales_item 对象，输出他们的和。
```c++
// ./atest < ch01_data/data_1_21
#include<iostream>
#include"Sales_item.h"
using namespace std;
int main(){
    Sales_item a,b;
    cin>>a>>b;
    if(a.isbn()==b.isbn()){
        cout<<a+b<<endl;
        return 0;
	}else{
        cerr<<"no same books"<<endl;
        return 1;
    }
}

```

# 1.22
> 编写程序，读取多个具有相同 ISBN 的销售记录，输出所有记录的和。
```c++
// ./atest < ch01_data/data_1_22
#include<iostream>
#include"Sales_item.h"
using namespace std;
int main(){
    Sales_item sum, book;
	if(cin>>sum){
		while(cin>>book)
			sum+=book;
        cout<<sum<<endl;
		return 0;
	}else{
    	cerr<<"no books"<<endl;
        return 1;
	}
}
```

# 1.23
> 编写程序，读取多条销售记录，并统计每个 ISBN（每本书）有几条销售记录。
```c++
// ./atest < ch01_data/data_1_23
#include <iostream>
#include <map>
#include "Sales_item.h"
int main(){
    Sales_item cur;
	Sales_item val;
	std::map<std::string, Sales_item> result;
	while(std::cin>>val)
		result[val.isbn()]+=val;
	for(const auto &w : result){
		std::cout<<"the book id is "<<w.first;
		std::cout<<" average price is "<<w.second.avg_price()<<'\n';
	}
	return 0;
}
```

# 1.24
> 读输入表示多个 ISBN 的多条销售记录来测试上一个程序，每个 ISBN 的记录应该聚在一起。
```c++
// ./atest < ch01_data/data_1_24
#include<iostream>
#include"Sales_item.h"
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

# 1.25
> 借助网站上的Sales_item.h头文件，编译并运行本节给出的书店程序。

参考1.24

