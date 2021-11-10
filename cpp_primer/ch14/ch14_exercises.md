# 14.11 输入流的格式安全
> 下面的 Sales_data 输入运算符存在错误吗？如果有，请指出来。对于这个输入运算符如果仍然给定上个练习的输入将会发生什么情况？
```c++
istream& operator>>(istream& in, Sales_data& s)
{
  double price;
  in >> s.bookNo >> s.units_sold >> price;
  s.revence = s.units_sold * price;
  return in;  // 未检测输入流是否发生错误, 发生错误后没有对s进行恢复
}
```

# 14.42 函数对象
> 使用标准库函数对象及适配器定义一条表达式，令其
> (a) 统计大于1024的值有多少个。
> (b) 找到第一个不等于pooh的字符串。
> (c) 将所有的值乘以2。
```c++
std::cout<<std::count_if(vec.begin(), vec.end(), 
  std::bind(std::greater<int>(), _1, 1024));
std::cout<<*std::find_if(vec.begin(), vec.end(),
  std::bind(std::not_equal_to<std::string>(), _1, "pooh"));
std::transform(vec.begin(), vec.end(), 
  vec.begin(), std::bind(std::multiplies<int>(), _1, 2));
```

# 14.43 函数对象
> 使用标准库函数对象判断一个给定的int值是否能被 int 容器中的所有元素整除。
```c++
int main() {
  std::vector<int> vec{2, 1, 3};
  int number;
  std::cin >> number;
  if (vec.end() == std::find_if(vec.begin(), vec.end(),
                                std::bind(std::modulus<int>(), number, _1))) {
    // 发现不到存在 余数的情况 -> 全部都可以被整除
    std::cout << "Yes!\n";
  } else {
    std::cout << "No!\n";
  }
  return 0;
}
```

# 14.44 函数对象
> 编写一个简单的桌面计算器使其能处理二元运算。
```c++
int add(const int a1, const int a2) { return a1 + a2; }
auto minus = [](const int a1, const int a2) -> int { return a1 - a2; };
std::multiplies<int> multi;
class Divide {
 public:
  int operator()(const int a1, const int a2) {
    if (!a2) {
      throw std::runtime_error("class Divide operator() can't divide 0");
    }
    return a1 / a2;
  }
};

int main() {
  std::map<std::string, std::function<int(const int, const int)>> mp;

  mp.insert({"+", add});
  mp.insert({"-", ::minus});  // 与 std::minus 冲突
  mp.insert({"*", multi});
  mp.insert({"/", Divide()});

  std::cout << mp["+"](1, 5) << std::endl;
  std::cout << mp["-"](1, 5) << std::endl;
  std::cout << mp["*"](1, 5) << std::endl;
  std::cout << mp["/"](1, 9) << std::endl;

  return 0;
}
```

# 14.47 类型转换
> 说明下面这两个类型转换运算符的区别。
```c++
struct Integral {
  int a = 10;
  // 只会对 类对象是否是 const 进行重载
  operator const int() { std::cout<<"#1 "<<std::endl; return a; }
  operator int() const { std::cout<<"#2 "<<std::endl; return a; }
};
int main(){
  // 在需要内置类型时会隐式调用转换运算符, 表面上 #1 #2都没有型参但是根据 this 是否是const会发生参数匹配的优先级比较
  const Integral ci;
  std::cout << ci << std::endl; // #2
  Integral i;
  std::cout << i << std::endl;  // #1
  return 0;
}
```

# 14.50 类型转换
> 在初始化 ex1 和 ex2 的过程中，可能用到哪些类类型的转换序列呢？说明初始化是否正确并解释原因。
```c++
struct LongDouble {
  LongDouble(double = 0.0);
  operator double();
  operator float();
};
LongDouble ldObj;
int ex1 = ldObj;    // 发生歧义 double 和 float 转换为 int 优先级相同
float ex2 = ldObj;  // 调用 float() 进行转换
```

# 14.51 类型转换
> 在调用 calc 的过程中，可能用到哪些类型转换序列呢？说明最佳可行函数是如何被选出来的。
```c++
void calc(int);        // #4
void calc(LongDouble); // #5
double dval;
calc(dval);            // 调用了哪个calc？ 

// 调用 clac(int)
```

1. 精确匹配 : 
  - 类型相同
  - 数组名函数名转换成对应指针
  - `const int -> int` 或 `int -> const int`
2. `type [&/*] -> const type [&/*]` (因此存在底层const不同的调用区别)
3. 算数类型提升(函数在匹配前,没有精确匹配的实参会进行类型提升)
4. 算术类型转换(所有的算数类型转换都一样) 或 指针转换 : 
  - `0/nullptr -> type*;`
  - `type *(非常量指针) -> void *;`
  - `type * -> const void *`
5. 类类型转换

# 14.52 类型转换
> 在下面的加法表达式中分别选用了哪个operator+？列出候选函数、可行函数及为每个可行函数的实参执行的类型转换：

# 14.53 类型转换
> 假设我们已经定义了如第522页所示的SmallInt，判断下面的加法表达式是否合法。如果合法，使用了哪个加法运算符？如果不合法，应该怎样修改代码才能使其合法？
```c++
// int -> SmallInt
// SmallInt -> int
struct SmallInt {
  friend SmallInt operator+(const SmallInt &, const SmallInt &);

  // SmallInt(int i = 0) : val_(i) {}    // 产生歧义
  explicit SmallInt(int i = 0) : val_(i) {}
  operator int() const { return val_; }
  size_t val() const { return val_; }
 private:
  std::size_t val_;
};

SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs) {
  int a = lhs.val_ + rhs.val_;
  return SmallInt(a);
}

// double -> LongDouble
// LongDouble -> double
// LongDouble -> float
struct LongDouble {
  LongDouble operator+(const LongDouble &rhs) const {
    return {val_ + rhs.val_};
  }
  LongDouble(double val = 0.0F) : val_(val) {}
  operator double() { return val_; }
  // operator float()  { return val_; }  // 产生歧义
  double val_;
};

int main() {
  SmallInt si;
  LongDouble ld;
  ld = si + ld;
  // 产生歧义:
  // int + double
  // int + float

  ld = ld + si;
  double d = si + 3.14;
  // 产生歧义
  // 3.14 -> int -> SmallInt : SmallInt + SmallInt
  // si -> int : int + double
  return 0;
}
```


# 14.05
> 在7.5.1节中的练习7.40中，编写了下列类中某一个的框架(Tree)，请问在这个类中应该定义重载的运算符吗？如果是，请写出来。
# 14.08
> 你在7.5.1节中的练习中曾经选择并编写了一个类，为它定义一个输出运算符。
# 14.12
> 你在7.5.1节的练习中曾经选择并编写了一个类，为它定义一个输入运算符并确保该运算符可以处理输入错误。
# 14.15
> 你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有其他算术运算符吗？如果是，请实现它们；如果不是，解释原因。
# 14.17
> 你在7.5.1节中的练习7.40中曾经选择并编写了一个类，你认为它应该含有相等运算符吗？如果是，请实现它；如果不是，解释原因。
# 14.19
> 你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有关系运算符吗？如果是，请实现它；如果不是，解释原因。
# 14.24
> 你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有拷贝赋值和移动赋值运算符吗？如果是，请实现它们。
# 14.25
> 上题的这个类还需要定义其他赋值运算符吗？如果是，请实现它们；同时说明运算对象应该是什么类型并解释原因。
# 14.48
> 你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有向 bool 的类型转换运算符吗？如果是，解释原因并说明该运算符是否应该是 explicit的；如果不是，也请解释原因。
# 14.49
> 为上一题提到的类定义一个转换目标是 bool 的类型转换运算符，先不用在意这么做是否应该。

见 tree.cc