# 12.01
> 在此代码的结尾，b1 和 b2 各包含多少个元素？
```c++
StrBlob b1;
{
	StrBlob b2 = {"a", "an", "the"};
	b1 = b2;
	b2.push_back("about");  
}

// 各 4 个
```

# 12.02
> 编写你自己的StrBlob 类，包含const 版本的 front 和 back

见 str_blob.cc

# 12.05
> 我们未编写接受一个 initializer_list explicit 参数的构造函数。讨论这个设计策略的优点和缺点。

- 优点: 不会发生隐式类型转换, 所写即所得, 清晰明白
- 缺点: 调用麻烦, 需要临时变量时需要显示定义一个StrBlob, 其次`StrBlob str2={"123", "234", "345"};`形式出错无法调用拷贝构造函数

# 12.06
> 编写函数，返回一个动态分配的 int 的vector。将此vector 传递给另一个函数，这个函数读取标准输入，将读入的值保存在 vector 元素中。
> 再将vector传递给另一个函数，打印读入的值。记得在恰当的时刻delete vector。
```c++
#include <iostream>
#include <new>
#include <vector>

std::vector<int> *createVector() {
  return new (std::nothrow) std::vector<int>;
}

void print(std::vector<int> *p) {
  for (const auto &item : *p) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

void process(std::vector<int> *p) {
  if (!p) {
    std::cout << "new error!\n";
    return;
  }
  int curr;
  while (std::cin >> curr)
    p->push_back(curr);
  print(p);
  delete p;
}

int main() {
  auto it = createVector();
  process(it);
  return 0;
}
```

# 12.07
> 重做上一题，这次使用 shared_ptr 而不是内置指针。
```c++
#include <iostream>
#include <memory>
#include <vector>
std::shared_ptr<std::vector<int>> createVector() {
  return std::make_shared<std::vector<int>>();
}
void print(std::shared_ptr<std::vector<int>> p) {
  for (auto it = p->cbegin(); it != p->cend(); ++it)
    std::cout << *it << " ";
  std::cout << "\n";
}

void process(std::shared_ptr<std::vector<int>> p) {
  int curr;
  while (std::cin >> curr)
    p->push_back(curr);
  print(p);
}
int main() {
  auto it = createVector();
  process(it);
  return 0;
}
```

# 12.09
> 解释下面代码执行的结果。
```c++
int *q = new int(42), *r = new int(100);
r = q;   // r被赋值前没有释放内存导致内存泄漏
auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
r2 = q2; // r2被赋值前计数器减1为零, 自动释放内存, 安全
```

# 12.10
> 下面的代码调用了第413页中定义的 process 函数，解释此调用是否正确。如果不正确，应如何修改？
```c++
shared_ptr<int> p(new int(42)); // p 引用计数: 1
process(shared_ptr<int>(p));	// p 引用计数: 2
								// p 引用计数: 1 正确
```

# 12.16
> 如果你试图拷贝或赋值 unique_ptr，编译器并不总是能给出易于理解的错误信息。编写包含这种错误的程序，观察编译器如何诊断这种错误。
```bash
# 拷贝初始化
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
  std::unique_ptr<int> p=q;
                         ^
In file included from /usr/include/c++/8/memory:80,
                 from test.cpp:2:
/usr/include/c++/8/bits/unique_ptr.h:394:7: note: declared here
       unique_ptr(const unique_ptr&) = delete;
       ^~~~~~~~~~

# 赋值
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
  p=q;
    ^
In file included from /usr/include/c++/8/memory:80,
                 from test.cpp:2:
/usr/include/c++/8/bits/unique_ptr.h:395:19: note: declared here
       unique_ptr& operator=(const unique_ptr&) = delete;
                   ^~~~~~~~
```

# 12.21
> 也可以这样编写 StrBlobPtr 的 deref 成员，你认为哪个版本更好？为什么？
```c++
std::string& deref() const {
	return (*check(curr, "dereference past end"))[curr];
}
```

前者, 简洁明了, debug 好追踪

# 12.22
> 为了能让 StrBlobPtr 使用 const StrBlob，你觉得应该如何修改？定义一个名为ConstStrBlobPtr 的类，使其能够指向 const StrBlob。
 
见 str_blob_ptr.cc

# 12.25
> 给定下面的new表达式，你应该如何释放pa？
```c++
int *pa = new int[10];
```

delete [] pa;

# 12.26
> 用 allocator 重写第427页中的程序。
```c++
#include <iostream>
#include <string>
#include <memory>
const int n = 5;
int main() {
  std::string s, *q;
  std::allocator<std::string> alloc;
  auto const p = alloc.allocate(n);
  q = p;
  while (std::cin >> s && q != p + n)
    alloc.construct(q++, s);
  while (q != p) {
    std::cout << *(--q) << " ";
    alloc.destroy(q);
  }
  alloc.deallocate(p, n);
  return 0;
}
```

# 12.29
> 我们曾经用do while 循环来编写管理用户交互的循环。用do while 重写本节程序，解释你倾向于哪个版本，为什么？

个人认为 while-do 思考方式可以减少死循环发生可能性

# 12.30
> 定义你自己版本的 TextQuery 和 QueryResult 类，并执行12.3.1节中的runQueries 函数。

见 TextQuery.h 和 QueryResult.h

# 12.31
> 如果用 vector 代替 set 保存行号，会有什么差别？哪个方法更好？为什么？

vector 需要自己解决重复问题, 浪费效率

# 12.32
> 重写 TextQuery 和 QueryResult类，用StrBlob 代替 `vector<string>` 保存输入文件。
```c++
// 见 TextQuery.h 和 QueryResult.h
// StrBlob.h 增加函数	
std::string &operator[](Rank t);
```

# 12.33
> 在第15章中我们将扩展查询系统，在 QueryResult 类中将会需要一些额外的成员。
> 添加名为 begin 和 end 的成员，返回一个迭代器，指向一个给定查询返回的行号的 set 中的位置。
> 再添加一个名为 get_file 的成员，返回一个 shared_ptr，指向 QueryResult 对象中的文件。

见 TextQuery.h 和 QueryResult.h