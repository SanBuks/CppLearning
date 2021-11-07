# 13.01
> 拷贝构造函数是什么？什么时候使用它？

拷贝构造函数是形如 `ClassName (const ClassName &, int a=3...)`的成员函数, 在如下情况下调用: 
  - `ClassName a=b;`
  -  实参传递
  -  函数值返回
  -  列表初始化
  -  容器的push等操作

# 13.03
> 当我们拷贝一个StrBlob时，会发生什么？拷贝一个StrBlobPtr呢？

StrBlob 的 shared_ptr<vector<string>> 的引用计数 + 1, StrBlobPtr 的 weak_ptr<vector<string>> 无变化

# 13.05
> 给定下面的类框架，编写一个拷贝构造函数，拷贝所有成员。你的构造函数应该动态分配一个新的string，并将对象拷贝到ps所指向的位置，而不是拷贝ps本身：
```c++
class HasPtr {
 public:
  HasPtr(const std::string &s = std::string()) :
      ps(new std::string(s)), i(0) {}
 private:
  std::string *ps;
  int i;
};
```

见 has_ptr_value.cc

# 13.06
> 拷贝赋值运算符是什么？什么时候使用它？
> 合成拷贝赋值运算符完成什么工作？
> 什么时候会生成合成拷贝赋值运算符？

- 重载 = 运算符的成员函数, 如 Foo &operator=(const Foo& rhs); 形如 a = b; 时调用
- 将 b 对象的所有数据成员的值赋予 a 对象的所有数据成员
- 如果一个类未定义 operator= 函数, 且 operator= 函数可以合成的时候会合成

# 13.07
> 当我们将一个 StrBlob 赋值给另一个 StrBlob 时，会发生什么？赋值 StrBlobPtr 呢？

- 右侧 StrBlob 的引用计数 + 1, 左侧 -1 
- StrBlobPtr 的引用计数不会发生变化

# 13.08
> 为13.1.1节练习 13.5 中的 HasPtr 类编写赋值运算符。类似拷贝构造函数，你的赋值运算符应该将对象拷贝到ps指向的位置。

见 has_ptr_value.cc

# 13.09
> 析构函数是什么？合成析构函数完成什么工作？什么时候会生成合成析构函数？

- 负责对象销毁相关工作的成员函数, 形如 ~Foo(); 
- 没有自定义析构函数且能够合成析构函数时会合成析构函数


# 13.10
> 当一个 StrBlob 对象销毁时会发生什么？一个 StrBlobPtr 对象销毁时呢？

- StrBlob 引用计数减少, 其他成员析构
- StrBlobPtr 所有成员析构

# 13.11
> 为前面练习中的 HasPtr 类添加一个析构函数。

见 has_ptr_value.cc

# 13.18
> 定义一个 Employee 类，它包含雇员的姓名和唯一的雇员证号。为这个类定义默认构造函数，以及接受一个表示雇员姓名的 string 的构造函数。
> 每个构造函数应该通过递增一个 static 数据成员来生成一个唯一的证号。
```c++
class Employee {
 public:
  static unsigned long long no;

  explicit Employee(std::string name) : name_(std::move(name)) {
    if (++no == 0ULL) {
      throw std::runtime_error("Can't Generate Unique Number!");
    }
    employee_sn_ = no;
  }
  Employee(const Employee &rhs) = delete;
  Employee &operator=(const Employee &rhs) = delete;
  ~Employee() = default;

 private:
  std::string name_;
  unsigned long long employee_sn_;
};

unsigned long long Employee::no = 0ULL;
```

# 13.19
> 你的 Employee 类需要定义它自己的拷贝控制成员吗？如果需要，为什么？如果不需要，为什么？实现你认为 Employee 需要的拷贝控制成员。

需要, 需要定义为删除, 因为拷贝一个唯一标识雇员的操作是没有意义的

# 13.20
> 解释当我们拷贝、赋值或销毁 TextQuery 和 QueryResult 类对象时会发生什么？

- TextQuery: files_ 引用计数增加减少, mp_ 值复制销毁
- QueryResult: word_search_ 值复制销毁, files_ 和 lines_ 引用计数增加减少 

# 13.21
> 你认为 TextQuery 和 QueryResult 类需要定义它们自己版本的拷贝控制成员吗？如果需要，为什么？实现你认为这两个类需要的拷贝控制操作。

不需要, 数据成员的相关拷贝控制操作符合语义

# 13.22
> 假定我们希望 HasPtr 的行为像一个值。即，对于对象所指向的 string 成员，每个对象都有一份自己的拷贝。
> 我们将在下一节介绍拷贝控制成员的定义。但是，你已经学习了定义这些成员所需的所有知识。
> 在继续学习下一节之前，为 HasPtr 编写拷贝构造函数和拷贝赋值运算符。

见 has_ptr_value.cc

# 13.23
> 比较上一节练习中你编写的拷贝控制成员和这一节中的代码。确定你理解了你的代码和我们的代码之间的差异。

见 has_ptr_value.cc

# 13.24
> 如果本节的 HasPtr 版本未定义析构函数，将会发生什么？如果未定义拷贝构造函数，将会发生什么？

- 未定义析构函数，会发生内存泄漏
- 未定义拷贝构造函数，浅复制后析构可能会产生野指针

# 13.25
> 假定希望定义 StrBlob 的类值版本，而且希望继续使用 shared_ptr，这样我们的 StrBlobPtr 类就仍能使用指向vector的 weak_ptr 了。
> 你修改后的类将需要一个拷贝的构造函数和一个拷贝赋值运算符，但不需要析构函数。解释拷贝构造函数和拷贝赋值运算符必须要做什么。解释为什么不需要析构函数。

类值拷贝, 每个 StrBlob 的引用计数唯一, 析构时候为 0, 会自动释放对象, 因此不需要析构函数

# 13.26
> 对上一题中描述的 StrBlob 类，编写你自己的版本。
```c++
class A {                                      // 等价StrBlob
  std::shared_ptr<int> ps;                     // 对智能指针成员定义值拷贝则每个对象引用计数为1
 public:
  A(const int &e = 10) 
      : ps(std::make_shared<int>(e)) {}

  A &operator=(const A &rhs) {
    ps = std::make_shared<int>(*rhs.ps);       // 分配值拷贝, 原来分配的对象被销毁
  }

  A(const A &rhs)
      : ps(std::make_shared<int>(*rhs.ps)) {}  // 与赋值运算符类似
  ~A() = default;                              // 每个对象离开作用域时引用计数必定为0 则直接使用默认即可
  void print() { std::cout << *ps << '\n'; }
};
```

# 13.27
> 定义你自己的使用引用计数版本的 HasPtr。

见 has_ptr_pointer.cc

# 13.29
> 解释 swap(HasPtr&, HasPtr&)中对 swap 的调用不会导致递归循环。

- 对于 int 调用 模板函数 std::swap(int lhs, int rhs) 版本
- 对于 string * 调用 模板函数 std::swap(string *lhs, string *rhs) 版本

# 13.30
> 为你的类值版本的 HasPtr 编写 swap 函数，并测试它。为你的 swap 函数添加一个打印语句，指出函数什么时候执行。

见 has_ptr_value.cc

# 13.31
> 为你的 HasPtr 类定义一个 < 运算符，并定义一个 HasPtr 的 vector。为这个 vector 添加一些元素，并对它执行 sort。注意何时会调用 swap。

见 has_ptr_test.cc 的 TestHasPtrValueSwap 函数

# 13.32
> 类指针的 HasPtr 版本会从 swap 函数收益吗？如果会，得到了什么益处？如果不是，为什么？

类指针的版本不用进行内存分配, 不会得到性能提升

# 13.39
> 编写你自己版本的 StrVec，包括自己版本的 reserve、capacity 和 resize。

见 StrVec.cc

# 13.40
> 为你的 StrVec 类添加一个构造函数，它接受一个 initializer_list<string> 参数。

见 StrVec.cc

# 13.41
> 在 push_back 中，我们为什么在 construct 调用中使用后置递增运算？如果使用前置递增运算的话，会发生什么？

- first_free_ 指向第一个未构造的元素内存空间
- 前置递增会忽略第一个空间, 指向最后一个不存在的空间, 产生未定义行为

# 13.42
> 在你的 TextQuery 和 QueryResult 类中用你的 StrVec 类代替vector<string>，以此来测试你的 StrVec 类。

StrBlob 同理

# 13.45
> 解释左值引用和右值引用的区别？

- 左值引用 绑定到 左值
- 右值引用 绑定到 右值
- const 左值引用 可以绑定到任何值

# 13.46
> 什么类型的引用可以绑定到下面的初始化器上？
```c++
int f();
vector<int> vi(100);
int? r1 = f();          // && 
int? r2 = vi[0];        // &
int? r3 = r1;           // &
int? r4 = vi[0] * f();  // &&
```

# 13.47
> 对你在习题13.44中定义的 String类，为它的拷贝构造函数和拷贝赋值运算符添加一条语句，在每次函数执行时打印一条信息。

见 string_test.cc 中 TestPushBack

# 13.49
> 为你的 StrVec、String 和 Message 类添加一个移动构造函数和一个移动赋值运算符。

见 str_vec.cc, m_string.h, message.h

# 13.50
> 在你的 String 类的移动操作中添加打印语句，并重新运行13.6.1节的练习13.48中的程序，它使用了一个vector<String>，观察什么时候会避免拷贝。

见 string_test.cc 中 TestMove

# 13.52
> 详细解释第478页中的 HasPtr 对象的赋值发生了什么？特别是，一步一步描述 hp、hp2 以及 HasPtr 的赋值运算符中的参数 rhs 的值发生了什么变化。
```c++
hp = hp2;             // 优先调用拷贝赋值运算符, 重新生成一个新的 string 和 use 指针
hp = std::move(hp2);  // 优先调用移动赋值运算符, 只是移动了指向资源的指针
```

# 13.53
> 从底层效率的角度看，HasPtr 的赋值运算符并不理想，解释为什么？
> 为 HasPtr 实现一个拷贝赋值运算符和一个移动赋值运算符，并比较你的新的移动赋值运算符中执行的操作和拷贝并交换版本中的执行的操作。

- 不理想的原因是赋值运算符函数生成了一个新的临时对象 rhs
- 移动赋值运算符 只 进行移动操作, 而拷贝赋值运算符分配内存生成了临时对象

# 13.55
> 为你的 StrBlob 添加一个右值引用版本的 push_back。
```c++
void push_back(string &&s) {
  data->push_back(std::move(s));
}
```

# 13.56
> 如果 sorted 定义如下，会发生什么？
```c++
Foo Foo::sorted() const & {
	Foo ret(*this);
	return ret.sorted();
}

// 会产生无限递归
```

# 13.57
> 如果 sorted 定义如下，会发生什么：
```c++
Foo Foo::sorted() const & { 
  return Foo(*this).sorted(); 
}

// 正确, Foo(*this) 调用 右值限定版本的排序函数, 不会发生无限递归
```


# 13.58
> 编写新版本的 Foo 类，其 sorted 函数中有打印语句，测试这个类，来验证你对前两题的答案是否正确。
```c++
using namespace std;

class Foo {
 public:
  Foo sorted() &&;
  Foo sorted() &;
 private:
  vector<int> data;
};
Foo Foo::sorted() && {
  sort(data.begin(), data.end());
  std::cout << "&&" << std::endl;
  return *this;
}
Foo Foo::sorted() & {
  std::cout << "const &" << std::endl;
  Foo ret(*this);
  ret.sorted();  // 产生无限循环
  return ret;
//  return Foo(*this).sorted();
}

int main() {
  Foo f;
  f.sorted();
}
```