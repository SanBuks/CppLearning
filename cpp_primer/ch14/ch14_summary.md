# 1. 重载运算符
## 1.1 基本概念
- 重载运算符: 名字是运算符的特殊函数 如 `A &operator+(const A &a, const A &b);` 
- 重载运算符限制: 除 operator() 外不能有默认实参, 形参类型不能都是基本类型
- 根据参数数量分为一元和二元运算符(调用运算符除外), 如果是成员函数则数量减一(默认第一个绑定为自身)
```c++
d1+d2;             // 非成员函数调用方法
operator+(d1,d2);  // 同上

d1+=d2;            // 调用成员函数 符合赋值一般是成员函数
d1.operator+=(d2); // 同上
```

## 1.2 重载建议
- 不能重载: `::`, `.*`, `.`, `? :`, 新的运算符, 内置类型运算符
- 不应重载: `&&`, `||`, `,` (求值顺序无法保留), `&`(作用于类存在特殊含义)
- 成员函数: `=`, `[]`, `()`, `->`, `复合赋值`, `自增自减`, `解引用` 
- 一般函数: 算术运算符, 判断相等运算符, 关系运算符, 位运算符, 包含混合, 对称的关系
- 保留语义特性: 原优先级用法, 原返回值类型, 操作语义

# 2. 一般重载运算符
## 2.1 输入和输出运算符
- 要求: 包含标准流对象, 所以重载输入输出都为非成员函数
- 输出: 需要减少格式控制给用户空间
- 输入: 需要在一次输入完成后检查流的状态, 发生错误则需要保证异常安全, 同时也可以通过设置流的标识表示格式对错
```c++
class SalesData {
  friend std::istream &operator>>(std::istream &is, SalesData &rhs);        // 输出重载
  friend std::ostream &operator<<(std::ostream &os, const SalesData &rhs);  // 输入重载
};
```

## 2.2 算术运算符
- 非成员函数, 注意委托赋值运算符
- 参数大都为常量引用

### 加法减法
```c++
SalesData operator+(const SalesData &lhs, const SalesData &rhs) {
  SalesData sum = lhs;  // 拷贝构造
  sum += rhs;           // 委托赋值运算符
  return sum;           // 值返回
}

SalesData &SalesData::operator+=(const SalesData &rhs) {
  units_sold_ += rhs.units_sold_;
  revenue_ += rhs.revenue_;
  return *this;
}
```

### 判等比较
```c++
// 非成员函数, 一般同时定义 != 和 == 且委托其中一个
bool operator==(const SalesData &lhs, const SalesData &rhs) {
  return lhs.book_no_ == rhs.book_no_ &&
         lhs.units_sold_ == rhs.units_sold_ &&
         lhs.revenue_ == rhs.revenue_;
}
bool operator!=(const SalesData &lhs, const SalesData &rhs) {
  return !(lhs == rhs);
}
// < 关系一定要有实际意义, 当与 == 不冲突时才可以重载
bool operator<(const SalesData &lhs, const SalesData &rhs);
```

### 赋值
```c++
StrVec &StrVec::operator=(std::initializer_list<std::string> il) {
  using std::swap;
  if (Size() == il.size() && std::equal(elements_, first_free_, il.begin())) {
    return *this;
  }
  // 委托构造, 保证异常安全
  StrVec temp(il);
  swap(*this, temp);
  return *this;
}
```

### 下标访问
```c++
// 必须是成员函数, 通常会定义两个版本, 返回常量引用和返回普通引用
std::string &operator[](size_t n){ return elements[n]; }
const std::string &operator[](size_t n){ return elements[n]; }
```

### 递增递减
```c++
// 成员函数, 前置返回引用, 后置返回值 
StrBlobPtr &StrBlobPtr::operator++() {
  // 保证异常安全, 先检测改变后的状态
  RankType modified_rank = curr_ + 1;
  Check(modified_rank, StrBlobPtrError::kIncrefPastEnd);

  ++curr_;
  return *this;
}
StrBlobPtr StrBlobPtr::operator++(int) & {
  auto ret = *this;
  this->operator++();
  return ret;
}
// p.operator++(0);  // 显示调用后置运算符
// p.operator++();   // 显示调用前置运算符 
```

### 成员访问
```c++
// 1. 必须是成员函数, 其中箭头运算符保留成员访问的含义
//   1) p->mem 内置指针则等价于 (*pointer).mem;
//   2) p->mem 等价于 pointer.operator->()->mem
//      返回值为指针则同上, 
//      如果是对象则继续第二步一致递归到结算或错误
std::string & operator*() const {
    auto def=check(curr, "deref past end");
    return (*def)[curr];
}
std::string * operator->() const {
    return & this->operator*();
}
// 2. operator->() 委托 operator*()
```

### 调用运算
```c++
// 成员函数, 定义了调用运算符的类称作调用对象, 可以像函数一样地调用它
// lambda 表达式是函数对象, 产生相应的类, 类中含有相应的数据成员对应捕获的类型值
int a = 3, b = 4;
auto it = [a, &b](int p) ->std::ostream& { std::cout << a + b + p; return std::cout; };
// 等价为
class Lambda {
  // 不含默认构造函数, 赋值运算符
  // 是否含有拷贝/移动构造函数 视 数据成员而定
  Lambda(int a, int &b) : a_(a), b_(b) {}
  std::ostream &operator(int p) const {  // lambda 非 mutable
     std::cout << a + b + p;
     return std::cout;
  }
 private:
  int a_;
  int &b_;
};
```

# 3. 函数对象与可调用对象
## 3.1 函数对象
```c++
// 重载了调用运算符的类对象可以看作函数对象
// 标准库通过函数对象提供内置的运算符部分未能提供的功能, 同时方便调用
#include <functional>

std::string a;
std::string b;
std::string *pa = &a;
std::string *pb = &b;

std::less<std::string *> le;  // 补充未定义的操作
std::cout << le(pa, pb);      // 按照内存地址比较
std::cout << (pa < pb);       // 未定义
```

## 3.2 可调用对象
- 可调用对象: 函数, 函数指针, lambda表达式, bind创建对象, 函数对象
- 调用形式(call signature): 返回类型, 型参, 用 `return_type(type1, type2)` 表示
- 函数表: 可以简单用 `map<string, xxx>` 形式构成, 但是无法统一所有可调用对象
- function 类型: 统一可调用对象的模板, 解决多种调用对象类型不一的问题
```c++
// 类型别名
std::function<int(int,int)>::result_type result_type;
std::function<int(int,int)>::first_argument_type param_type_1;
std::function<int(int,int)>::second_argument_type param_type_2;
// 初始化
std::function<int(int,int)> f1(TestInt);  
std::function<int(int,int)> f2(nullptr);
// 判断是否为空指针
if (f1) {
  // 调用
  std::cout << f1(1, 2) << std::endl;
}
// 赋值
f2 = [](int, int) -> int { return 1; };
if (f2) {
  std::cout << f2(1, 2) << std::endl;
}

// 存放重载函数名字时会发生命名冲突, 可以通过使用 指针 或 lambda 解决
map<string, function<int(int, int)>> mp;
mp.insert({"add", add});  // add 函数存在重载版本会发生歧义
```

# 4. 类型转换与重载
## 4.1 用户定义的类型转换
- 类类型转换 :
  - 转换构造函数: arg -> class_obj
  - 类型转换运算符: class_obj -> type
- 标准(内置)类型转换与类类型转换: 用户定义类型转换可以发生在内置类型转换之前或之后, 并一起使用
```c++
class SmallInt {
  SmallInt(int a);       // 定义了 int      -> SmallInt
  operator int() const;  // 定义了 SmallInt -> int
  explicit B() const;    // 定义显示类型转换, 调用 static_cast<int>(si) 进行转换
                         // 显示类型转换有一个例外, 表达式被用于条件会隐式调用类型转换
};
SmallInt si = 3.14;      // 3.14 -> int -> SmallInt
si + 3.14;               // si   -> int -> double
```

## 4.2 类型转换运算符
```c++
operator type() const { ... return typeA; }
// 1. 成员函数, 无参, 无显示返回类型, 隐式返回类型为 type
// 2. type 不可为数组类型, 函数类型
// 3. 一般不改变数据成员, 是 const 成员函数
// 4. typeA 类型必须符合type
```

## 4.3 避免歧义
### 相同路经类型转换带来的歧义
```c++
class A{};           // 定义了 B->A 的转换构造函数
class B{};           // 定义了 B->A 的类型转换运算符
A ff(const A &b); 
B b;
ff(b);               // 发生歧义, 不要在 两个类之间定义重复的类型转换
ff(A(B));            // 显示调用转换构造函数
ff(b.operator A());  // 显示调用转换运算符
```

### 标准类型转换带来的歧义
```c++
struct Integral {
  int a = 10;
  // 不要定义 多个转换目标为算术类型的类型转换, 因为算术类型之间存在标准类型转换会发生歧义
  // 或者广泛的说, 多个转换目标之间没有类似的标准类型转换
  operator double() const { return 10; }
  operator short() const  { return 10; }
  // 同理, 不要当以多个转换源为算术类型转换
  Integral(double a);
  Integral(short a);
};

void f1(int ld)       { std::cout<<ld<<std::endl; }
void f2(long long ld) { std::cout<<ld<<std::endl; }

int main() {
  Integral ci;
  f1(ci);       // ci -> short -> 整型提升为 int 优于 ci -> double -> int
  f2(ci);       // ci -> short -> long long 与 ci -> short -> long long 产生歧义
  return 0;
}
```

### 重载函数与转换构造函数带来歧义
```c++
class A {};     // 定义了 int -> A
class B {};     // 定义了 int -> B
void ff(const A &);
void ff(const B &);
ff(10);         // 发生 int 转换的重载歧义
                // 避免重载的参数存在同一转换源类型
                
class A{};      // 定义了 double -> A
class B{};      // 定义了 int -> B
void ff(const A &);
void ff(const B &);
ff(10); 
// 参数 10 需要转换, 寻找匹配过程中定级为最后一级即自定义的类型转化
// 其中 int -> B 优先级高与 int -> double -> A
```

### 成员函数和非成员函数重载带来歧义
```c++
class A {};     // 定义了 int -> A
                // 定义了 A   -> int
                // 避免转换源和转换目标相同
friend A operator+(const A &lhs, const A &rhs);
A a3 = a1 + 0;  // 发生歧义
```