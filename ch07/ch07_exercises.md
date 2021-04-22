# 第七章
### 7.01
> 使用2.6.1节定义的Sales_data类为1.6节的交易处理程序编写一个新版本。

### 7.02
> 曾在2.6.2节的练习中编写了一个Sales_data类，请向这个类添加combine函数和isbn成员。

### 7.03
> 修改7.1.1节的交易处理程序，令其使用这些成员。

参考 Sales\_data

### 7.04
> 编写一个名为Person的类，使其表示人员的姓名和地址。使用string对象存放这些元素，接下来的练习将不断充实这个类的其他特征。

参考Person

### 7.05
> 在你的Person类中提供一些操作使其能够返回姓名和地址。 这些函数是否应该是const的呢？解释原因。

如果只读应该是const, 返回const string & 

### 7.06
> 对于函数add、read和print，定义你自己的版本。

参考 Sales\_data

### 7.07
> 使用这些新函数重写7.1.2节练习中的程序。

参考 Sales\_data

### 7.08
> 为什么read函数将其Sales_data参数定义成普通的引用，而print函数将其参数定义成常量引用？

read 需要修改 Sales\_data 内部数据
print 只读 Sales\_data 数据

### 7.09
> 对于7.1.2节练习中代码，添加读取和打印Person对象的操作。

参考 Person

### 7.10
> 在下面这条if语句中，条件部分的作用是什么？
```c++
if (read(read(cin, data1), data2)) // read返回is给第二个read传参, 报错存在隐蔽性
```

### 7.11
> 在你的Sales_data类中添加构造函数， 然后编写一段程序令其用到每个构造函数。

### 7.12
> 把只接受一个istream作为参数的构造函数移到类的内部。

### 7.13\*
> 使用istream构造函数重写第229页的程序。
```c++
void test_combine_refactor(){ 
    Sales_data total(std::cin);
    if(std::cin){
        Sales_data trans(std::cin);
        while(std::cin){
            if(total.isbn() == trans.isbn())
                total.combine(trans);
            else{
                print(std::cout, total);
                std::cout<<"\n";
                total = std::move(trans);
            } 
            trans = std::move(Sales_data(std::cin));
        }
        print(std::cout, total);
    }else{
        std::cerr << "No data!\n";
    }
}
```

### 7.14
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

### 7.15
> 为你的Person类添加正确的构造函数。

参考 Person

### 7.16
> 在类的定义中对于访问说明符出现的位置和次数有限定吗？ 如果有，是什么？什么样的成员应该定义在public说明符之后？ 什么样的成员应该定义在private说明符之后？

访问说明符没有位置和次数限定, 可被用户调用的公共接口在public说明符之后, 需要被隐藏的数据成员定义在private说明符之后

### 7.17
> 使用class和struct时有区别吗？如果有，是什么？

class 默认访问说明符为 private
struct 默认访问说明符为 public

### 7.18
> 封装是何含义？它有什么用处?

- 封装实现类的接口和实现分离, 隐藏实现的细节, 产生数据抽象
- 确保用户代码不会无意间破坏封装对象的状态
- 封装类的具体实现可以随时改变, 无需改变用户级别的代码

### 7.19
> 在你的Person类中，你将把哪些成员声明成public的？ 哪些声明成private的？ 解释你这样做的原因。

构造函数, 访问器 声明为 public
数据成员 声明为 private

### 7.20
> 友元在什么时候有用？请分别举出使用友元的利弊。

- 友元帮助函数或其他的类可以访问类中的不可见成员
- 会破坏类的封装性, 产生安全性隐患

### 7.21
> 修改你的 Sales\_data 类使其隐藏实现的细节。 你之前编写的关于 Sales\_data 操作的程序应该继续使用，借助类的新定义重新编译该程序，确保其正常工作。

参考 Sales\_data

### 7.22
> 修改你的Person类使其隐藏实现的细节。

参考 Person

### 7.23
> 编写你自己的Screen类型。

参考 Screen

### 7.24
> 给你的Screen类添加三个构造函数：一个默认构造函数；另一个构造函数接受宽和高的值，然后将contents初始化成给定数量的空白；第三个构造函数接受宽和高的值以及一个字符，该字符作为初始化后屏幕的内容。

参考 Screen

### 7.25
> Screen能安全地依赖于拷贝和赋值操作的默认版本吗？ 如果能，为什么？如果不能？为什么?

可以, screen中只有简单内置类型和string的类, 可以使用默认版本

### 7.26
> 将Sales_data::avg_price定义成内联函数。

参考 Sales\_data

### 7.27
> 给你自己的Screen类添加move、set 和display函数，通过执行下面的代码检验你的类是否正确。
```c++
// 注意, inline 函数定义在头文件中
int main(){
    Screen myScreen(5, 3);
    const Screen blank(5, 3);
    myScreen.set('#').display(std::cout);
    std::cout<<"\n";
    blank.display(std::cout);
    return 0;
}
```

### 7.28
> 如果move、set和display函数的返回类型不是Screen& 而是Screen，则在上一个练习中将会发生什么？

改变内部数据后, 返回一个副本作为一个左值进行接下来的调用

### 7.29
> 修改你的Screen类，令move、set和display函数返回Screen并检查程序的运行结果，在上一个练习中你的推测正确吗？
```c++
class Screen{
	...
    inline 
    Screen copyDisplay(std::ostream &os){
        do_display(os); return *this;
    }
};

void testReturnLeftValue(){
    Screen myScreen1(5, 3, '*');
    myScreen1.display(std::cout).set('#');
    myScreen1.display(std::cout);

    std::cout<<"\n";

    Screen myScreen2(5, 3, '*');
    myScreen2.copyDisplay(std::cout).set('#');
    myScreen2.display(std::cout);

    // 显示 : 
    // *****************************#
	// ******************************
}
```

### 7.30
> 通过this指针使用成员的做法虽然合法，但是有点多余。讨论显示使用指针访问成员的优缺点。

- 优点 : 防止形参与成员重名, 更加清晰反应访问的对象来源
- 缺点 : 调用复杂, 维护风格代价大

### 7.31
> 定义一对类X和Y，其中X包含一个指向Y的指针，而Y包含一个类型为X的对象。
```c++
class Y;
class X{
    Y *p=nullptr;
};
class Y{
    X item;
};
```

### 7.32
> 定义自己的Screen和Window_mgr,其中clear是Window_mgr的成员是Screen的友元
```c++
//test.cpp
#include"Screen.h"
int main(){
    Window_mgr m;
    m.print(0);
    m.clear(0);
    m.print(0);
    return 0;
}

// Screen.h
#ifndef SCREEN_H
#define SCREEN_H
#include<iostream>
#include<cstring>
#include"Window_mgr.h"
class Screen{
friend void Window_mgr::clear(ScreenIndex );
public:
    typedef std::string::size_type pos;
    Screen()=default;
    Screen(pos ht, pos wd, char c):height(ht),width(wd),contents(ht*wd, c){}
    const Screen &display(std::ostream &os) const { do_display(os); return *this; }
private:
    pos cursor=0;
    pos height=0, width=0;
    std::string contents;
    void do_display(std::ostream &os) const { os<<contents; }
};
#endif

//Window_mgr.h
#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H
#include<vector>
class Screen;
class Window_mgr{
public:
    using ScreenIndex=std::vector<Screen>::size_type;
    Window_mgr();
    void clear(ScreenIndex);
    void print(ScreenIndex);
private:
    std::vector<Screen> screens{};//Screen(24,80,' ')
};
#endif

//Window_mgr.cpp
#include"Window_mgr.h"
#include"Screen.h"
void Window_mgr::print(ScreenIndex i){
    screens[i].display(std::cout);
}
Window_mgr::Window_mgr(){
    screens.push_back(Screen(24,80,'x'));
}
void Window_mgr::clear(ScreenIndex i){
    Screen &s=screens[i];
    s.contents=std::string(s.height*s.width,' ');
}
```


7. (7.41)重新编写Sale_data类,给每个构造函数添加打印信息,探究委托构造函数的调用顺序
```c++
class Sales_data{
friend std::istream &read(std::istream &is, Sales_data &item);
private:
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
    double avg_price() const;
public:
    Sales_data(): Sales_data("",0,0) { std::cout<<"default\n";}
    Sales_data(const std::string &s):Sales_data(s,0,0){ std::cout<<"string\n";}
    Sales_data(const std::string &s, unsigned n, double p):
                bookNo(s), units_sold(n), revenue(p*n){ std::cout<<"s.u.d\n"; }
    Sales_data(std::istream &is): Sales_data() {read(is,*this); std::cout<<"istream\n";};                
};
std::istream &read(std::istream &is, Sales_data &item){
    double price=0;
    is>>item.bookNo>>item.units_sold>>price;
    item.revenue=price*item.units_sold;
    return is;
}
int main(int argc, char *argv[]){
    Sales_data item; // s.u.d default
    Sales_data item("132"); // s.u.d string
    Sales_data (std::cin); //s.u.d default istream
    return 0;
}
```
8. (7.43,45)假定有一个名为NoDefault类,有一个接受int的构造函数,没有默认构造函数.定义类C,有一个NoDefault类型成员,定义C的默认构造函数. vector\<C> vec(10);合法吗?
```c++
class NoDefault{
public:
    NoDefault(int i){}
};

class C{
public:
    C():nd(NoDefault(0)){}
private:
    NoDefault nd;    
};

int main(){
    C c;
    std::vector<C> vec(10); // 合法 C中的默认构造函数在初始化列表中调用接受int类型的构造函数初始化NoDefault
    return 0;
}
```
9.  (7.49) 对于combine函数的三种不同声明，当我们调用i.combine(s)时分别发生了什么情况？其中i是一个Sales_data(含有非explicit的转化构造函数)，而s是一个string对象
参考[链接](https://stackoverflow.com/questions/31444343/cconfusion-about-converting-constructor-when-using-the-result-as-parameter-of)
```c++
Sales_data& combine(Sales_data rhs); // 正确,发生隐式类类型转换,string->Sales_data
Sales_data& combine(Sales_data& rhs); // 错误,无法发生隐式类类转换
/*
1. string -> Sales_data 产生临时变量 temporary_rhs
2. Sales_data & rhs = temporary_rhs; 
3. 进入函数体或者括号结束后临时变量temporary_rhs销毁,编译器报错
*/
Sales_data& combine(const Sales_data& rhs) const; // 错误,const this指针无法改变类成员
Sales_data& combine(const Sales_data& rhs) ; // 正确,可以发生隐式类类型转换
/*
1. string -> Sales_data 产生临时变量 temporary_rhs
2. const Sales_data temp = tempporary_rhs;
3. const Sales_data & rhs = temp;(2,3步等价var->const var& 第二章知识点)
4. 进入函数体,处理完后自动变量(形参)销毁
*/
```
10.  (7.51)vector将其单参数的构造函数定义成explicit,而string不是,原因何在?
- string接受const char*的隐式类类型转换可以方便对c类型字符数组转换成string,在多个函数中可以合理方便用于转换
- vector不接受单参数vector的隐式类类型转换可以有效避免不注意的size_type转换成vector发生错误
11.  (7.56)什么是类的静态成员?有何优点?与普通成员有何区别?
- 类的静态成员定义 : 与类本身相关,不与各个类对象关联的类成员,类对象共享静态成员变量却不包含静态成员数据
- 优点与区别 : 定义一次直到程序结束销毁,不占类对象空间,可以是不完全类型,可以作为成员函数默认实参(constexpr类型)
12.  (7.58)下面的静态数据成员的声明和定义有错误吗?请解释原因
```c++
//example.h
#include<vector>
class Example{
public:
    static double rate=6.5;  // 错误,类内初始化静态成员需要用constexpr修饰
    // static constexpr double=6.5;

    static const int vecSize=20;   // 正确,此时constexpr与const没有区别

    static std::vector<double> vec(vecSize); 
    // 错误,类内初始化需要constexpr修饰,vector不可被constexpr修饰,需要在类外定义
    // static std::vector<double> vec;
};

//example.cpp
#include"example.h"
double Example::rate;  //错误,类内初始化后在外部定义需要const修饰,由于已在类内初始化则无需再初始化了
//double const Example::rate;

std::vector<double> Example::vec;  //错误.没有对vector的参数进行初始化
//std::vector<double> Example::vec(Example::vecSize);
//这里vecSize在类作用域中,无需在类外进行一次定义
//总结:最好不要类内初始化，否则必须是常量静态成员
```