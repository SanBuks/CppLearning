# 1. 概述
## 1.1 OOP核心思想
- 数据抽象(封装): 接口与实现分离, 形成抽象数据类型(类, 访问权限)
- 继承: 派生类复用基类的成员, 实现层次关系模型
- 多态: 指针和引用的静态和动态类型不一致, 运行时根据实际类型动态绑定为各自虚函数, 达到同一调用形式多种调用状态 

## 1.2 基类与派生类
```c++
// 1. 基类
class B {
 public:
  // 1.1 基类必定义虚析构函数, 虚函数在派生类中隐式为虚函数 
  //     且派生类析构函数默认为虚函数
  virtual ~B();
  // 1.2 基类的静态成员在整个继承体系中唯一存在
  static int s;
 protected:
  // 1.3 protected 表明 派生类及派生类友元可以通过派生类对象(sneaky problem)访问, 其他用户不可访问
  int a;
 ...
};

// 2. 派生类
// 2.1 声明派生类不用声明派生列表, 派生类不能是自己的派生类
class A;
// 2.2 类派生列表中基类必须已经定义
// 2.3 final 规定 A 不可以被继承
class A final : public B {
  // 2.4 virtual 只声明于类内, 除构造函数外非静态成员均可声明
  // 2.5 override 表明 覆盖基类的虚函数, final 表示禁止派生类覆盖
  virtual auto func()->int const override final;
  
  // 2.6 必须调用基类的构造函数初始化基类部分的数据成员, 先 B 后 A
  A() : B(1,2) {}
};

// 3. 动态绑定
A a;
// 3.1 派生类到基类的类型转换, 基类到派生类转换需要用 dynamic_cast
B &b=a;
B *p=&a;
// 3.2 根据实际类型调用相应的虚函数
b->func();
p.func();
// 3.3 slice down 问题, 拷贝没有虚函数, 会调用基类的相关拷贝操作, 忽略派生类部分
A a_temp;
B slice_down = a_temp;
```

## 1.3 关于静态类型和动态类型
- 静态类型: 变量声明时的类型或表达式生成的类型, 编译时已知
- 动态类型: 变量和表达式所表示内存中的对象类型, 运行时才知
- 动态绑定本质: 基类的指针或引用的静态和动态类型不一致, 其他类型均一致
- 回避动态绑定: `baseP->Base::func()`
- 覆盖的要求: 派生类所有默认实参和参数数量类型必须与基类相同, 防止隐藏的错误, 必要用override标识

# 2. 访问控制
## 2.1 访问说明符

| 基类      | public 继承 | protected 继承 | private 继承 |
| --------- | ----------- | -------------- | ------------ |
| public    | public      | protected      | private      |
| protected | protected   | protected      | private      |
| private   | private     | private        | private      |

- 继承方式不改变派生类和其友元对基类的可访问性, 改变派生类的派生类或用户对于基类的可访问性
- 派生类和其友元只能通过派生类对象访问派生类的基类成员(sneaky problem)
- class  默认 private 控制 和 private 继承
- struct 默认 public  控制 和 public 继承
- 在不同访问控制符下 `using Base::objname;` 可改变基类成对应的访问权限

## 2.2 派生类向基类的可转换性
> 一言以蔽之, 基类的 public 部分可见即可转换

### 用户代码的可转换性
```c++
class B {
 public:
  virtual void test() {};
  virtual ~B() = default;
};

class Dpub : public B {
 public:
  void test() override { std::cout << "dpub"; }
};
class Dpro : protected B {
 public:
  void test() override { std::cout << "dpro"; }
};
class Dpri : private B {
 public:
  void test() override { std::cout << "dpri"; }
};

int main() {
  Dpub dpub; Dpro dpro; Dpri dpri;
  B &bpub = dpub;  // public    继承成功
  B &bpro = dpro;  // protected 继承出错
  B &bpri = dpri;  // private   继承出错
  return 0;
}
```

### 直接派生类和友元的可见性(继承方式不影响)
```c++
class B {
 public:
  virtual void test() {};
  virtual ~B() = default;
};

class Dpub : public B {
 public:
  void test() override {
    Dpub dpub;
    B &b = dpub;
  }
};
class Dpro : protected B {
 public:
  void test() override {
    Dpro dpro;
    B &b = dpro;
  }
};
class Dpri : private B {
 public:
  void test() override {
    Dpri dpri;
    B &b = dpri;
  }
};

int main() {
  Dpub dpub; Dpro dpro; Dpri dpri;
  dpub.test();  // public    直接继承 可转换
  dpro.test();  // protected 直接继承 可转换
  dpri.test();  // private   直接继承 可转换
  return 0;
}
```

### 间接派生类和友元的可转换性
```c++
class B {
 public:
  virtual void test() {}
  virtual ~B() = default;
};

class Dpub : public    B {};
class Dpro : protected B {};
class Dpri : private   B {};

class Ddpub : public Dpub {
 public:
  void test() override {
    Ddpub ddpub;
    B &b = ddpub;
  }
};
class Ddpro : public Dpro {
 public:
  void test() override {
    Ddpro ddpro;
    B &b = ddpro;
  }
};
class Ddpri : public Dpri {
 public:
  void test() override {
    Ddpri ddpri;
    B &b = ddpri;
  }
};

int main() {
  Ddpub ddpub;
  Ddpro ddpro;
  Ddpri ddpri;
  // 派生类的访问控制对间接派生类的可见性有影响
  // 间接派生类如何继承不影响可见性
  ddpub.test();  // public -> public -> public       可见
  ddpro.test();  // public -> protected -> protected 可见
  ddpri.test();  // public -> private -> private     直接派生类和本身都不可见
  return 0;
}
```

## 2.3 友元与继承
- C 是 B 的友元: C 的派生类不是 B 的友元
- F 是 B 的友元: F 不是 B 派生类的友元
- F 是 B 的友元: F 可以借助 B 派生类对象访问其 B 部分的成员

## 2.4 继承中类作用域
- 派生类作用域嵌套在基类中, 派生类隐藏基类的同名成员(即使参数列表不同)不会发生重载
- 调用函数查找过程 :
  - 确定静态类型后在静态类型中查找候选函数, 不断到达顶端基类
  - 进行常规的类型检查及函数匹配
  - 根据是否是虚函数判断调用版本, 虚则动态绑定, 实则常规调用
```c++
class B { public: virtual ~B() = default; };
class A : public B { virtual void test() {} }
A a; B &b=a;
b.test();   // 即使 b中含有test()函数成员 但是根据查找过程并非是虚函数, 无法调用
```

- 可以通过 `d.Base::mem` 使用被隐藏的基类成员
- 需要对基类的函数进行重载时可以通过 `using Base::funcname();` 使基类可见, 然后再对特定的函数进行覆盖

## 2.5 抽象类
```c++
// 声明纯虚函数的类为抽象类, 抽象类不可创建对象
class AbstractClass {
 public:
  // 纯虚函数形如 =0 必须只声明在类中, 函数体可以定义在类外
  // 纯虚函数一定要被派生类覆盖, 抽象类负责定义接口
  virtual void test() const = 0;
  // 抽象类的派生类仍然需要调用其构造函数
  virtual ~AbstractClass();
};
```

# 3. 继承中的构造与拷贝控制
## 3.1 虚析构函数
- 基类析构必为虚函数, 继承的派生类的析构函数也为虚函数, delete 动态绑定的指针所指对象没有虚析构函数则未定义
- 虚析构并不一定带来自定义的拷贝赋值
- 虚析构函数阻止合成移动操作, 所以派生类需要移动操作基类中必须显示定义

## 3.2 拷贝控制与继承
- 拷贝控制调用顺序: 继承链自顶向下依次调用
- 析构控制调用顺序: 继承链自低向下依次调用
- 合成删除的原因: 见 ch13 拷贝控制是删除的情况
- 构造或析构函数中调用虚函数以当前调用的类型为准(以函数所属的静态类型为准)
- 派生类相关函数写法:
```c++
D(const D &d) : Base(d) {}  // 如果略去派生列表会发生 "切掉" 错误
D(D &&d) : Base(std::move(d)) {}
D &operator=(const D &rhs) { 
  Base::operator=(rhs); 
  ... 
  return *this; 
}
```

## 3.3 继承构造函数
- 自己的数据成员会被默认初始化, 一般用于没有自己数据成员的情况
- 不改变访问级别, 不能指定但能继承 explicit 或 constexpr 属性
- 默认实参问题:
```c++
struct Base {
  Base(int a, int b, int c = 1, int d = 2, int e = 3) {}
};
struct Derived : Base {
  using Base::Base;
//  相当于生成构造函数为 (含有默认实参的个数逐个递减)
//  Derived::Derived(int a, int b) : Base(a, b) {}
//  Derived::Derived(int a, int b, int c) : Base(a, b, c) {}
//  Derived::Derived(int a, int b, int c, int d) : Base(a, b, c, d) {}
//  Derived::Derived(int a, int b, int c, int d, int e) : Base(a, b, c, d, e) {}

//  例外:
//  1. 默认, 拷贝和移动构造函数不会被继承, 派生类会自己合成
//  2. 如果 自己定义了 Derived(int x, int y, int z);  则对应的相同形参列表的构造函数不会被继承
//  3. 继承的构造函数不能视为自定义构造函数, 类仍会合成默认构造函数
};
```

# 4. 容器实现多态
- 容器中一般通过存放基类的(智能)指针实现多态
- 为了调用简洁性一般实现类的虚函数 clone
```c++
virtual Quote *clone() const & { 
  return new Quote(*this); 
}
virtual Quote *clone() const && { 
  return new Quote(std::move(*this)); 
}

AddItem(const Quote &sale) {
  insert(shared_ptr<Quote>(sale.clone())); 
} 
AddItem(Quote &&sale) { 
  insert(shared_ptr<Quote>(std::move(sale).clone())); 
}
```
