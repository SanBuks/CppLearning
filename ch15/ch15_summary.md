# 第 十五 章 面对对象程序设计
### 1. 概述
#### OOP核心思想
- 数据抽象 : 封装实现接口与实现分离, 形成抽象数据类型 
- 继承 : 通过基类和派生类实现类的层次关系, 通过虚函数定义各自派生类的特殊操作 
- 动态绑定 : 根据对象的类型在运行时调用形式上相同但实质不同的虚函数, 各自的差异形成多态 

#### 派生类
- 派生类继承直接基类和间接基类的所有成员
- 对基类函数继承分为两种 : 直接继承的 和 用于覆盖的虚函数
```c++
class A; // 声明派生类不用声明派生列表
// 继承基类时派生类必须已经定义
class A final : public B{ // 派生类定义, 公有继承基类, 不能被继承
	virtual auto func()->int const override final; 
    // virtual只声明于类内, 除构造函数外非静态成员均可声明
	// final 禁止派生类覆盖
	A():B(1,2){}  // 必须调用基类的构造函数初始化基类部分的数据成员, 先B 后A
};
A a;
// 派生类到基类的类型转换
B &b=a; B *p=&a;
```
- 基类的静态成员 : 在派生类中只有唯一定义, 根据访问控制决定派生类是否可以调用
	- D::sfunc();
	- B::sfunc(); 
	- d.sfunc();

#### 虚函数 
- 动态绑定与静动态类型 :
	- 虚函数在派生类中隐式为虚函数, 根据指针或引用调用时会针对对象类型进行动态绑定
    - 静态类型在编译时已知, 动态类型表示内存中的对象类型,运行时才知
    - 虚函数默认实参遵循静态类型, 派生类所有默认实参一般要与基类相同
	- `baseP->Base::func();` 不进行动态绑定, 执行静态类型的虚函数
- 避免问题 : 
    - 覆盖虚函数的型参和返回类型必须与派生类一致, 除非返回父类的指针或引用(前提 转换可见)
    - 与父类同名不同参的虚函数会发生"隐藏错误", 即使隐藏仍然存在, 必要用override标识
    - 可以将基类的指针(包括智能指针)和引用绑定到派生类上, 但反过来不可以, 如果是安全的可以使用`static_cast`转换
    - 将派生类对象转换成基类对象时会调用基类的相关拷贝操作, 只能处理自己的成员, 切掉了派生类自己独有的成员

### 2. 访问控制
#### 访问说明符

| 基类      | public 继承 | protected 继承 | private 继承 |
| --------- | ----------- | -------------- | ------------ |
| public    | public      | protected      | private      |
| protected | protected   | protected      | private      |
| private   | private     | private        | private      |

- 继承方式不改变派生类和其友元对基类的可访问性, 改变派生类的派生类或用户对于基类的可访问性
- 派生类和其友元只能通过派生类对象访问派生类的基类成员

#### 转换(D2B)可见性
- 用户代码的可见性 : (只有public才可见)
```c++
#include <iostream>
class B{
public: virtual void test(){};
};

class Dpub : public B{
public: void test() override { std::cout<<"dpub"; } 
};
class Dpro : protected B{
public: void test() override { std::cout<<"dpro"; } 
};
class Dpri : private B{
public: void test() override { std::cout<<"dpri"; } 
};

int main(){
	Dpub dpub; Dpro dpro; Dpri dpri;
	B &bpub=dpub;  // public 继承成功
	B &bpro=dpro;  // protected 继承出错
	B &bpri=dpri;  // private 继承出错
	return 0;
}
```

- 直接派生类和友元的可见性 :  (继承方式不影响)
```c++
class B{
public: virtual void test(){};
};

class Dpub : public B{
public: void test() override { Dpub dpub; B &b=dpub; } 
};
class Dpro : protected B{
public: void test() override { Dpro dpro; B &b=dpro; } 
};
class Dpri : private B{
public: void test() override { Dpri dpri; B &b=dpri; } 
};

int main(){
	Dpub dpub; Dpro dpro; Dpri dpri;
	dpub.test();  // public直接继承 可见性存在
	dpro.test();  // protected直接继承 可见性存在
	dpri.test();  // private直接继承 可见性存在
	return 0;
}
```

- 间接派生类和友元的可见性 : (基类公有是否可见为标准)
```c++
#include <iostream>
class B{
public: virtual void test(){};
};

class Dpub : public B{ };
class Dpro : protected B{ };
class Dpri : private B{ };

class Ddpub : public Dpub{
public: void test() override { 
			Dpub dpub; B &bd=dpub; 
			Ddpub ddpub; B &bdd=ddpub;
		} 
};
class Ddpro : public Dpro{
public: void test() override { 
			Dpub dpub; B &bd=dpub; 
			Ddpub ddpub; B &bdd=ddpub;
		} 
};
class Ddpri : public Dpri{
public: void test() override { 
			Dpub dpub; B &bd=dpub; 
			Ddpub ddpub; B &bdd=ddpub;
		} 
};

int main(){
	Ddpub ddpub; Ddpro ddpro; Ddpri ddpri;
	// 派生类的访问控制对间接派生类的可见性有影响
	// 间接派生类如何继承不影响可见性(可以测试)
	ddpub.test(); // public -> public -> public 可见 
	ddpro.test(); // public -> protected -> protected 可见 
	ddpri.test(); // public -> private -> private 直接派生类和本身都不可见 
	return 0;
}
```

#### 其他规则
- 友元与继承 : F是B的友元则
    - F的派生类不是B的友元
    - F也不是B派生类的友元
    - F可以借助B派生类对象访问其B部分的成员 \*
- 在不同访问控制符下`using Base::objname;`可改变基类成对应的访问权限
- 默认继承保护级别 : 
    - class 默认private 控制 和 pirvate继承
    - struct 默认public 控制 和 public继承

#### 继承中类作用域
- 派生类作用域嵌套在基类中隐藏基类的同名成员不会发生重载
- 可以通过 `d.Base::mem`使用被隐藏的基类成员
- 查找过程 : 
	- 确定静态类型后在静态类型中查找, 不断到达顶端基类
	- 进行常规的类型检查及函数匹配
	- 根据是否是虚函数判断调用版本, 虚则动态绑定, 实则常规调用
```c++
class B{};
class A : public B{
    void test(){}
}
A a; B &b=a;
b.test() // 即使 b中含有test()函数成员 但是根据查找过程并非是虚函数, 无法调用
```

- 成员函数无论是否是虚函数都会发生重载, 对于覆盖虚函数重载时可以使用`using Base::funcname();`达到统一覆盖效果, 然后再对特定的函数进行覆盖

### 3. 继承中的构造与拷贝控制
#### 虚析构函数
- 基类析构必为虚, 合成也为虚
- 虚析构并不一定带来自定义的拷贝赋值
- 虚析构函数(合成)阻止合成移动操作

#### 拷贝控制与继承
- 拷贝控制从继承链顶向下依次调用, 析构操作从类往继承链顶依次销毁本类自己部分成员
- 合成删除的原因 : 
    - 基类拷贝控制删除 派生类对因拷贝控制删除
    ;- 基类有删除的析构函数 派生类中合成的默认和拷贝构造函数删除 
    - 基类有删除的析构函数或拷贝操作 派生类中合成拷贝操作删除
> 因此如果派生类需要移动操作基类中必须显示定义(default或自定义)

- 派生类相关函数写法
```c++
D (const D &d) : Base(d){} // 如果略去派生列表会发生"切掉"错误
D (D &&d) : Base(std::move(d)){}
D &operator=(const D&rhs){ Base::operator=(rhs); ... return *this; }
```

- 在构造函数或析构函数中调用虚函数以当前调用的类型为准, 否则类的未完成状态会产生错误

#### 继承构造函数
- 可用 `using Base::Base;`直接继承父类的构造函数生成形如`Derived(parms):Base(args)`
- 自己的数据成员会被默认初始化
- 不改变访问级别
- 不能指定但能继承 explicit 或 constexpr属性  
- 默认实参问题 : 
```c++
struct Base {
    Base(int a, int b, int c = 1, int d = 2, int e = 3) {}
};
struct Derived : Base {
    using Base::Base; //相当于
//Derived::Derived(int a, int b) : Base(a, b) {}
//Derived::Derived(int a, int b, int c) : Base(a, b, c) {}    
//Derived::Derived(int a, int b, int c, int d) : Base(a, b, c, d) {}
//Derived::Derived(int a, int b, int c, int d, int e) : Base(a, b, c, d, e) {} 

//如果 自己定义了Derived(int x, int y, int z) : Base(a, b, c) {} 则对应的构造函数不被继承
};
```

- 默认, 拷贝和移动构造函数不会被继承, 而是合成, 继承的构造函数不能视为自定义构造函数, 类仍会合成默认构造函数













