# 14.01
> 在什么情况下重载的运算符与内置运算符有所区别？在什么情况下重载的运算符又与内置运算符一样？

不一样: `&&`, `||`, `,` 求值顺序会发生改变, `&` 语义会发生改变
一样: 其他重载运算符是一致的(实现上保证语义, 返回类型的前提下)

# 14.02
> 为 Sales_data 编写重载的输入、输出、加法和复合赋值运算符。

见 sales_data.cc

# 14.03
> string 和 vector 都定义了重载的==以比较各自的对象，
> 假设 svec1 和 svec2 是存放 string 的 vector，确定在下面的表达式中分别使用了哪个版本的==？
```c++
"cobble" == "stone"   // 非重载
svec1[0] == svec2[0]  // string
svec1 == svec2        // vector
svec1[0] == "stone"   // string
```

# 14.04
> 如何确定下列运算符是否应该是类的成员？
```c++
%   // 算术, 非成员
%=  // 赋值, 成员
++  // 递增, 成员
->  // 访问, 成员
<<  // 输出, 非成员
&&  // 算术, 非成员
==  // 判等, 非成员
()  // 调用, 成员
```

# 14.06
> 为你的 Sales_data 类定义输出运算符。

见 sales_data.cc

# 14.07
> 你在13.5节的练习中曾经编写了一个String类，为它定义一个输出运算符。

见 m_string.h

# 14.09
> 为你的 Sales_data 类定义输入运算符。

见 sales_data.cc

# 14.10
> 对于 Sales_data 的输入运算符来说如果给定了下面的输入将发生什么情况？

(a) 0-201-99999-9 10 24.95  格式正确
(b) 10 24.95 0-210-99999-9  读入double时格式错误, 输入对象被重置为默认构造

# 14.13
> 你认为 Sales_data 类还应该支持哪些其他算术运算符？如果有的话，请给出它们的定义。

减法运算符, 与加法类似

# 14.14
> 你觉得为什么调用 operator+= 来定义operator+ 比其他方法更有效？

委托 operator+= 可以保持一致性, 同时使代码更简洁

# 14.16
> 为你的 StrBlob 类、StrBlobPtr 类、StrVec 类和 String 类分别定义相等运算符和不相等运算符。

见 str_blob.cc, str_blob_ptr.cc, str_vec.cc, m_string.h

# 14.18
> 为你的 StrBlob 类、StrBlobPtr 类、StrVec 类和 String 类分别定义关系运算符。

见 str_blob.cc, str_blob_ptr.cc, str_vec.cc, m_string.h

# 14.20
> 为你的 Sales_data 类定义加法和复合赋值运算符。

见 sales_data.cc

# 14.21
> 编写 Sales_data 类的+ 和+= 运算符，使得 + 执行实际的加法操作而 += 调用+。
> 相比14.3节和14.4节对这两个运算符的定义，本题的定义有何缺点？试讨论之。
```c++
SalesData operator+(const SalesData & lhs, const SalesData &rhs) {
  SalesData sum;         // 定义一次临时变量
  sum.book_no_ = lhs.book_no_;
  sum.units_sold_ = lhs.units_sold_ + rhs.units_sold_;
  sum.revenue_ = lhs.revenue_ + rhs.revenue_;
  return sum;            // 拷贝一次到调用点
}
SalesData& SalesData::operator+=(const SalesData &rhs){
  *this = *this + rhs;   // 调用 + 等价定义一次 拷贝一次 
  return *this;
}
// 缺点: 复合赋值多生成一次临时变量 和 额外执行一次拷贝
```

# 14.22
> 定义赋值运算符的一个新版本，使得我们能把一个表示 ISBN 的 string 赋给一个 Sales_data 对象。
```c++
SalesData::SalesData(std::string book_no) 
    : SalesData(std::move(book_no), 0, 0.0F) {}
```

# 14.23
> 为你的 StrVec 类定义一个 initializer_list 赋值运算符。

见 str_vec.cc

# 14.26
> 为你的 StrBlob 类、StrBlobPtr 类(个人觉得没有必要)、StrVec 类和 String 类定义下标运算符。

见 str_blob.cc, str_blob_ptr.cc, str_vec.cc, m_string.h

# 14.27
> 为你的 StrBlobPtr 类添加递增和递减运算符。

见 str_blob_ptr.cc

# 14.28
> 为你的 StrBlobPtr 类添加加法和减法运算符，使其可以实现指针的算术运算。

见 str_blob_ptr.cc

# 14.29
> 为什么不定义const版本的递增和递减运算符？

递增与递减会改变自身内容

# 14.30
> 为你的 StrBlobPtr 类和在12.1.6节练习12.22中定义的 ConstStrBlobPtr 的类分别添加解引用运算符和箭头运算符。
> 注意：因为 ConstStrBlobPtr 的数据成员指向const vector，所以ConstStrBlobPtr 中的运算符必须返回常量引用。

见 str_blob_ptr.cc

# 14.31
> 我们的 StrBlobPtr 类没有定义拷贝构造函数、赋值运算符以及析构函数，为什么？
```c++
// 数据成员的类型决定合成的拷贝构造, 赋值运算符和析构可以正常使用
std::weak_ptr<std::vector<std::string>> wptr;
std::size_t curr;
```

# 14.32
> 定义一个类令其含有指向 StrBlobPtr 对象的指针，为这个类定义重载的箭头运算符。

见 str_blob_ptr_ptr.cc

# 14.33
> 一个重载的函数调用运算符应该接受几个运算对象？

等于调用运算符的参数

# 14.34
> 定义一个函数对象类，令其执行if-then-else 的操作：
> 该类的调用运算符接受三个形参，它首先检查第一个形参，如果成功返回第二个形参值；
> 如果不成功返回第三个形参的值。
```c++
class IfThenElse {
 public:
  int operator()(const int &e1, const int &e2, const int &e3) {
    return e1 ? e2 : e3;
  }
};
```

# 14.35
> 编写一个类似于 PrintString 的类，令其从 istream 中读取一行输入，然后返回一个表示我们所读内容的string。如果读取失败，返回空string。
```c++
class PrintString {
 public:
  explicit PrintString(std::istream &ist) : is(ist) {}
  std::string operator()() {
    std::string curr;
    if (getline(is, curr)) { return curr; }
    return curr = "";
  }
 private:
  std::istream &is;
};
```

# 14.36
> 使用前一个练习定义的类读取标准输入，将每一行保存为 vector 的一个元素。 
```c++
int main() {
  std::vector<std::string> vec;
  PrintString ps(std::cin);
  for (size_t i = 0; i != 3; ++i) {
    vec.push_back(ps());
  }
  for (const auto &it: vec) {
    std::cout << it << std::endl;
  }
  return 0;
}
```

# 14.37
> 编写一个类令其检查两个值是否相等。使用该对象及标准库算法编写程序，令其替换某个序列中具有给定值的所有实例。
```c++
class E {
 private:
  std::string str;
 public:
  E(const std::string a = "") : str(a) {}
  bool operator()(const std::string &s) const {
    return s == str;
  }
};

int main() {
  std::string curr, str1, str2;
  std::cin >> str1 >> str2;  // str1 要替换的值  str2 替换成的值
  E e(str1);

  std::vector<std::string> vec;
  while (std::cin >> curr) {
    vec.push_back(curr);
  }
  for (const auto &it: vec) {
    std::cout << it << " ";
  }
  std::cout << std::endl;

  std::replace_if(vec.begin(), vec.end(), e, str2);

  for (const auto &it: vec) {
    std::cout << it << " ";
  }
  std::cout << std::endl;

  return 0;
}
// 14_37_data
```

# 14.38
> 编写一个类令其检查某个给定的 string 对象的长度是否与一个阈值相等。
> 使用该对象编写程序，统计并报告在输入的文件中长度为1的单词有多少个，长度为2的单词有多少个、......、长度为10的单词有多少个。
```c++
class IsE {
 public:
  explicit IsE(const size_t &n) : n_(n) {}

  size_t n() const { return n_; }

  bool operator()(const std::string &str) const { return str.size() == n_; }
  IsE &operator++() { n_++; return *this; }

 private:
  size_t n_ = 0;
};

int main() {
  std::string curr;
  std::vector<std::string> vec;
  while (std::cin >> curr) {
    vec.push_back(curr);
  }

  size_t min = numeric_limits<size_t>::max();
  size_t max = numeric_limits<size_t>::min();
  std::for_each(vec.begin(), vec.end(),
                [&min, &max](const std::string &str) {
                  if (str.size() >= max) max = str.size();
                  if (str.size() <= min) min = str.size();
                });
  IsE ise(min);
  while (ise.n() <= max) {
    std::cout << "word size : " << ise.n()
              << " count : " << std::count_if(vec.begin(), vec.end(), ise)
              << std::endl;
    ++ise;
  }
  return 0;
}
// 14_38_data
```

# 14.39
> 修改上一题的程序令其报告长度在1到9之间的单词有多少个、长度在10以上的单词有多少个。
```c++
class IsE {
 private:
  size_t min;
  size_t max;
 public:
  explicit IsE(const size_t &mi = 0, const size_t &ma = 0) : min(mi), max(ma) {}
  bool operator()(const std::string &str) const {
    return (min <= str.size()) && (str.size() <= max);
  }
  void setRange(const size_t &mi = 0, const size_t &ma = 0) {
    min = mi;
    max = ma;
  }
};

int main() {
  std::string curr;
  std::vector<std::string> vec;
  while (std::cin >> curr) {
    vec.push_back(curr);
  }
  IsE ise(0, 9);
  std::cout << " size : 00 ~ 09  count : "
            << std::count_if(vec.begin(), vec.end(), ise) << "\n";

  ise.setRange(10, std::numeric_limits<size_t>::max());

  std::cout << " size : 10 ~ max count : "
            << std::count_if(vec.begin(), vec.end(), ise) << "\n";
  return 0;
}
// 14_39_data
```

# 14.40
> 重新编写10.3.2节的biggies 函数，使用函数对象替换其中的 lambda 表达式。
```c++
class CheckSize {
 public:
  bool operator()(const string &s, string::size_type sz) {
    return s.size() >= sz;
  }
};

class Print {
 public:
  void operator()(const string &s) {
    cout << s << " ";
  }
};

void Biggies(vector<string> &vec, vector<string>::size_type sz) {
  // 去重
  sort(vec.begin(), vec.end());
  auto iter = unique(vec.begin(), vec.end());
  vec.erase(iter, vec.end());

  // 筛选 >= size 的元素出来
  auto it = stable_partition(vec.begin(), vec.end(), bind(CheckSize(), _1, sz));
  vec.erase(it, vec.end());
  for_each(vec.begin(), vec.end(), Print());
}

int main() {
  vector<string> vec{"2134", "2134", "2", "", "324324234", "234123413241"};
  Biggies(vec, 5);
  return 0;
}
```

# 14.41
> 你认为 C++ 11 标准为什么要增加 lambda？对于你自己来说，什么情况下会使用 lambda，什么情况下会使用类？

- lambda 生成临时的无名类的无名对象, 比函数对象更方便调用, 更好支持函数式编程
- 适合只一次性用到, 处理流程简单的情形

# 14.45
> 编写类型转换运算符将一个 Sales_data 对象分别转换成 string 和 double，你认为这些运算符的返回值应该是什么？

见 SalesData.cc

# 14.46
> 你认为应该为 Sales_data 类定义上面两种类型转换运算符吗？应该把它们声明成 explicit 的吗？为什么？
```c++
// 返回 书 id, 为了让使用者不发生意外隐式转换声明为explicit
explicit operator std::string() { return book_no_; }
// 返回值是什么存在歧义, 应该不定义该类型转换
explicit operator double() { return units_sold_; }
```