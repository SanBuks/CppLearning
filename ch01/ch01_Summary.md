# 第一章 编写一个简单的C++程序
## 1. 初识输入输出
- 流定义 : 随着时间推移,字符被生成或消耗的字符序列
- iostream库 : 包含istream,ostream两个基础类型, 其中cin, cout 为标准输入输出流 cerr, clog为标准错误流和标准日志流
- 流对象 : `std::cout<<"123";`的返回值是cout对象, 当其用于条件判断时如`while(cin>>a){...}`调用其bool运算符, 当检测到文件结束符(EOF)后状态变为无效, 返回false

## 2. 缓冲区
- 缓冲区 : 协调IO设备与CPU速度不匹配问题, 减少IO读写次数, 缓冲区类型有 : 
	1. 全缓冲 : 写满限制大小才输入输出, 如 cin cout 写文件
	2. 行缓冲 : 遇到换行符后才真正输入输出, 如 printf(linux) scanf函数
	3. 不带缓冲 : 没有缓存直接输入输出, 如 getchar() putchar()
- 关联 : 一般将输入流与输出流相关联, 对输入流操作时会先刷新输出流的缓冲区
|流对象|是否缓冲|其他信息|
|---|---|---|
|cin|全缓冲|跳过空白符,与cout关联,有缓冲残留问题|
|cerr|不缓冲|用于打印错误信息,与cout关联|
|clog|全缓冲|用于打印一般性信息,不关联任何流|
|cout|全缓冲|需要手动刷重新|

> C与C++中的空白符为 :  ' '(SPC), '\t' (TAB), '\n'(LF), '\v'(VT), '\f'(FF), '\r'(CR)

## 3. 命名空间
- 命名空间 : 将库中的名字放在单一位置, 解决名字冲突问题, 比如标准库命名空间std, 一般头文件不包含using声明, 防止命名冲突
- using声明 : `using namespace::name;` 一次引进一个命名空间的成员, 作用域从声明开始到结束, 此时外层同名实体被隐藏(存在例外如 operator=函数) 
- 库名字改动 : C语言头文件`xxx.h`变为`cxxx`,让`cxxx`中的名字从属于相关的命名空间

## 4. 其他
- Win 下 `^ + Z + Enter`结束输入 Unix 下 `^ + D`结束输入 
- `$ exename < infile > outfile` 通过流重定向简化输入输出
- `std::ios_base::sync_with_stdio(false);` 关闭标准流与标准C流同步加快速度, 之后不能混用否则会导致未知的插入字符出现
	- 的
		- 123
			- 123 
### 4. 例题
1. (1.14) for与while的优缺点(二者也可以互相转化)  
	1. 在for循环中,循环控制变量的初始化和修改都放在头部分,形式较简洁,且特别适用于循环次数已知的情况。
	2. 在while循环中,循环控制变量的初始化一般放问在while语句之答前,循环控制变量的修改一般放在循环体中,形式上不如for语句简洁,适用于循环次数不知的情况
	3. for局部变量i再循环结束后自动清除,while要额外设立变量

2. (1.21) 读取两个相同的sales_item对象,并输出和
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
// 编译命令 $ g++ test.cpp -o atest.o -std=c++11 -Wall -g
```
3. (1.23) 读取多条聚在一起的纪录,统计结果并输出
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
