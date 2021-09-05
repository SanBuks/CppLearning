# 7.01
> 使用2.6.1节定义的Sales_data类为1.6节的交易处理程序编写一个新版本。

# 7.02
> 曾在2.6.2节的练习中编写了一个Sales_data类，请向这个类添加combine函数和isbn成员。

# 7.03
> 修改7.1.1节的交易处理程序，令其使用这些成员。

参考 sales\_data

# 7.04
> 编写一个名为Person的类，使其表示人员的姓名和地址。使用string对象存放这些元素，接下来的练习将不断充实这个类的其他特征。

参考 person

# 7.05
> 在你的Person类中提供一些操作使其能够返回姓名和地址。 这些函数是否应该是const的呢？解释原因。

如果只读应该是const, 返回const string & 

# 7.06
> 对于函数add、read和print，定义你自己的版本。

参考 sales\_data

# 7.07
> 使用这些新函数重写7.1.2节练习中的程序。

参考 sales\_data

# 7.08
> 为什么read函数将其Sales_data参数定义成普通的引用，而print函数将其参数定义成常量引用？

read 需要修改 sales\_data 内部数据
print 只读 sales\_data 数据

# 7.09
> 对于7.1.2节练习中代码，添加读取和打印Person对象的操作。

参考 person

# 7.10
> 在下面这条if语句中，条件部分的作用是什么？
```c++
if (read(read(cin, data1), data2)) // read返回is给第二个read传参, 报错存在隐蔽性
```

# 7.11
> 在你的Sales_data类中添加构造函数， 然后编写一段程序令其用到每个构造函数。

# 7.12
> 把只接受一个istream作为参数的构造函数移到类的内部。

# 7.13
> 使用istream构造函数重写第229页的程序。

参考 sales\_data

# 7.14
> 编写一个构造函数，令其用我们提供的类内初始值显式地初始化成员。
```c++
class A{
public:
	A():{}
	void print(){ std::cout<<a; }
private:
	int a = 3;
};
```

# 7.15
> 为你的Person类添加正确的构造函数。

参考 person

# 7.16
> 在类的定义中对于访问说明符出现的位置和次数有限定吗？ 如果有，是什么？什么样的成员应该定义在public说明符之后？ 什么样的成员应该定义在private说明符之后？

访问说明符没有位置和次数限定, 可被用户调用的公共接口在public说明符之后, 需要被隐藏的数据成员定义在private说明符之后

# 7.17
> 使用class和struct时有区别吗？如果有，是什么？

class 默认访问说明符为 private
struct 默认访问说明符为 public

# 7.19
> 在你的Person类中，你将把哪些成员声明成public的？ 哪些声明成private的？ 解释你这样做的原因。

构造函数, 访问器 声明为 public
数据成员 声明为 private

# 7.21
> 修改你的 sales\_data 类使其隐藏实现的细节。 你之前编写的关于 Sales\_data 操作的程序应该继续使用，借助类的新定义重新编译该程序，确保其正常工作。

参考 sales\_data

# 7.22
> 修改你的Person类使其隐藏实现的细节。

参考 person

# 7.23
> 编写你自己的Screen类型。

参考 screen

# 7.24
> 给你的Screen类添加三个构造函数：一个默认构造函数；另一个构造函数接受宽和高的值，然后将contents初始化成给定数量的空白；第三个构造函数接受宽和高的值以及一个字符，该字符作为初始化后屏幕的内容。

参考 screen

# 7.25
> Screen能安全地依赖于拷贝和赋值操作的默认版本吗？ 如果能，为什么？如果不能？为什么?

可以, screen中只有简单内置类型和string的类, 可以使用默认版本

# 7.26
> 将Sales_data::avg_price定义成内联函数。

参考 sales\_data

# 7.27
> 给你自己的Screen类添加move, set 和 display 函数，通过执行下面的代码检验你的类是否正确。

参考 screen

# 7.28
> 如果move、set和display函数的返回类型不是Screen& 而是Screen，则在上一个练习中将会发生什么？

改变内部数据后, 返回一个副本作为一个左值进行接下来的调用

# 7.29
> 修改你的Screen类，令move、set和display函数返回Screen并检查程序的运行结果，在上一个练习中你的推测正确吗？
 
参考 screen

# 7.30
> 通过this指针使用成员的做法虽然合法，但是有点多余。讨论显示使用指针访问成员的优缺点。

- 优点 : 防止形参与成员重名, 更加清晰反应访问的对象来源
- 缺点 : 调用复杂, 维护风格代价大

# 7.33
> 如果我们给Screen添加一个如下所示的size成员将发生什么情况？如果出现了问题，请尝试修改它。
```c++
pos Screen::size() const  // pos 没有找到定义, 需要改为 screen::pos 
{
    return height * width;
}
```

# 7.34
> 如果我们把第256页Screen类的pos的typedef放在类的最后一行会发生什么情况？

之前包含 pos 的声明和定义会报错, 未找到 pos 定义

# 7.36
> 下面的初始值是错误的，请找出问题所在并尝试修改它。
```c++
struct X {
	X (int i, int j): base(i), rem(base % j) {}  
	int rem, base;
	// int base, rem;
};
```

# 7.37
> 使用本节提供的Sales_data类，确定初始化下面的变量时分别使用了哪个构造函数，然后罗列出每个对象所有的数据成员的值。
```c++
//sales_data(const std::string &s = "")
Sales_data first_item(cin); 

int main() {
    // 默认构造函数
    Sales_data next;
	// sales_data(const std::string &s = "")
    Sales_data last("9-999-99999-9"); 
}
```

# 7.38
> 有些情况下我们希望提供cin作为接受istream&参数的构造函数的默认实参，请声明这样的构造函数。
```c++
Sales_data(std::istream &is = std::cin){
    read(is, *this);
}
```

# 7.39
> 如果接受string的构造函数和接受istream&的构造函数都使用默认实参，这种行为合法吗？如果不，为什么？

不合法, 两者都为默认构造函数, 规定每个类只能有一个默认构造函数

# 7.40
> 从下面的抽象概念中选择一个（自己指定Tree），思考这样的类需要哪些数据成员，提供一组合理的构造函数并阐明这样做的原因。
```c++
// tree.h
class Tree;

class TreeNode{
    friend class Tree;
public:
    TreeNode(int val = 0) : data(val), parent(nullptr), lchild(nullptr), rchild(nullptr){}
    unsigned long size();
private:
    int data;
    TreeNode *lchild;
    TreeNode *rchild;
    TreeNode *parent;
};

class Tree{
public:
    Tree() : root(nullptr), size(0){}
    Tree(TreeNode *p) : root(p), size(p->size()) {}
private:
    TreeNode *root;
    unsigned long size;
};

// tree.cpp
#include "Tree.h"
unsigned long TreeNode::size(){
    unsigned long size = 0;
    if(lchild) size = lchild->size();
    if(rchild) size += rchild->size();
    return size + 1;
};
```

# 7.42
> 对于你在练习7.40中编写的类，确定哪些构造函数可以使用委托。如果可以的话，编写委托构造函数。如果不可以，从抽象概念列表中重新选择一个你认为可以使用委托构造函数的，为挑选出的这个概念编写类定义。

暂时没有

# 7.44
> 下面这条声明合法吗？如果不，为什么？
```c++
vector<NoDefault> vec(10); // 不合法, 因为没有默认构造函数
```

# 7.45
> 如果在上一个练习中定义的vector的元素类型是C，则声明合法吗？为什么？

合法, C有默认构造函数 

# 7.46
> 下面哪些论断是不正确的？为什么？
```c++
(a) 一个类必须至少提供一个构造函数。  // 正确, 如果没有构造函数会合成一个默认构造函数
(b) 默认构造函数是参数列表为空的构造函数。  // 不准确, 参数列表为空或都有默认实参
(c) 如果对于类来说不存在有意义的默认值，则类不应该提供默认构造函数。 // 正确, 不提供默认构造函数 不等于 不初始化
(d) 如果类没有定义默认构造函数，则编译器将为其生成一个并把每个数据成员初始化成相应类型的默认值。 // 不准确, 没有定义任何一个构造函数时才会自动合成一个默认构造函数
```

# 7.48
> 假定Sales_data的构造函数不是explicit的，则下述定义将执行什么样的操作？
```c++
string null_isbn("9-999-9999-9"); 
Sales_data item1(null_isbn); // 调用 sales_data 的 构造函数
Sales_data item2("9-999-99999-9"); // const char * => string (string类类型转化) => 调用 sales_data 的 构造函数
```

# 7.50
> 确定在你的Person类中是否有一些构造函数应该是explicit 的。

参考 person

# 7.51
> vector将其单参数的构造函数定义成explicit的，而string则不是，你觉得原因何在？

- string 接受 const char\* 的隐式类类型转换可以方便对 c 类型字符数组转换成 string, 在多个函数中可以合理方便用于转换
- vector 不接受单参数 vector 的隐式类类型转换可以有效避免不注意的 size\_type 转换成 vector发生错误

# 7.52
> 使用2.6.1节的 Sales_data 类，解释下面的初始化过程。如果存在问题，尝试修改它。
```c++
struct Sales_data{
	std::string bookNo;
	unsigned units_sold; //  聚合类没有类内初始值, 没有构造函数
	double revenue;
};

Sales_data item = {"987-0590353403", 25, 15.99};
```

# 7.54
> Debug中以 se\t_ 开头的成员应该被声明成constexpr 吗？如果不，为什么？

constexpr 函数只可包含一个返回语句

# 7.55
> 7.5.5节的Data类是字面值常量类吗？请解释原因。

std::string 不是字面值常量类

# 7.57
> 编写你自己的Account类。
```c++
#pragma once
#include <string>
#include <iostream>
class Account{
public:
    Account(const std::string &_owner, double _amount) : owner(_owner), amount(_amount) {}

    void calculate(){ amount += amount * interestRate;}
    double getAmount() const { return amount; }

    static double rate() { return interestRate; }
    static void rate(double);
private:
    std::string owner;
    double amount;

    static double interestRate;
};

double Account::interestRate = 0.01;
void Account::rate(double newRate){
    interestRate = newRate;
}

void testAmount(){
    Account account("James", 10000);
    Account::rate(0.80);
    account.calculate();
    std::cout<<account.getAmount();
}
```