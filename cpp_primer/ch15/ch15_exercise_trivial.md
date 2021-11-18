# 15.03
> 定义你自己的 Quote 类和 print_total 函数。

见 quote.h

# 15.04
> 下面哪条声明语句是不正确的？请解释原因。
```c++
class Base { ... };
class Derived : public Derived { ... };  // 错误, 不可自继承
class Derived : private Base { ... };    // 正确
class Derived : public Base;             // 错误, 声明不用派生列表
```

# 15.05
> 定义你自己的 Bulk_quote 类。

见 bulk_quote.h

# 15.06
> 将 Quote 和 Bulk_quote 的对象传给15.2.1节练习中的 print_total 函数，检查该函数是否正确。

见 quote_test.cc

# 15.07
> 定义一个类使其实现一种数量受限的折扣策略，具体策略是：
> 当购买书籍的数量不超过一个给定的限量时享受折扣，如果购买量一旦超过了限量，则超出的部分将以原价销售。 

见 bulk_limit_quote.h

# 15.10
> 回忆我们在8.1节进行的讨论，解释第284页中将 ifstream 传递给 Sales_data 的read 函数的程序是如何工作的。

std::istream 是 std::ifstream 的基类, 存在动态绑定

# 15.11
> 为你的 Quote 类体系添加一个名为 debug 的虚函数，令其分别显示每个类的数据成员。

见 quote.h

# 15.12
> 有必要将一个成员函数同时声明成 override 和 final 吗？为什么？

- override 表示覆盖基类的虚函数
- final 表示声明的虚函数不能被派生类覆盖
- 二者没有直接关系, 可以一起声明

# 15.15
> 定义你自己的 Disc_quote 和 Bulk_quote。

见 disc_quote.h, bulk_quote.h

# 15.16
> 改写你在15.2.2节练习中编写的数量受限的折扣策略，令其继承 Disc_quote。

见 bulk_limit_quote.h

# 15.17
> 尝试定义一个 Disc_quote 的对象，看看编译器给出的错误信息是什么？

cannot declare variable ‘dq’ to be of abstract type ‘DiscQuote’

# 15.21
> 从下面这些一般性抽象概念中任选一个（或者选一个你自己的），将其对应的一组类型组织成一个继承体系：
```text
(a) 图形文件格式（如gif、tiff、jpeg、bmp）
(b) 图形基元（如方格、圆、球、圆锥）         
(c) C++语言中的类型（如类、函数、成员函数）

见 shape
```

# 15.22
> 对于你在上一题中选择的类，为其添加函数的虚函数及公有成员和受保护的成员。

见 shape_2d.h

# 15.23
> 假设第550页的 D1 类需要覆盖它继承而来的 fcn 函数，你应该如何对其进行修改？
> 如果你修改之后 fcn 匹配了 Base 中的定义，则该节的那些调用语句将如何解析？
```c++
// 将 int fcn(int); 改为
int fcn();
// 对于 fcn() 的调用遵循动态绑定
```

# 15.25
> 我们为什么为 Disc_quote 定义一个默认构造函数？如果去掉该构造函数的话会对 Bulk_quote 的行为产生什么影响？

Disc_quote 自定义了一个构造函数不会合成默认构造函数, 如果没有定义父类的默认构造函数则Bulk_quote 的默认构造函数无法调用

# 15.26
> 定义 Quote 和 Bulk_quote 的拷贝控制成员，令其与合成的版本行为一致。
> 为这些成员以及其他构造函数添加打印状态的语句，使得我们能够知道正在运行哪个程序。使用这些类编写程序，预测程序将创建和销毁哪些对象。
> 重复实验，不断比较你的预测和实际输出结果是否相同，直到预测完全准确再结束。

- 拷贝控制: 顺序从继承链顶至底
- 析构: 顺序从继承链底至顶

# 15.27
> 重新定义你的 Bulk_quote 类，令其继承构造函数。

见 bulk_quote.h

# 15.28
>  定义一个存放 `Quote` 对象的 `vector`，将 `Bulk_quote` 对象传入其中。计算 `vector` 中所有元素总的 `net_price`。

发生 slice down 问题

# 15.29
> 再运行一次你的程序，这次传入 Quote 对象的 shared_ptr 。如果这次计算出的总额与之前的不一致，解释为什么;如果一直，也请说明原因。

见 quote_test.cc, 调用虚函数不会发生 slice down 问题

# 15.30
> 编写你自己的 Basket 类，用它计算上一个练习中交易记录的总价格。

见 basket.h

# 15.32
> 当一个 Query 类型的对象被拷贝、移动、赋值或销毁时，将分别发生什么？

- Query 只含有指向 QueryBase的智能指针
- 拷贝时指针计数 +1 移动时指针不改变计数
- 销毁时计数-1, 若为零则销毁QueryBase对象

# 15.33
> 当一个 Query_base 类型的对象被拷贝、移动赋值或销毁时，将分别发生什么？

- Query\_base 对象及其派生类对象的数据成员分别为 
- WordQuery : string 保存查询单词, 是组合查询字符串的基础 
- NotQuery : query 保存一元的Query类(封装了其他Query\_base对象指针)
- BinaryQuery : lhs rhs 保存二元的Query类(类似树, 封装了孩子的指针 )

# 15.35
> 实现 Query 类和 Query_base 类，其中需要定义rep 而无须定义 eval。

见 Query.cc, QueryBase.cc

# 15.36
> 在构造函数和 rep 成员中添加打印语句，运行你的代码以检验你对本节第一个练习中(a)、(b)两小题的回答是否正确。
```text
# Query q = Query("fiery") & Query("bird") | Query("wind");
WordQuery constructor() : wind
WordQuery constructor() : bird
WordQuery constructor() : fiery
AndQuery constructor() : (fiery & bird)
OrQuery constructor() : ((fiery & bird) | wind)

# 同一表达式扫描后, 具体的对象求值顺序是未定义的, 运算符处理的顺序是固定的
AndQuery 必定在 OrQuery 之前, wind 和 bird之后

BinaryQuery rep() : |
WordQuery rep() : wind
BinaryQuery rep() : &
WordQuery rep() : bird
WordQuery rep() : fiery
```

# 15.38
> 下面的声明合法吗？如果不合法，请解释原因;如果合法，请指出该声明的含义。
```c++
BinaryQuery a = Query("fiery") & Query("bird"); // 不合法, slice down
AndQuery b = Query("fiery") & Query("bird");    // 不合法, 同上
OrQuery c = Query("fiery") & Query("bird");     // 不合法, 同上
```

# 15.39
> 实现 Query 类和　Query_base 类，求图15.3中表达式的值并打印相关信息，验证你的程序是否正确。

见 query_test.cc

# 15.40
> 在 OrQuery 的 eval 函数中，如果 rhs 成员返回的是空集将发生什么？

rhs 返回空集 则插入空集

# 15.41
> 重新实现你的类，这次使用指向 Query_base 的内置指针而非 shared_ptr。请注意，做出上述改动后你的类将不能再使用合成的拷贝控制成员。

略

# 15.42
> 从下面的几种改进中选择一种，设计并实现它:

(a) 按句子查询并打印单词，而不再是按行打印。
(b) 引入一个历史系统，用户可以按编号查阅之前的某个查询，并可以在其中添加内容或者将其余其他查询组合。
(c) 允许用户对结果做出限制，比如从给定范围的行中跳出匹配的进行显示。 (选择 C)

见 Query_base.h