# 13.02 拷贝构造函数
> 解释为什么下面的声明是非法的：
`Sales_data::Sales_data(Sales_data rhs);`

实参传递参数会调用拷贝构造函数, 而本身定义拷贝构造函数产生无限递归

# 13.04 拷贝构造函数
> 假定 Point 是一个类类型，它有一个public的拷贝构造函数，指出下面程序片段中哪些地方使用了拷贝构造函数：
```c++
Point global;
Point foo_bar(Point arg)                           // 1    形参拷贝构造
{
	Point local = arg, *heap = new Point(global);  // 2, 3 直接拷贝构造
	*heap = local; 
	Point pa[4] = { local, *heap };                // 4, 5 列表拷贝构造
	return *heap;                                  // 6    返回拷贝构造
}
```

# 13.12 析构函数
> 在下面的代码片段中会发生几次析构函数调用？
```c++
bool fcn(const Sales_data *trans, Sales_data accum)  // accum 
{
	Sales_data item1(*trans), item2(accum);          // item1, item2
	return item1.isbn() != item2.isbn();             // 共 3 次
}
```

# 13.13 测试拷贝构造和赋值运算符
> 理解拷贝控制成员和构造函数的一个好方法的定义一个简单的类，为该类定义这些成员，每个成员都打印出自己的名字：
> 给 X 添加拷贝赋值运算符和析构函数，并编写一个程序以不同的方式使用 X 的对象：将它们作为非引用参数传递；动态分配它们；将它们存放于容器中；
> 诸如此类。观察程序的输出，直到你确认理解了什么时候会使用拷贝控制成员，以及为什么会使用它们。
> 当你观察程序输出时，记住编译器可以略过对拷贝构造函数的调用。
```c++
struct X {
  X() { std::cout << "X()" << std::endl; }
  X(const X &) { std::cout << "X(const X&)" << std::endl; }
  X &operator=(const X &) {
    std::cout << "operator=(const X&)" << std::endl;
    return *this;
  }
  ~X() { std::cout << "~X()" << std::endl; }
};

int main() {
  std::vector<X> vec(1, X());

//X()
//X(const X&)
//~X()
//~X()

  return 0;
}
```

# 13.14 拷贝构造
> 假定 numbered 是一个类，它有一个默认构造函数，能为每个对象生成一个唯一的序号，保存在名为 mysn 的数据成员中。
> 假定 numbered 使用合成的拷贝控制成员，并给定如下函数：
> 则下面代码输出什么内容？
```c++
struct Numbered {
  static unsigned long long no;
  unsigned long long mysn;
  Numbered() {
    if (++no == 0ULL) {
      throw std::runtime_error("Can't Generate Unique Number!");
    }
    mysn = no;
  }
};

void f(Numbered s) {
  std::cout << s.mysn << "\n";
}

unsigned long long Numbered::no = 0ULL;

int main() {
  Numbered a, b = a, c = b;
  f(a);  // 1
  f(b);  // 1
  f(c);  // 1
  return 0;
}
```

# 13.15 拷贝构造
> 假定numbered 定义了一个拷贝构造函数，能生成一个新的序列号。这会改变上一题中调用的输出结果吗？如果会改变，为什么？新的输出结果是什么？
```c++
Numbered(const Numbered &rhs) {
  if (++no == 0ULL) {
    throw std::runtime_error("Can't Generate Unique Number!");
  }
    mysn = no;
}
// f 函数形参传递时挥发生拷贝构造
// 4
// 5
// 6
```

# 13.16 拷贝构造
> 如果 f 中的参数是 const numbered&，将会怎样？这会改变输出结果吗？如果会改变，为什么？新的输出结果是什么？
```c++
void f(const Numbered &s) {
  std::cout << s.mysn << "\n";
}
// 会, 引用不会发生拷贝构造
// 1
// 2
// 3
```

# 13.17 拷贝构造
> 分别编写前三题中所描述的 numbered 和 f，验证你是否正确预测了输出结果。

见 前三题 

# 13.28 树结构
> 给定下面的类，为其实现一个默认构造函数和必要的拷贝控制成员。
```c++
// (a) 
class TreeNode {
  private:
	std::string value;
	int count;
	TreeNode *left;
	TreeNode *right;	
};
// (b)
class BinStrTree{
  private:
	TreeNode *root;	
};
```

见 tree.cc

# 13.34 Message&Folder
> 编写本节所描述的 Message。

- 见 message.cc
- Message 与 Folder 多对多可以独立存在 (关联关系用 raw_pointer 即可)
- 对 set 的 insert 操作保证强异常安全 (换句话说, 对 OOM 保证强异常安全, 一般情况下不需要, 这里只是练习)
- 更改并解耦 remove, add 接口 (Message 与 Folder 对等, 接口应该对等)

# 13.35 Message&Folder
> 如果Message 使用合成的拷贝控制成员，将会发生什么？

Message 的复制不会在 Folder 中同步新增自身的关联, 导致析构时候数据不同步产生野指针

# 13.36 Message&Folder
> 设计并实现对应的 Folder 类。此类应该保存一个指向 Folder 中包含 Message 的 set。

见 folder.cc

# 13.33 Message&Folder
> 为什么Message的成员save和remove的参数是一个 Folder&？为什么我们不能将参数定义为 Folder 或是 const Folder？

- 见 message.h, 这里 save 和 remove 改为 AddFolderConnection 和 RemoveFolderConnection, 参数改为 Folder *
- 引用避免复制的额外成本, 语义中需要改变 Folder 中的 set 内容, 使用 const 限定则语义不符

# 13.37 Message&Folder
> 为 Message 类添加成员，实现向 folders 添加和删除一个给定的 Folder*。这两个成员类似Folder 类的 addMsg 和 remMsg 操作。

见 message.cc 这里考虑到同步问题, 将功能实现在 AddFolderConnection 中

# 13.38 Message&Folder
> 我们并未使用拷贝交换方式来设计 Message 的赋值运算符。你认为其原因是什么？

- 拷贝交换需要生成一个临时对象, 增加了成本, 考虑到异常安全这里使用的拷贝并交换方法

# 13.43 lambda&alloc
> 重写 free 成员，用 for_each 和 lambda 来代替 for 循环 destroy 元素。你更倾向于哪种实现，为什么？
```c++
// 后者, 函数式编程表达语义更加清楚
std::for_each(elements_, first_free_, [](std::string &p) {alloc.destroy(&p);});
```

# 13.44 String
> 编写标准库 string 类的简化版本，命名为 String。你的类应该至少有一个默认构造函数和一个接受 C 风格字符串指针参数的构造函数。
> 使用 allocator 为你的 String类分配所需内存。

见 m_string.h, 为了防止 '\0' 缓冲溢出, 增加 字符个数参数

# 13.48 vector扩容策略
> 定义一个vector<String> 并在其上多次调用 push_back。运行你的程序，并观察 String 被拷贝了多少次。
```c++
// 考虑到扩容 push_back 4 个对象实际上拷贝了 1 + 2 + 3 + 1 = 7 次
String(const String &str)
size:1 capacity:1
String(const String &str)
String(const String &str)
size:2 capacity:2
String(const String &str)
String(const String &str)
String(const String &str)
size:3 capacity:4
String(const String &str)
size:4 capacity:4
```

# 13.51 移动构造函数
> 虽然 unique_ptr 不能拷贝，但我们在12.1.5节中编写了一个 clone 函数，它以值的方式返回一个 unique_ptr。
> 解释为什么函数是合法的，以及为什么它能正确工作。

返回右值, 调用 `unique_ptr( unique_ptr&& u ) noexcept;` 移动动构造函数

# 13.54 移动赋值函数
> 如果我们为 HasPtr 定义了移动赋值运算符，但未改变拷贝并交换运算符，会发生什么？编写代码验证你的答案。
```c++
// 下面二者产生歧义
HasPtrPointer &HasPtrPointer::operator=(HasPtrPointer &&rhs);
HasPtrPointer &HasPtrPointer::operator=(HasPtrPointer rhs);
```