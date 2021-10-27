# 12.03 StrBlob 类设计
> StrBlob 需要 const 版本的 push_back 和 pop_back 吗？如需要，添加进去。否则，解释为什么不需要。

不需要, 二者操作改变类的数据, 不符合 成员函数的 const 语义, 即使可以通过 data 间接改变数据

# 12.04 StrBlob 类设计
> 在我们的 check 函数中，没有检查 i 是否大于0。为什么可以忽略这个检查？

i是无符号数, 模运算规定了边界

# 12.08 raw pointer 问题
> 下面的函数是否有错误？如果有，解释错误原因。
```c++
bool b() {
	int* p = new int;
	// ...
	return p;
}
```

出错, 指针p被强制类型转化成bool型后不能被正确释放, 产生内存泄漏 

# 12.11 smart pointer 问题
> 如果我们像下面这样调用 process，会发生什么？
```c++
process(shared_ptr<int>(p.get()));
// 所有权越界, 智能指针 p 持有的对象被临时对象给释放
```

# 12.12 smart pointer 问题
> p 和 sp 的定义如下，对于接下来的对 process 的每个调用，如果合法，解释它做了什么，如果不合法，解释错误原因：
```c++
auto p = new int();
auto sp = make_shared<int>();
process(sp);                   // 合法
process(new int());            // 不合法, 智能指针接管 raw_pointer 的构造函数是 explicit
process(p);                    // 不合法, 理由同上
process(shared_ptr<int>(p));   // 合法, 虽然 p 会成野指针
```

# 12.13 smart pointer 问题
> 如果执行下面的代码，会发生什么？
```c++
auto sp = make_shared<int>(); // make_shared 使用空参构造 int
                              // make_shared 必定构造对象
auto p = sp.get();            // 获取 raw_pointer
delete p;                     // sp 持有的对象成了野指针
```

# 12.14 smart pointer 问题管理哑类
> 编写你自己版本的用 shared_ptr 管理 connection 的函数。

# 12.15 smart pointer 问题管理哑类
> 重写上一题的程序，用 lambda 代替end_connection 函数。
```c++
#include <iostream>
#include <memory>
#include <exception>

struct destination {};
struct connection {};

connection connect(destination *p) {
  std::cout << "connect ! \n";
  return connection();                  // 值返回一个默认构造的connection
}

void disconnect(connection conn) {
  std::cout << "disconnect ! \n";
}

void end_connection(connection *conn) { // 注意 删除器参数必须是 T* 类型
  disconnect(*conn);
}

void f(destination &d) {
  connection conn = connect(&d);
  //std::shared_ptr<connection> p(&conn, end_connection);
  std::shared_ptr<connection> p(&conn, [](connection *p) { disconnect(*p); });

  // throw std::exception();
}

int main() {
  destination dd;
  f(dd);
  return 0;
}
```

# 12.17 smart pointer 问题
> 下面的 unique_ptr 声明中，哪些是合法的，哪些可能导致后续的程序错误？解释每个错误的问题在哪里。
```c++
int ix = 1024, *pi = &ix, *pi2 = new int(2048);
typedef unique_ptr<int> IntP;
IntP p0(ix);                    // 错误, int不是内置指针
IntP p1(pi);                    // 错误, pi不是手动分配的内存
IntP p2(pi2);                   // 正确, 但是pi2有可能变成野指针
IntP p3(&ix);                   // 错误, 同p1
IntP p4(new int(2048));         // 正确
IntP p5(p2.get());              // 错误, 所有权越界
```

# 12.18 smart pointer 问题
> shared_ptr 为什么没有 release 成员？

- release 函数返回所管理的指针, 并将本身设置为空, shared_ptr 存在引用计数, 不会直接置空
- 存在类似的 reset 函数, 但是会先检查引用计数再做释放操作

# 12.19 StrBlobStr 设计
> 定义你自己版本的 `StrBlobPtr`，更新 `StrBlob` 类，加入恰当的 `friend` 声明以及 `begin` 和 `end` 成员。

见 str_blob_ptr.cc

# 12.20 StrBlobStr 设计
> 编写程序，逐行读入一个输入文件，将内容存入一个 StrBlob 中，用一个 StrBlobPtr 打印出 StrBlob 中的每个元素。

见 str_blob_test.cc

# 12.23 strncpy 与 strncat 区别
> 编写一个程序，连接两个字符串字面常量，将结果保存在一个动态分配的char数组中。重写这个程序，连接两个标准库string对象。
```c++
const char *p1 = "123456";
const char *p2 = "78910";
size_t p1_len = strlen(p1);
size_t p2_len = strlen(p2);

char *p = new char[p1_len + p2_len + 1];
std::strncpy(p, p1, p1_len);           // "\0" 包括在 n 内
std::strncat(p + p1_len, p2, p2_len);  // "\0" 不包括在 n 内
std::cout << p << "\n";

std::string s1("abcdefg");
std::string s2("hij");
strncpy(p, (s1 + s2).c_str(), p1_len + p2_len + 1);
std::cout << p << '\n';

delete[] p;
```

# 12.24 动态分配数组模拟 vector
> 编写一个程序，从标准输入读取一个字符串，存入一个动态分配的字符数组中。
> 描述你的程序如何处理变长输入。
> 测试你的程序，输入一个超出你分配的数组长度的字符串。
```c++
#include <iostream>
#include <cstring>
#include <string>
int main() {
  std::string str;
  size_t size = kDefaultSize;
  char *p = new char[kDefaultSize];
  while (std::cin >> str) {
    if (str.size() >= size) {
      char *newp = new char[size *= 2];
      delete [] p;
      p = newp;
    }
    std::strncpy(p, str.c_str(), str.size() + 1);
    std::cout << p << '\n';
  }
  delete [] p;
  return 0;
}
```

# 12.27 TextQuery 设计
> TextQuery 和 QueryResult 类只使用了我们已经介绍过的语言和标准库特性。不要提前看后续章节内容，只用已经学到的知识对这两个类编写你自己的版本。

见 TextQuery.h 和 QueryResult.h

# 12.28 TextQuery 设计
> 编写程序实现文本查询，不要定义类来管理数据。你的程序应该接受一个文件，并与用户交互来查询单词。使用vector、map 和 set 容器来保存来自文件的数据并生成查询结果。

见 text_query_test.cc