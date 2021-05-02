# 1. 让自己熟悉CPP
## CPP视为语言联邦
- C语言 : 面向过程
- 封装, 继承, 多态 : 面向对象
- STL, 模板 : 泛型编程

## 类内静态成员初始化后可作数组定义下标
- 一般类内声明, 类外定义(cpp中)
- 如果静态成员类内初始化 必须 :
    - constexpr 修饰 的 字面值类型 
    - 初识值是常量表达式
    - 类外需定义一次不必初始化

## enum hack 替换 
- 类内初始化, 也可做数组下标,
- 且不是对象没有地址 

## 尽量使用 const
- 尽量限制用户对参数的改动
- 作为 const 返回值放止作为左值 (&&限定符)
- const 成员函数会因为对象是否const而发生重载
- logical const 理念 : const 成员函数可以修改对象的bits, 前提是用户侦测不出来的情况下, 使用mutable限定这些bits
- non-const成员函数 委托 const 成员函数
```c++
const char &operator[](std::size_t posi) const { 
  return text[posi];
}
char &operator[](std::size_t posi) { 
  return const_cast<char &>(static_cast<const A&>(*this)[posi]);
}
// 反过来, const 成员函数不应该委托 non-const 成员函数
// 如果调用 non-const 成员 需要 const_cast<A &>(*this)[posi] 危险 
```

## 定义对象时候一定赋予初识值完成初始化
- 总使用初识值列表初始化, 对所有数据成员进行初始化 (包含默认初始化)
- 构造函数可以委托 或者 将赋值成本较低的元素封装在 其他初始化函数中
- 初识值列表按声明顺序初始化, 基类成员先被初始化

## non-local static 对象在不同编译单元的依存问题
```c++
// c++ 未规定跨编译单元 non-local static 对象的初始化顺序

// a.cpp
// lazy-evaluated, correctly-destroyed, and thread-safe
// c++11 standard guarnted that If control enters the declaration concurrently while the variable is being initialized, the concurrent execution shall wait for completion of the initialization.
class Singleton{
public:
  static Singleton &get(){
    static Singleton;
    return Singleton;
  }
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

private:
  Singleton() { }
};

// b.cpp
Singleton aa=Singleton::get();
```


# 2. 构造,析构和赋值运算
## 空类自动创建 dctor, dtor, cctor 和 =
- 他们在调用时才自动创建
- dctor 默认为 non-virtual, 除非父类有virtual dctor
- 如果数据成员是 const 或者 引用,  则相关合成拷贝函数为删除状态
- 泛化来说, 合成的拷贝控制函数会因各种情况能否合成而变成删除状态

## 阻止copy
- 将相关操作设为private, 且不实现, 类外无法访问, 类中产生链接错误
- 或者继承 Uncopyable类
- C++11 `=deleted` ;
```c++
class Uncopyable {
protected: // 避免被创建
	Uncopyable() {}
	~Uncopyable() {}  // 不一定为virtual 减少数据内存
private:
	Uncopyable(const Uncopyable &);
	Uncopyable &operator=(const Uncopyable &);
};
class A : private Uncopyable {...}; // private 蕴含 基于某类机制上实现出来
```

## 实现多态的基类析构函数必是virtual
- 派生类对象由 实现多态的基类 的指针删除, 如果基类析构函数是 non-virtual 结果未定义
- 可能派生类数据没有销毁, 产生局部销毁
- 非实现多态的基类, 析构函数如果是virtual反而增加机器字长大小的vptr
- 如果有virtual函数则析构函数声明为virtual
- string, vector, list等等STL容器没有virtual dctor

## 实现多态的基类可以是纯虚基类
```c++
class Base{
public:
	virtual ~Base()=0;
};
Base :: ~Base(){} // 注意增加析构函数的定义, 从派生向上逐步调用析构函数
```

## 析构函数不鼓励抛出异常
- 因为容器销毁时会发生多个异常抛出产生未定义情况
- 捕获异常, 记录信息, 然后终止程序
- 吞下异常, 记录信息
- 最好设定新的close成员函数和closed标志,  然后析构函数中采取上两种之一操作
```c++
class A {
  void close() { ... } // 给用户提供处理析构异常的机会,
  ~A() {
    if (!closed) {
      try{
        close();
      } catch(std::Exception &e) {
        ...
        std::abort();
      }
    }
  }
  bool closed = false;
};
```

## ctor和dtor中不要用虚函数
- 基类中调用虚函数不会下降到派生类中, 调用虚函数参考析构和构造所在类 
- 注意ctor和dtor中的子函数也不能使用虚函数
- 相关运行期类型信息也是基类类型
```c++
// Base中将相关虚函数变为非虚函数, 通过派生类的所传递的信息来处理
class Derived : public Base{
	Derived() : Base(createLogString()){...}
private:
	static std::string createLogString();  
	// static 决定其函数内不可使用构造期间未初始化的成员变量
};
```

## operator=写法
- return \*this;
- 处理自赋值 : 先复制再删除 或者 copy and swap

## 复制对象勿忘每个成分
- ctor, cctor, =, 非标准 = 必须密切注意每个数据成员 ( 改动的和新加的 ) 
- 在派生类中务必加上基类的相关拷贝操作
- 不能 = 和 cctor 互相调用(不符合语义)
- 如果存在重复代码可以新建 private: init() 减少重复 
```c++
D::D(const D &rhs):B(rhs),....{}
D& D::operator=(const D &rhs){
	B::operator=(rhs);
	...
	return *this;
}
```

# 3. 资源管理
## RAII(Resource Acquisition Is Initialization) 
- `auto_ptr` 确保只有一个 `auto_ptr` 指向资源, 所以被复制时会被置空, C++11被 `unique_ptr` 取代
- 智能指针只会调用delete, 对于默认对内置数组调用 delete 会产生错误, 需要手动添加 delete 调用对象
```c++
unique_ptr<int[]> up(new int[10]()); //可以通过unique_ptr管理手动分配的数组
shared_ptr<int> sp(new int[10](), // 可以通过shared_ptr管理手动分配的数组
	[](int *p) { delete [] p;} ); // 但是必须提供删除器
```

## 资源管理类的拷贝行为
- 禁止复制
- 引用计数 (shared\_ptr)
- 深复制
- 转移资源 (unique\_ptr) : reset()
```c++
#include <iostream>
#include <memory>

void LockMutex(int *) {
  std::cout << "Lock! \n";
}
void UnlockMutex(int *) {
  std::cout <<"Unlock! \n";
}

class Lock {
 public:
  explicit Lock(int *metex_ptr) : mutex_ptr_(metex_ptr, Deleter) {  
    LockMutex(mutex_ptr_.get());
  }
 private:
  static void Deleter(int *p) {  // 删除器不能为非静态, 模板推导会出错
    UnlockMutex(p);
  }
  std::shared_ptr<int> mutex_ptr_;
};

int main() {
  {
    int *p = new int(3);
    Lock lock(p);
  }
  return 0;
}
```

## 资源管理类一般要提供底层指针
- smartPtr.get() 返回底层指针
- operator Type() 自定义隐式转换得到底层指针

## delete配对
- `delete [] arrname;`  一般对数组名不进行别名声明, 否则一定检查是否要加上[], 或者尽量用 vector

## 以独立语句将 newed 对象放入智能指针
- 防止表达式求值顺序未定义问题
```c++
// OtherFunc() 函数调用次序和 shared_ptr 调用次序未定义会产生麻烦
func(std::shared_ptr<C>(new C), Otherfunc());
```

# 4. 设计与声明
## 让接口容易被使用,不易被误用
- 导入新的类型, 防止误用, 同时增加输入限制
- 尽量保持类型与内置类型, STL 的一致性, 如通用接口名, 类型别名, 返回类型是否为左值等等
- 用智能指针管理资源, 额外还可以消除 cross-dll 问题, 智能指针差不多是raw pointer 两倍大(计数, 删除器, 同步)
```c++
// Date d(2000,1,30); -> 
// Date d(Year(2000), Month(1), Day(30)) -> 
// Date d(Month::Jan(), Day(30), Year(1995));
class Month{
 public:
  static Month Jan() { return Month(1); }
 private:
  explicit Month(int m);
};
```

## 设计Class考虑
- 是否需要新的Class, 还是Template, 如果需要则要继承吗? 是否可以被继承?
- 资源创建, 销毁与拷贝(ctor, dtor, cctor, operator= , 移动构造, 移动赋值) 及 是否允许拷贝控制
- 资源的合法值
- 是否有合理的转换类型
- 访问控制

## 尽量 pass by (const) reference
- 性能, 减少自动变量不必要的构造与析构
- 防止 pass by value 产生基类的 silcing 问题
- 对于 内置类型, 迭代器, 函数对象列外
- 自定义小类型为防止拓展和编译器的"特殊对待" 也要尽量 引用传递

## 别返回局部对象的引用
- 对于 `operator*` 返回局部引用会产生错误, 应该直接返回一个新对象
- 对于 通过 static 局部对象返回引用最终会产生最优化问题, 这应该交给编译器进行优化

## private
- private 封装 数据对象, 产生读写控制
- 封装的最重要功能是保持拓展性
- 提供接口时强调 反应数据速度 还是 数据占用内存空间 需要权衡

## non-member & non-friend  > member
- 愈多能够访问数据的方法, 越低的封装性, 越低的可拓展性, 重用性导致后期维护成本飙升
```c++
// 对于命名空间分离式的声明, 有利于减少编译产生的冗余问题
// web_browser.h
namespace WebBrowserStuff{
  ...
};

// web_browser_bookmarks.h
namespace WebBrowserStuff{
  ...
}
```

## 所有参数皆需类型转换则采用 non-member
- 对于二元运算符和某些参数可以转换为Type的类, 尽量用 non-member 函数取代 member 函数
- 优先选择 non-friend&member 函数
```c++
Class A {
 public:
// 如果 没有接口data 则将 operator+ 声明为 friend 
  A(int);
  int data() const { return data; }
  ...
 private:
  int data;
};

A operator+(const A &lhs, const A &rhs) {
  return lhs.data()+rhs.data();
}
```

## swap() nonexcept


## PImpl
```c++
// test.h
#include <memory>
class Widget {
  class WidgetImpl; // 1. 前置的Impl类
 public:
  explicit Widget(int number);
  ~Widget();
  Widget(const Widget &rhs) = delete;
  Widget(Widget &&rhs);
  Widget &operator =(const Widget &rhs) = delete;
  Widget &operator =(Widget &&rhs);

  void show();
 private:
  std::unique_ptr<WidgetImpl> Pimpl;  // 2. 保存Impl类的 Pimpl
};

// test.cc
#include "test.h"
#include <iostream>
class Widget::WidgetImpl{  //  首先实现 Impl 类
 public:
  explicit WidgetImpl(int number);
  ~WidgetImpl();
  WidgetImpl(const WidgetImpl &rhs) = delete;
  WidgetImpl(WidgetImpl &&rhs) = delete;
  WidgetImpl &operator =(const WidgetImpl &rhs) = delete;
  WidgetImpl &operator =(WidgetImpl &&rhs) = delete;

  void show();
 private:
  int number_;
};

Widget::WidgetImpl::WidgetImpl(int number) : number_(number) {}
Widget::WidgetImpl::~WidgetImpl() { 
  std::cout << "Dtor : " << number_ << "\n"; 
}
void Widget::WidgetImpl::show() {
  std::cout << number_ << "\n";
}

// 再实现 Widget 的相关接口
Widget::Widget(int number) : Pimpl(new WidgetImpl(number)) { }
Widget::~Widget() = default;
Widget::Widget(Widget &&rhs) : Pimpl(std::move(rhs.Pimpl)){ }
Widget &Widget::operator =(Widget &&rhs) { 
  Pimpl  = std::move(rhs.Pimpl); 
  return *this;
}
void Widget::show() { Pimpl->show(); }


int main() {
  Widget w(3);
  Widget s(2);
  w.show();
  s.show();
  w = std::move(s);
  w.show();
}
```