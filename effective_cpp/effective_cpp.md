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
  // 注意 转换为 const A& ， 如果事 const A 会发生拷贝
}
// 反过来, const 成员函数不应该委托 non-const 成员函数
// 如果调用 non-const 成员 需要 const_cast<A &>(*this)[posi] 危险 
// 
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
## 空类自动创建 dctor, dtor, cctor 和 operator =
- 他们在调用时才自动创建
- dctor 默认为 non-virtual, 除非父类有virtual dctor
- 如果数据成员是 const 或者 引用,  则相关合成拷贝函数为删除状态
- 泛化来说, 合成的拷贝控制函数会因各种情况无法合成而变成删除状态

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
- 派生类对象由指向实现多态的基类指针而删除, 如果基类析构函数是 non-virtual 结果未定义
- 可能派生类数据没有销毁, 产生局部销毁
- 非实现多态的基类, 析构函数如果是virtual反而增加机器字长大小的 vptr
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

## ctor 和 dtor 中不要用虚函数
- 基类中调用虚函数不会下降到派生类中, 调用的虚函数参考析构和构造时所在的类 
- 注意 ctor 和 dtor 中的子函数也不能使用虚函数
- 相关运行期类型信息也是基类类型
```c++
// 处理方法, Base中将相关虚函数变为非虚函数, 通过派生类传递给基类构造函数相关信息来处理
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
- 不能 = 和 cctor 互相调用(不符合语义), 如果存在重复代码可以新建 private: init() 减少重复 
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
- 智能指针只会调用 delete, 对于默认对内置数组调用 delete 会产生错误, 需要手动添加 delete 调用对象
```c++
shared_ptr<int[]> up(new int[10]); // 管理手动分配的数组 调用删除器:template< class T > struct default_delete<T[]>;
shared_ptr<int> sp(new int[10], // 管理手动分配的数组 自定义删除器
	[](int *p) { delete [] p;} ); 
```

## 资源管理类的拷贝行为
- 禁止复制
- 引用计数 (shared\_ptr)
- 深复制
- 转移资源 (unique\_ptr) : reset()
```c++
#include <iostream>
#include <memory>
//  拿互斥器举例
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

## delete 配对
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
- 对于 通过 static 局部对象返回引用最终会产生 线程安全 和 static对象数组的最优化问题, 这应该交给编译器进行优化

## private
- private 封装 数据对象, 产生读写控制
- 封装的最重要功能是保持拓展性
- 提供接口时强调 反应数据速度 还是 数据占用内存空间 需要权衡

## non-member & non-friend  > member
- 愈多能够访问数据的方法, 越低的封装性, 越低的可拓展性和重用性, 导致后期维护成本飙升
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

# 5. 定义
## 尽可能延后变量定义式出现时间
- 不仅延后变量定义的时间到使用之前为止
- 应当尝试延后能给到初始值
- 循环中定义变量还是循环外定义变量需要看效果
    - 如果赋值操作成本低于构造和析构且注重效率 -> 循环外
    - 防止作用域污染 -> 循环内

## 少做转型
- 新式转型显眼 + 作用窄化 比旧式更容易维护
- 转型产生额外的代码其中多态转换较为特殊
```c++
Base *p = &derived;
//  Derived * => Base *p
//  会在 Derived *p 的基础上加上偏移量
//  不要自定义增加偏移量 除非对 对象在内存上的布局有假定
```

- 使用转型场景相当于进入微妙场景, 如下
```c++
class Derived : public Base {
    void func(){
        static<Base>(*this).ChangeFunc();
        //  实质上是在 Derived 对象上的 Base 成分副本上调用函数 产生错误
        Base::ChangeFunc()
    }
};
```

- `dynamic_cast<>()` : 对 base 指针或引用 执行所认定的 derived对象 的相关操作
    - 比较多次类相关信息, 运行较慢
    - 保存每种类型指针的容器 或 基类提供一个实现了的函数体为空的虚函数, 派生类根据需求覆盖
    - 避免 cascading dynamic cast (一堆if else 判断所有用到的派生类) : 难为护且运行慢

## 避免返回 handle 指向对象内部部分
- 成员变量的封装性最多等于返回引用函数的封装级别
- 数据成员存储于对象外, const 成员 返回 引用仍有可能改变该数据 (bitwise constness)
- 返回 handle 指向对象内部部分可能被调用者释放产生 dangling handles

## 异常安全
- 三种异常保证 : (整体的异常安全性有 木桶效应 )
    - 基本承诺 : 失败则保证数据结构未败坏但是当前状态未定义
    - 强烈保证 : 失败则保证恢复到原来状态
    - 无异常抛出 : 保证没有异常抛出 或者 抛出异常将是严重错误(主要决定于实现而非声明)
- 可用 copy & swap 强烈保证, 但还是会因为多个过程函数 或 无法恢复全局性数据而无法强烈保证

## inline
- inline 发生在编译期, 产生代码膨胀成本, 谨慎对模板, 构造函数和析构函数 inline, inline 无法调试
- 编译器会最终对 inline 进行取舍, 有时会因为需要在运行期间调用而不inline如通过函数指针调用或者调用virtual函数
- 使用的策略, 对于基本对象 getter 或 setter inline, 对于 80% 时间成本的代码通过 inline 优化

## 降低文件之间的编译依存
- `pimpl` : 通过指针指向内部类(impl), 通过指针访问, 存在额外的指针开销, 额外的动态内存分配和分配异常
- `interface_class` : 通过指针实现多态访问, 存在虚指针大小

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


## interface class
```c++
// interface_class.h
#include <iostream>
#include <string>
#include <memory>

class Person {
 public:
  static std::shared_ptr<Person> create(const std::string &name, 
                                        const std::string &birth_date, 
                                        const std::string &address);
  virtual ~Person();
  virtual std::string Name() const = 0;
  virtual std::string BirthDate() const = 0;
  virtual std::string Address() const = 0;
};

// interface_class.cc
#include "interface_class.h"

#include <memory>
#include <string>

class RealPerson: public Person {
 public:
  RealPerson(const std::string &name, 
             const std::string &birth_date,
             const std::string &address);
  virtual ~RealPerson();
  std::string Name() const override;
  std::string BirthDate() const override; 
  std::string Address() const override;
 private:
  std::string the_name_;
  std::string birth_date_;
  std::string the_address_;
};
RealPerson::RealPerson(const std::string &name, 
                       const std::string &birth_date,
                       const std::string &address) 
    : the_name_(name), birth_date_(birth_date), the_address_(address) { }
RealPerson::~RealPerson(){}
std::string RealPerson::Name() const {
  return the_name_;
}
std::string RealPerson::BirthDate() const {
  return birth_date_;
} 
std::string RealPerson::Address() const {
  return the_address_;
}
std::shared_ptr<Person> Person::create(const std::string &name, 
                                       const std::string &birth_date, 
                                       const std::string &address) {
  return std::shared_ptr<Person>(new RealPerson(name, birth_date, address)); 
}
Person::~Person(){ }
```

# 6. OOD
## public = is a
- public 继承 代表能够施行在基类对象上的操作也能施行派生类对象上
- 李氏替换原则

## 派生类名称遮掩
- 派生类中的同名函数或数据 覆盖掉所有 基类同名函数或数据
- 在同一访问控制符下 使用 `using base::func;` 可以实现与基类函数重载
```c++
class Base {
 public:
	void func(int a);
	void func(int a, int b);
};

class Derived : public Base {
 public:
	using Base::func;  //  1. 继承重载函数, 维护 is a 关系 
	void func(int a, int b);  // 与 func(int a) 重载, 覆盖掉基类相同函数

	inline void func(int a, int b) {  //  2. 或者写转交函数, 实现继承基类某个特定函数
		Base::func(a,b);
	}
};
```

## 类的接口继承和实现继承
- 纯虚函数 : 让派生类 接口继承
- 虚函数 : 让派生类 接口继承 和 缺省实现
- 普通成员函数 : 让派生类 接口继承 和 强制实现
- 权衡 : 8-2法则判断类是否能够虚函数效率成本(是否为虚函数), 函数的不变性是否凌驾于特异性(是否为普通函数)

## 替换 virtual 函数的设计模式
- NVI (Template Method) : virtual 实现 method , 基类普通成员函数实现 template
- Pointer Strategy
- Function Strategy
- 传统 Strategy

## 绝不重新定义继承而来的普通成员函数
- 重新定义则会出问题 ： 通过指针或引用调用会触发静态绑定产生行为不一致
- 在公有继承下, 李氏替换原则表明基类的普通成员函数具有不变性, 如果重新定义则违反 is a 的关系
- 其他继承下类似

## 绝不重新定义继承而来的默认实参
- 默认实参为了执行速度采取静态绑定 
- 可以使用 niv 模式, 用 template 统一派生类的默认实参

## is-implemented-in-terms-of
- 总概括就是复合关系 : 根据应用领域不同而改变
    - 应用域 : 有一个
    - 实现域 : 根据某物实现出

## private 继承
- 隐去接口, 使用其中的某些实现, 是一种 is-implemented-in-terms-of (可以通过复合替换)
    - 使用 base 类 的 protected 成员
    - 重新定义一个 或 多个virtual函数
- 但是存在一些问题, 比如
```c++
class Base {
 public:
  void virtual test() {
    ... 
  }
};

class Derived : private Base {  // 1. 继承 Base 时, Base 的定义可见, 存在编译依存
 private:
  void virtual test() override {   // 2. 即使 test 变为 private, Derived 的派生类仍然可以override 
    ...
  }
};

// 根据以上缺点, 实现 Derived 的内部类来解决
class Derived {
 private:
  class BaseD;
 public:
  void test() {    // non-vertual 解决 可能被 override 问题
    p_based_->test();
  }
 private:
  BaseD *p_based_;  // 解决编译依存
};

class Derived::BaseD : public BaseP {
  ...
};
```

- EBO (empty base optimization) : 
    - 空类 (独立非附属) 非空, 会插入一个char 或 对齐补齐
    - 继承的空类为空, 在继承的空类中加上调用对象, 类型别名, 枚举, 静态对象可以实现一种抽象

## MI

# 7. Template & GP











