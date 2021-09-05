# 7.18 封装定义
> 封装是何含义？它有什么用处?

- 封装实现类的接口和实现分离, 隐藏实现的细节
- 确保用户代码不会无意间破坏封装对象的状态
- 封装类的具体实现可以随时改变, 无需改变用户级别的代码

# 7.20 友元作用
> 友元在什么时候有用？请分别举出使用友元的利弊。

- 友元帮助函数或其他的类可以访问类中的不可见成员
- 会破坏类的封装性, 产生安全性隐患
 
# 7.31 不完整类型
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

# 7.32 前置声明和友元
> 定义自己的Screen和Window_mgr,其中clear是Window_mgr的成员是Screen的友元
```c++
// 简略如下, 具体参考 screen 
// 总而言之, Window_mgr 中的 screen 类型均是 "pimpl"
// screen.h
#include"Window_mgr.h"
class Screen{
friend void Window_mgr::clear(ScreenIndex );
public:
   ...
};

//Window_mgr.h
class Screen;
class Window_mgr{
public:
    using ScreenIndex=std::vector<Screen>::size_type;
    Window_mgr();
    void clear(ScreenIndex);
    void print(ScreenIndex);
    ...
private:
    // 类内初始值为空 合法
    // 类内初始值为具体构造参数 不合法
    std::vector<Screen> screens{} /*{{24, 80, ''}}*/;
};

//Window_mgr.cpp
#include"Screen.h"
Window_mgr::Window_mgr(){
    screens.push_back(Screen(24,80,'x'));
}
```

# 7.35 类作用域与类型别名
> 解释下面代码的含义，说明其中的Type和initVal分别使用了哪个定义。如果代码存在错误，尝试修改它。
```c++
typedef string Type;
Type initVal(); 
class Exercise {
public:
    typedef double Type;
    Type setVal(Type);  // double 
    Type initVal();  // double
private:
    int val;
};
// 修改为 Exercise::Type 
Type Exercise::setVal(Type parm) {   // string , double
    val = parm + initVal();      
    return val; // double => string 出错
}
```

# 7.41 委托构造函数的执行顺序
> 使用委托构造函数重新编写你的Sales_data类，给每个构造函数体添加一条语句，令其一旦执行就打印一条信息。用各种可能的方式分别创建Sales_data对象，认真研究每次输出的信息直到你确实理解了委托构造函数的执行顺序。
```c++
class Sales_data{
friend std::istream &read(std::istream &is, Sales_data &item);
private:
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
    double avg_price() const;
public:
    Sales_data(): Sales_data("",0,0) { 
    	std::cout<<"default\n";
    }
    Sales_data(const std::string &s):Sales_data(s,0,0){ 						std::cout<<"string\n";
        std::cout<<"string\n"; 
    }
    Sales_data(const std::string &s, unsigned n, double p):
      bookNo(s), units_sold(n), revenue(p*n){ 
      	std::cout<<"s.u.d\n"; 
    }
    Sales_data(std::istream &is) : Sales_data() {
    	read(is,*this); 
    	std::cout<<"istream\n";
    }                
};

std::istream &read(std::istream &is, Sales_data &item){
    double price=0;
    is>>item.bookNo>>item.units_sold>>price;
    item.revenue=price*item.units_sold;
    return is;
}

int main(int argc, char *argv[]){
    Sales_data item1; // s.u.d default
    Sales_data item2("132"); // s.u.d string
    Sales_data item3(std::cin); //s.u.d default istream
    return 0;
}
```

# 7.43 无默认构造函数调用
> 假定有一个名为NoDefault的类，它有一个接受int的构造函数，但是没有默认构造函数。定义类C，C有一个 NoDefault类型的成员，定义C的默认构造函数。
```c++
#include <iostream>
class NoDefault{
public:
    NoDefault(int i) : data(i){}
	void print(){ std::cout<< data;}
private:
	int data;
};

class C{
public:
    C():nd(0){}  // 调用唯一的构造函数进行初始化
	void print(){ nd.print(); }
private:
    NoDefault nd;    
};


int main(){
	C c;
	c.print();
	return 0;
}
```

# 7.47 转换构造函数
> 说明接受一个string参数的Sales_data构造函数是否应该是explicit的，并解释这样做的优缺点。

- explicit :
  优点 : 能够抑制意想不到的隐式类类型转换
  缺点 : 需要手动调用 `Sales_data(str)`
- 非 explicit :
  优点 : 方便, 直接在可以使用 Sales\_data 直接用 string 对象替代
  缺点 : 隐式转换会产生隐藏

# 7.49 转换构造函数, 右值, 引用
> 对于combine函数的三种不同声明，当我们调用 i.combine(s) 时分别发生什么情况？其中i是一个Sales_data，而 s是一个string对象。
```c++
Sales_data& combine(Sales_data rhs); 
// 正确,发生隐式类类型转换,string->sales_data

Sales_data& combine(Sales_data& rhs); 
// 错误,无法发生隐式类类转换
/*
1. string -> sales_data 产生临时变量 temporary_rhs (右值)
2. sales_data & rhs = temporary_rhs; 
3. 进入函数体或者括号结束后 临时变量temporary_rhs销毁, 编译器报错
*/

Sales_data& combine(const Sales_data& rhs) const; 
// 错误,const this指针无法改变类成员

Sales_data& combine(const Sales_data& rhs) ; 
// 正确,可以发生隐式类类型转换, 虽然是 Sales_data -> const Sales_data& rhs 符合调用函数匹配条件
/*
1. string -> sales_data 产生临时变量 temporary_rhs
2. const sales_data temp = tempporary_rhs; 将右值赋予 const 左值
3. const sales_data & rhs = temp; ( 2,3 步等价 var->const var&  )
4. 进入函数体,处理完后自动变量(形参)销毁
*/
```

参考[链接](https://stackoverflow.com/questions/31444343/cconfusion-about-converting-constructor-when-using-the-result-as-parameter-of)

# 7.53 字面值常量类
> 定义你自己的Debug。
```c++
// debug.h
class Debug{
public:
    constexpr Debug(bool b = true) : hw(b), io(b), other(b){}
    constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o){}
    constexpr bool any() const { return hw | io | other; }

    void set_hw(bool b) const { hw = b; }
    void set_io(bool b) const { io = b; }
    void set_other(bool b) const { other = b; }

private:
    bool mutable hw;
    bool mutable io;
    bool mutable other;
};

// test.cpp
#include <iostream>
#include "debug.h"

int main(){
	constexpr Debug debug(false, false, true);
	debug.set_other(false);
	std::cout << debug.any();
	return 0;
}
```

# 7.56 类静态成员
> 什么是类的静态成员？它有何优点？静态成员与普通成员有何区别？

- 类的静态成员定义 : 与类本身相关, 不与各个类对象关联的类成员, 类对象共享静态成员变量却不包含静态成员数据
- 优点与区别 : 定义一次直到程序结束销毁, 不占类对象空间, 可以是不完全类型, 可以作为成员函数默认实参 (constexpr const 类型 )

# 7.58 类静态成员
> 下面的静态数据成员的声明和定义有错误吗？请解释原因。
```c++
// example.h
#include<vector>
class Example{
public:
    // 1. 错误, 类内初始化静态成员需要用 constexpr 修饰
    static double rate=6.5;  
    // static constexpr double=6.5;
    
    // 2. 正确, 此时 constexpr 与 const 没有区别
    static const int vecSize=20;   
    
    // 3. 错误, 类内初始化需要 constexpr 修饰,vector 不可被 constexpr 修饰, 需要在类外定义
    static std::vector<double> vec(vecSize); 
    // static std::vector<double> vec;
};

//example.cpp
#include"example.h"
double Example::rate;   // 错误, 类内初始化后在外部定义需要const修饰, 由于已在类内初始化则无需再初始化了
// const double Example::rate;

std::vector<double> Example::vec;  // 错误, 没有对vector的参数进行初始化
// std::vector<double> Example::vec(Example::vecSize);
// 这里vecSize在类作用域中, 无需在类外进行一次定义
```