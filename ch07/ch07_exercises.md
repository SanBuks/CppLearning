# 第七章
### 7.01
> 
```c++

```

1. (7.18)封装是什么?有什么用处?
- 封装实现类的接口和实现分离,隐藏实现的细节,产生数据抽象
- 确保用户代码不会无意间破坏封装对象的状态
- 封装类的具体实现可以随时改变,无需改变用户级别的代码
2. (7.20)友元的利弊
- 友元帮助函数或其他的类可以访问类中的不可见成员
- 会破坏类的封装性,产生安全性隐患
3. (7.25)screen类可以安全地依赖默认的拷贝和赋值操作吗?
- 可以,screen中只有简单内置类型和string的类,可以使用默认版本
4. (7.30)显示使用this访问成员的优缺点
- 优点:防止形参与成员重名,更加清晰反应访问的对象来源
- 缺点:调用复杂,维护风格代价大
5. (7.31)定义一对类X和Y,其中X包含一个指向Y的指针,而Y包含一个类型为X的对象
```c++
class Y;
class X{
    Y *p=nullptr;
};
class Y{
    X item;
};
```
6. (7.32)定义自己的Screen和Window_mgr,其中clear是Window_mgr的成员是Screen的友元
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