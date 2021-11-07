# 1. 拷贝构造, 拷贝赋值和析构
## 1.1 拷贝构造函数(cctor)
- 形式: 
```c++
// 1. 形式: 第一个参数必为自身类型引用(一般为const), 其余参数都有默认实参
Foo(const Foo &rhs, int other_arg1 = 10, ...);
// 1.1 错误一 : 拷贝构造函数存在隐式类型转化 必须非 explicit
explicit Foo(const Foo &rhs, int other_arg1 = 10, ...);
// 1.2 错误二 : 如果非引用会发生无限循环
Foo(const Foo rhs, int other_arg1 = 10, ...);

// 2. 使用方式:
string s2 = s1;     // 调用拷贝构造函数初始化
string s3 = "123";  // 隐式类类型转化后调用拷贝构造函数 (非 explicit)

// 3. 编译器 提供 拷贝移动构造函数 的优化 copy-elision, 直接转化成等价的构造函数
string test = string("123");  // 直接优化成
string test("123");
```

- 合成拷贝构造函数: 如果没有定义拷贝构造函数则会合成, 逐一将非 static 成员拷贝到新对象中
  - 数据类成员: 调用类成员的拷贝构造函数
  - 内置类型: 直接复制
  - 数组类型: 逐一将数组内元素拷贝到另一个数组
- 调用场景举例: 
  - 作为实参进行值传递
  - 非引用类型函数返回
  - 花括号列表初始化数组中元素或者聚合类
  - 容器 push, insert操作等

## 1.2 拷贝赋值运算符(=operator)
- 形式:
```c++
// 必须定义为成员函数
Foo &operator=(const Foo& rhs) {
  ... 
  // 尽量保持内置类型赋值运算符一致, 返回本身引用 *this
  return *this;
}
```

- 合成拷贝赋值运算符: 逐一将非static成员拷贝到新对象中

## 1.3 析构函数(dtor)
- 形式:
```c++
// 无参数, 无返回值, 唯一
~Foo() {
  // 1. 先执行函数体
  // 2. 手动执行收尾工作 (如 delete pointer)
  ...
  // 3. 最后按初始化顺序逆序销毁非 static 成员 (隐式, 调用其他类型析构函数)
} 
```

- 合成析构函数: 函数体为空, 自动销毁成员, 但是不能进行收尾工作
- 调用场景: 
  - 变量离开作用域调用
  - 对象销毁, 类成员调用
  - 容器或数组销毁, 元素调用
  - delete pointer 调用
  - 临时对象表达式结束时销毁 如 A( A("123") ); 括号内的临时对象拷贝后即销毁

# 2. 拷贝控制
## 2.1 基本概念
- 拷贝控制: cctor, =operator, dtor, mctor, m=operator 五个管理对象构造, 拷贝, 移动, 析构操作的函数
- 三五法则:  
  - dtor       -> 其他4项
  - cctor      -> 其他3项(除了析构函数)
  - =operator  -> 其他3项(除了析构函数)
  - mctor      -> 其他3项(除了析构函数)
  - m=operator -> 其他3项(除了析构函数)

## 2.2 管理拷贝控制
### default
- 显示要求合成的拷贝控制版本
- 内部默认内联, 可以内部仅声明外部加限定避免内联, default 直到编译器需要产生代码时需要
- 个人强烈推荐按此方法显示声明所有合成操作 (从某种程度上来说, delete 和 default 可以实现未声明即删除的效果)
### delete
- 定义为删除的函数, 必须第一次声明时限定
- 编译器编译函数调用时用到, 可以对任何函数使用
- 删除的析构函数:
  - 本质是阻止栈分配, 不可定义变量和临时变量, 包含成员的类变量
  - 虽然可以堆分配, 但是不可 delete 释放
### private
```c++
class NoCopyable {
 public:
  NoCopyable() = default;
  ~NoCopyable() = default;
  // 对于一般调用发生编译错误
 private:
  // 不实现, 对于友元会发生链接错误
  NoCopyable(const &NoCopyable rhs);           
  NoCopyable &operator=(const &NoCopyable rhs);
};
```

## 2.3 拷贝控制是删除的情况
### dctor
- T has a member of reference type without a default initializer.
- T has a non-const-default-constructible const member without a default member initializer.
- T has a member (without a default member initializer) (since C++11) which has a deleted default constructor, or its default constructor is ambiguous or inaccessible from this constructor.
- T has a direct or virtual base which has a deleted default constructor, or it is ambiguous or inaccessible from this constructor.
- T has a direct or virtual base which has a deleted destructor, or a destructor that is inaccessible from this constructor.
- T is a union with at least one variant member with non-trivial default constructor, and no variant member of T has a default member initializer.
- T is a non-union class with a variant member M with a non-trivial default constructor, and no variant member of the anonymous union containing M has a default member initializer.
- T is a union and all of its variant members are const.
### cctor 
- T has non-static data members that cannot be copied (have deleted, inaccessible, or ambiguous copy constructors);
- T has direct or virtual base class that cannot be copied (has deleted, inaccessible, or ambiguous copy constructors);
- T has direct or virtual base class with a deleted or inaccessible destructor;
- T is a union-like class and has a variant member with non-trivial copy constructor;
- T has a data member of rvalue reference type;
- T has a user-defined move constructor or move assignment operator (this condition only causes the implicitly-declared, not the defaulted, copy constructor to be deleted).
### =operator
- T has a user-declared move constructor;
- T has a user-declared move assignment operator.
- T has a non-static data member of non-class type (or array thereof) that is const;
- T has a non-static data member of a reference type;
- T has a non-static data member or a direct or virtual base class that cannot be copy-assigned (overload resolution for the copy assignment fails, or selects a deleted or inaccessible function);
- T is a union-like class, and has a variant member whose corresponding assignment operator is non-trivial.
### mctor
- T has non-static data members that cannot be moved (have deleted, inaccessible, or ambiguous move constructors);
- T has direct or virtual base class that cannot be moved (has deleted, inaccessible, or ambiguous move constructors);
- T has direct or virtual base class with a deleted or inaccessible destructor;
- T is a union-like class and has a variant member with non-trivial move constructor.
### m=operator
- T has a non-static data member that is const;
- T has a non-static data member of a reference type;
- T has a non-static data member that cannot be move-assigned (has deleted, inaccessible, or ambiguous move assignment operator);
- T has direct or virtual base class that cannot be move-assigned (has deleted, inaccessible, or ambiguous move assignment operator).
### dtor
- T has a non-static data member that cannot be destructed (has deleted or inaccessible destructor)
- T has direct or virtual base class that cannot be destructed (has deleted or inaccessible destructors)
- T is a union and has a variant member with non-trivial destructor.
- The implicitly-declared destructor is virtual (because the base class has a virtual destructor) and the lookup for the deallocation function (operator delete()) results in a call to ambiguous, deleted, or inaccessible function.

## 2.4 "值类" 和 "指针类"
- 行为像值的类: 拷贝赋值运算符注意先拷贝内容再释放来解决和异常安全的问题
- 行为像指针的类: 使用 share_ptr 或 自定义引用计数
```c++
// 表现像值一样类
// 1. 拷贝构造写法
HasPtrValue(const HasPtrValue &rhs) : ps(new string(*rhs.ps)) {}
// 2. 拷贝赋值运算符写法 
HasPtrValue &operator=(const HasPtrValue &rhs) {
  auto newp = new string(*rhs.ps);  // 首先复制一份指针所指内容
  delete ps;                        // 防止自身赋值被意外释放掉
  ps = newp;                        // 复制指针
  i = rhs.i;                        // 直接复制非动态分配的成员
  return *this;
}
// 3. 析构函数写法:
HasPtrValueValue() { delete ps; }

// 表现像指针一样类 (引用计数) 
// 1. 拷贝构造写法:
HasPtrPointer(const HasPtrPointer &rhs) : ps(rhs.ps), use(rhs.use) { ++*use; }
// 2. 拷贝赋值运算符写法:
HasPtrPointer &operator=(const HasPtrPointer &rhs) {
  ++*rhs.use;                       // 应对自处理, 防止自身复制
  if (--*use == 0) {                // 左侧对象引用计数减一 为零则释放
    delete ps;
    delete use;
  }
  ps = rhs.ps;                      // 复制指针
  use = rhs.use;                    // 复制引用计数指针 (已经增加计数)
  return *this;
}
// 3. 析构函数引用计数使用写法:
HasPtrPointerPointer() {            // 析构函数注意只有在引用计数为零后才真正释放
  if (--*use == 0) {
    delete ps;
    delete use;
  }
}
```

## 2.5 交换操作
### swap 实质
```c++
A temp = v1;  // 拷贝构造函数 
v1 = v2;      // 拷贝赋值运算符
v2 = temp;    // 拷贝赋值运算符 
// 对于 值类, 总共成本为 创建一个临时对象, v1 被拷贝 1 次, v2 被拷贝 1 次
// 可以对栈中的对象 通过 swap 进行优化
```

### 自定义 swap
```c++
// swap 的重载问题
class A {
  friend void swap(A &lhs, A &rhs);
  string ps;
  int i;
};

inline void swap(A &lhs, A &rhs) {
  using std::swap;       // 使 std::swap 可见, 但是依然不会覆盖 自定义的 swap 函数
  swap(lhs.ps, rhs.ps);  // 标准库模板 与 非模板 swap 发生重载 优先调用非模板函数
  swap(lhs.i, rhs.i);    // 调用函数时, 除了在当前作用域中寻找函数, 也会在型参(类类型, 类类型指针 或 引用) 类型的所属命名空间中寻找
}
```

### copy-swap 保证异常安全
```c++
A& A::operator=(A rhs) {  // 拷贝构造 rhs 作为一个副本 如果发生错误则不会进入函数体 且 处理了自赋值
  swap(*this, rhs);       // 交换数据成员
  return *this;           // 返回后临时对象 rhs 自动销毁
}
```

# 3. 两个实例
## 3.1 Message
- 使用 raw pointer 表示 Folder 多对多 Message 独立关系
- 考略到 OOM 的异常安全性
- 对于表示关系的一对容器的事务性操作
## 3.2 StrVec
- allocator 使用方式
- 倍增策略

# 4. 移动语义
## 4.1 值类别
> 参见 "CppCon 2019:Ben Saks “Back to Basics: Understanding Value Categories” 详细介绍

- value category 是 \[编译器] 产生代码所需要的 \[表达式] 属性, 编译时已确定, 是 \[面向编译器] 而非 \[面向用户] 的语言特性
- value category 可以分为两个主要方面: "identity" 和 "value can be stolen": 
  - 左值, 表达式明确指定某个对象(对象即是一组有意义的内存), 如 "xyz" 是左值存放在静态内存
  - 右值, 非左值, 表达式不指定某个对象或该对象的内存不存在或无意义, 如临时变量, 虽然可能占据内存, 但是即刻销毁无法求其地址, 如 枚举, x+y, 2
```c++
// 1) 左右值的概念来自 C , 左值和右值与赋值相关, 放在左边的为左值, 放在右边的为右值
int a = 3;  // a 左值, 3 右值 (字面值)
int b = a;  // b 左值, a 右值 (放在右边的 a 发生了 左值 -> 右值转换)

// 2) 在概念上, 左值占有可求内存, 右值没有内存或者说内存不可求(因为即刻消失)
//    在实现上, 右值也可能占据内存, 举例如下 
//    2.1) x + y 的 int 型临时值会存放栈寄存器中, 这个寄存器不可求地址但是任然会占据内存
//    2.2) auto x = Func().y; 此时 Func 函数返回的临时值虽然是右值, 但是为了调用成员 y 需要在临时对象的地址做偏移, 所以必须占据内存
//    2.3) const string &a = string("123"); const type & 的引入给让 string("123") 的生命周期延长了

// 3) 根据可能占据内存的右值, 这里做出进一步分类 将右值分为 消亡值 和 纯右值, 将 消亡值 和 左值 统称为 泛左值
//    3.1) 纯右值, 不占据内存, 资源不可重新使用
//    3.2) 消亡值, 占据内存, 通常临近生命周期尾端, 因此可以重新使用资源(比如 移动)
auto x = Func().y;                // Func()        纯右值 -> 消亡值 发生 temporary materialization
string &&a = string("123");       // string("123") 纯右值 -> 消亡值 发生 temporary materialization
const string &a = string("123");  // string("123") 纯右值 -> const 消亡值 发生 temporary materialization
int &&y = std::move(x);           // x             左值 -> 消亡值, 注意, 对 y 进行操作后, 对 x 作为对象的内容可能被窃取

// 4) 左值引用 和 右值引用的区别
int a = 3;                        // a 是一个变量, 是左值
int &b = a;                       // b 是一个左值引用, 本身是左值
int &&c = 3;                      // c 是一个右值引用, 本身是左值, 值的来源 3 从 纯右值 -> 消亡值
const int &d = 3;                 // d 是一个const int & 引用, 本身是左值, 值得来源 3 从 纯右值 -> 消亡值
int &&e = c;                      // error, c 必须是左值类别
```

## 4.2 移动拷贝控制
### 移动拷贝构造
```c++
// 1) 资源移动一般不会分配内存不会发生异常, 定义和声明中 指定 noexcept, 防止为了异常安全而只调用拷贝构造
// 2) 型参非 const, 因为右值被 '窃取' 数据, 一定会发生状态改变
A(A &&a) noexcept : p1(a.p1), p2(a.p2) { 
// 3) 资源移动后需要将型参置于能够被析构或有效状态, 能被重新赋值, 能进行操作(不以值为假设)
  a.p1 = a.p2 = nullptr; 
}
```

### 移动赋值构造
```c++
A& operator=(A &&rhs) noexcept { 
  // 需要检查自赋值情况, 防止使用 std::move 产生同源现象
  if (this != &rhs) {
    ...
  } 
  return *this;
}
```

## 4.3 合成的移动控制
- 如果类自定义了任何一个拷贝控制, 则不会合成移动控制
- 如果没有定义任何一个拷贝控制, 且每个非static数据成员都可移动则会合成相应的移动控制
- 移动控制永远不会隐式定义为删除, 除非显示声明为 default 且数据成员不能被移动则会定义为删除
- 如果定义了移动控制, 没有定义拷贝控制, 则拷贝控制会被定义为删除

## 4.4 移动迭代器
- 该迭代器解引用产生右值
- 通过 `make_move_iterator(it)` 转换为移动迭代器

## 4.5 引用限定符
```c++
// 对于右值进行了赋值, 为了限制该行为在自定义类中出现可以通过引用限定符来解决
// 引用限定符 规定 this 所指对象是右值还是左值, 与 const 类似会发生重载
str1 + str2 = "123";
A& operator=(const A &) &;  // 限制只有左值对象可以使用赋值运算符
A func() const &;           // const 出现在限定符之前, 且限定符 和 const 类似不能修饰 static 成员函数
A func() cosnt &&;          // 引用限定符规定 同名且同参数类型的函数需要都加上引用限定
```