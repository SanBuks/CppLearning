# 0. 背景
```text
C++ is one of the main development languages used by many of Google's open-source projects. As every C++ programmer knows, the language has many powerful features, but this power brings with it complexity, which in turn can make code more bug-prone and harder to read and maintain.

The goal of this guide is to manage this complexity by describing in detail the dos and don'ts of writing C++ code . These rules exist to keep the code base manageable while still allowing coders to use C++ language features productively.

Style, also known as readability, is what we call the conventions that govern our C++ code. The term Style is a bit of a misnomer, since these conventions cover far more than just source file formatting.

Most open-source projects developed by Google conform to the requirements in this guide.

Note that this guide is not a C++ tutorial: we assume that the reader is familiar with the language. 
```

C++ 是众多谷歌开源项目的主力语言之一。 众所周知，该语言拥有很多强大的特性，但同时也带来相应的复杂度，这些（强大的特性）反而会将代码变得更加容易出 bug 且难读难维护。

这份指南的目标是管理上述的复杂度——通过详细地讨论在写 C++ 代码时有哪些能做的，哪些不能做。这样好让代码库变得可管理的同时也能够让编码者有效率地使用 C++。

风格（style），也称可读性（readability），是 “治理” C++ 源码的惯例，传统。风格这一词有点歧义，因为这些惯例，传统远不止排版。

绝大多数谷歌开源项目都遵从本风格指南中的规定。

注意，这份指南不是教程，我们假设读者已熟悉语言。

## 0.1 风格指南的目标
```text
Why do we have this document?

There are a few core goals that we believe this guide should serve. These are the fundamental whys that underlie all of the individual rules. By bringing these ideas to the fore, we hope to ground discussions and make it clearer to our broader community why the rules are in place and why particular decisions have been made. If you understand what goals each rule is serving, it should be clearer to everyone when a rule may be waived (some can be), and what sort of argument or alternative would be necessary to change a rule in the guide.

The goals of the style guide as we currently see them are as follows:
```

为什么我们要有这份文档？

这里有一些我们认为风格指南应该遵从的核心目标。这些是构成每个条例的核心原因。把这些核心目标放在正文之前，我们希望引发广泛讨论，向我们的广大社区说明白，为什么某个条例存在，为什么我们做出了一些特殊的决定。而且也必须向所有人说明，什么时候条例也许（可以）能被忽略，什么样的论点或方法可以替代本风格指南中的条例。

风格指南的核心规则如下：

### 每一个条例都该“尽职尽责”
```text
Style rules should pull their weight

The benefit of a style rule must be large enough to justify asking all of our engineers to remember it. The benefit is measured relative to the codebase we would get without the rule, so a rule against a very harmful practice may still have a small benefit if people are unlikely to do it anyway. 

This principle mostly explains the rules we don’t have, rather than the rules we do: for example, goto contravenes many of the following principles, but is already vanishingly rare, so the Style Guide doesn’t discuss it.
```

规则带来的益处必须大到可以规定所有人去记住它。益处则通过以当前代码库为基础对比遵循和不遵循而衡量出来，所以一个规则即使反对了一个非常糟糕实践，但是人们都不太可能会做，这样只会产生有限的益处。

这一原则主要解释了为什么一些规则我们没有包含，而不是包含了一些规则：比如  `goto`  违反了接下来很多的原则， 但是已经近乎绝迹，所以风格指南没有讨论它。

###  为读者而非写者优化
```text
Optimize for the reader, not the writer

Our codebase (and most individual components submitted to it) is expected to continue for quite some time. As a result, more time will be spent reading most of our code than writing it. We explicitly choose to optimize for the experience of our average software engineer reading, maintaining, and debugging code in our codebase rather than ease when writing said code. 

"Leave a trace for the reader" is a particularly common sub-point of this principle: When something surprising or unusual is happening in a snippet of code (for example, transfer of pointer ownership), leaving textual hints for the reader at the point of use is valuable (std::unique_ptr demonstrates the ownership transfer unambiguously at the call site). 
```

我们当前代码库（大部分独立公司使用到的）预期要维护很长时间，导致了更多时间是花在读而非写上。我们明确地选择为我们的标准水平开发读者优化，维护和调试而非为写时方便优化。

给读者留下痕迹只是这一原则下非常普通的要求，当一小段代码干了会让人吃惊或者不寻常的事，留下一小段提示会非常有益（比如将 raw 指针传递给函数的 `std::unique_ptr` 参数时用时会隐式转移所有权）

### 与现有代码库保持一致性
```text
Be consistent with existing code

Using one style consistently through our codebase lets us focus on other (more important) issues. Consistency also allows for automation: tools that format your code or adjust your #includes only work properly when your code is consistent with the expectations of the tooling. 

In many cases, rules that are attributed to "Be Consistent" boil down to "Just pick one and stop worrying about it"; the potential value of allowing flexibility on these points is outweighed by the cost of having people argue over them. 

However, there are limits to consistency; it is a good tie breaker when there is no clear technical argument, nor a long-term direction. It applies more heavily locally (per file, or for a tightly-related set of interfaces). 

Consistency should not generally be used as a justification to do things in an old style without considering the benefits of the new style, or the tendency of the codebase to converge on newer styles over time.
```

在现有代码库中使用同一种风格让我们可以把注意力放在其它 (更重要的) 事上。一致性也会让自动化成为可能，只要你的代码符合自动工具的预期就可以用工具排版或者调整 include 的次序。

在大部分情况下，条例是一致性导致的结果，每个条例说到底就是 “选一个（从众多可行的规则中），不要再想它了” 。在这些条例的方面，允许自由的潜在价值远远小于人们为它而争辩的成本。

然而， 一致性还是有它的局限， 只有在没有明显技术争议和特定的长期发展方向情况下，保持一致性才会成为主要目标。

一致性因项目，文件甚至一组精密关联的接口而异，所以一致性不应该被泛泛地拿来当做墨守成规的理由 或者 拿来当作现有代码库风格发展的目标。

###  当合适的时候才与更开放的 C++ 社区保持一致
```text
Be consistent with the broader C++ community when appropriate

Consistency with the way other organizations use C++ has value for the same reasons as consistency within our code base. 

If a feature in the C++ standard solves a problem, or if some idiom is widely known and accepted, that's an argument for using it. However, sometimes standard features and idioms are flawed, or were just designed without our codebase's needs in mind. In those cases (as described below) it's appropriate to constrain or ban standard features.

In some cases we prefer a homegrown or third-party library over a library defined in the C++ Standard, either out of perceived superiority or insufficient value to transition the codebase to the standard interface.
```

与其他组织保持一致 C++ 风格的理由与我们在现有代码库上保持一致风格是一样的。

如果某一个 Standard 特性解决了一个问题或者是某种 idiom 广为人知且被接受，这就没有理由不用它。但是，有时候 Standard特性 或 idiom 是有缺憾的 或者 是在没有考虑我们的代码库基础上设计出来。在这些情况下，限制或禁止一些特性是合适的。

在某些情况下，我们更倾向于使用自己开发或者第三方库而不是标准库，这是出于感知型优越性，将现有代码库接口转换为标准接口是价值有限的。

> 谷歌教你说词 低情商：我们太厉害了 高情商：出于感知型优越性 

### 避免惊奇或危险的“构造”
```text
Avoid surprising or dangerous constructs

C++ has features that are more surprising or dangerous than one might think at a glance. Some style guide restrictions are in place to prevent falling into these pitfalls. 

There is a high bar for style guide waivers on such restrictions, because waiving such rules often directly risks compromising program correctness. 
```

C++ 有一些比看上去更加惊奇或危险的特性，某些条例就是为了防止陷入这些陷阱。

忽略这些条例的门槛是很高的，因为这会直接给很多代码带来风险。

### 避免大部分 C++ 程序员都觉得难以维护的“构造”
```text
Avoid constructs that our average C++ programmer would find tricky or hard to maintain

C++ has features that may not be generally appropriate because of the complexity they introduce to the code. 

In widely used code, it may be more acceptable to use trickier language constructs, because any benefits of more complex implementation are multiplied widely by usage, and the cost in understanding the complexity does not need to be paid again when working with new portions of the codebase. When in doubt, waivers to rules of this type can be sought by asking your project leads. 

This is specifically important for our codebase because code ownership and team membership changes over time: even if everyone that works with some piece of code currently understands it, such understanding is not guaranteed to hold a few years from now.
```

C++有一些特性给代码带来了太多复杂性，因此并没有没有对大部分情况都合适。

在被广泛使用的代码（基础代码）中，使用这些复杂构造可能更合适，因为任何一点复杂实现带来的好处都会因为广泛的用途而放大，而且在编写新代码时不用再对这些代码付出理解成本。因这条规则而疑惑时，最好咨询下项目管理者。

这个条例对于我们的现存代码库是非常重要的，因为随时间人员流动多，即使现在所有人对于某个部分代码都理解了，也很难保证未来几年仍然理解。

### 注意我们的代码规模
```text
Be mindful of our scale

With a codebase of 100+ million lines and thousands of engineers, some mistakes and simplifications for one engineer can become costly for many. 

For instance it's particularly important to avoid polluting the global namespace: name collisions across a codebase of hundreds of millions of lines are difficult to work with and hard to avoid if everyone puts things into the global namespace.
```

在 1亿+ 行代码和数千工程师的基础上，一个工程师的错误和过度简化都会导致很大的代价。

列如，避免全局命名空间污染尤为重要：如果每个人都在全局命名空间下定义些对象，那么名称冲突在 1亿+ 行代码下就会难以忍受而且难以避免。

### 必要时让位于性能
```text
Concede to optimization when necessary

Performance optimizations can sometimes be necessary and appropriate, even when they conflict with the other principles of this document.
```

某些时候，性能优化是必要且合适的，即使与一些原则冲突时。

### 最后
```text
The intent of this document is to provide maximal guidance with reasonable restriction. 

As always, common sense and good taste should prevail. By this we specifically refer to the established conventions of the entire Google C++ community, not just your personal preferences or those of your team. 

Be skeptical about and reluctant to use clever or unusual constructs: the absence of a prohibition is not the same as a license to proceed. Use your judgment, and if you are unsure, please don't hesitate to ask your project leads to get additional input.
```

本文意图提供最大的指导和合理的限制。

如往常一样，常识和好的风格需要提倡。对此，我们主要参考了整个Google C++社区的常规惯例而不只是你个人或团队的喜好。

对一切聪明的，不常规的构造保持质疑和审慎的态度：毕竟 没有明文禁止 和 要走批准流程的条例 还是不一样的。自己判断，如果不确定，请向项目领导获取额外的建议。

# 1. 头文件
## 1.1 自给自足
- 自给自足 ： 可以作为第一个头文件进行编译, 任何头文件应该以 `.h` 结尾，且与一个`.cc` 源文件相关联（单元测试源文件除外）
- 模板与内联函数的声明和定义 都该放在同一个头文件中，其次舍弃过去可能使用的做法：定义放在`-inl.h` 文件中然后头文件中再包含
- 如果模板为所有相关模板参数显式实例化，或本身就是某类的一个私有成员，那么它就只能定义在实例化该模板的 `.cc` 文件里
- 只用作纯文本插入（文件中的特殊位置，不一定是文件开头）， 非自给自足， 没有头文件保护， 没有需要首先包含的头文件放在`.inc` 文件

## 头文件保护
- `<PROJECT>_<PATH>_<FILE>_H_`

## 只包含你所用的
- 如果源文件或头文件用到某个其他地方定义的 symbol，应当直接包含 恰好用于提供该声明或定义的文件，而不该因为其他原因包含其他文件 
- 不依赖头文件相互包含的关系，这可以使得用户去除不必要的头文件而不发生错误，比如`foo.cc`要包含 `bar.h` 则应当直接包含它，即使 `foo.h` 包含了 `bar.h`

## 前置声明
> 个人认为这里的头文件类似 \<iosfwd\> , PIMPL 可以使用，环形声明可以使用模板替代

- 尽可能地避免使用 前置声明 而是 包含头文件
- 优点：前置声明节省编译时间不用再处理头文件包含，防止头文件改动而重新编译
- 缺点：
    - 节省编译时间所带来的问题即跳过重新编译的过程，隐藏了依赖关系
    - 难以让自动分析工具判断实际定义 symbol 的模块在哪
    - 前置声明不能随同后续定义的改动而产生错误，比如：前置声明的函数或模板无法与后续增加了函数型参或模板型参， 把某个对象标识符放入命名空间中等同步
    - 来自命名空间 std:: 前置声明标识符会产生未定义情况
	- 前置声明和头文件在一般情况下难以判断好坏，在极端情况下前置声明会产生歧义（比如隐藏继承关系）
	- 有时比单一行的 include 冗长
	- 使用成员对象的指针会使得 代码复杂 且 增加时间成本

## 内联函数
- 只对10行或更少的函数定义
- 谨慎对构造和析构函数内联
- 不要对包含循环的函数进行内联（除非循环很少用到），虚函数和递归函数即使内联也不会实际内联
- 虚函数内联的主要原因则是想把它的函数体放在类定义内, 主要为了 图个方便 或 当作文档描述其行为, 比如该虚函数是精短的存取函数

## 包含的名称和顺序
- 顺序：关联的头文件 | C库 | C++库 | 其他库头文件 | 项目头文件 | 额外的条件编译 （ ‘ | ’ 代表空行）
- 包含项目头文件时不要包含相对路径， 在同一层级下对头文件进行字母顺序排序，同时不要因为头文件关系省略一些头文件（起到明示作用）
```c++
// 比如 foo.cc 具体如下
#include "foo.h"  //  如果出错， 与维护文件人有关的信息会最先呈现出来

#include <stdlib.h>

#include <algorithm>

#include "other_library.h"
#include "project_library.h"

#ifdef LANG_CXX11
#include <initializer_list>
#endif
```

# 2. 作用域

## 命名空间
- 除非特例，将代码放入命名空间中（也有缺点如迷惑性，冗长）
- 规定 ： 
    - 不使用 using语句（污染命名空间） 和 内联命名空间（主要用于版本控制）
    - 命名空间名称必须唯一，可以是路径
    - 不要在命名空间 std 内声明任何东西，包括标准库的类前置声明，这产生未定义的行为，不可移植
    - 不要在头文件中使用 命名空间别名 除非显式标记内部命名空间使用。因为任何在头文件中引入的命名空间都会成为公开API的一部分。
```c++
//  In the .h file 排除一些头文件或前置声明
namespace mynamespace {  // 范围到文件结尾
// 空一行 不缩进
class MyClass {
 public:
  ...
  void Foo();
};

}   // namespace mynamespace 额外注释


// 在 .h 中使用别名缩短常用的命名空间
namespace librarian {

namespace impl {  // 仅限内部使用

namespace sidetable = ::pipeline_diagnostics::sidetable;
...
}  // namespace impl

inline void my_inline_function() {
  // 限制在一个函数中的命名空间别名
  namespace baz = ::foo::bar::baz;
  ...
}
}  // namespace librarian
```

## 内部链接
- 如果在源文件中的某个对象的定义不会被其他文件所引用，则将他们放入匿名命名空间中来内部链接，或者声明为 static。不要在头文件中使用匿名命名空间和声明变量为static
- 确保无法被其他文件所引用，防止命名冲突

## 非成员函数、静态成员函数和全局函数
- 将非成员函数放入命名空间，尽量不要用裸的全局函数
- 不要用类的静态方法模拟出命名空间的效果，类的静态方法应当和类的实例或静态数据紧密相关
- 非成员函数应尽量不依赖外部变量，应当尽量存在某个命名空间中
- 必须定义非成员函数, 又只是在 .cc 文件中使用它，可以使用内部链接方法

## 局部变量
- 尽量减少函数变量的作用域，尽量延后定义，一定初始化。
- `while (const char* p = strchr(str, '/')) str = p + 1;` 减少作用域，（对象则例外要比较构造和析构成本高还是赋值成本高）

## 静态和全局变量

- 规则 ： 
    - 禁止 非Trivial destructor 的 静态存储周期 对象
    - 静态函数局部对象可以使用动态初始化 但是不鼓励 对类静态数据成员 或 命名空间中定义的对象 进行动态初始化（有特列）
    - 根据经验，全局变量满足（上述）条件，可以被声明为constexpr（单独地来说）




# 3. 类

# 4. 函数

# 5. Google特殊工具

# 6. 其他特性

# 7. 命名约定
## 7.1 通用命名规则
- 不要为了节省横向空间而使用缩写, 除非缩写广为人知且在 wiki 上能找到, 也不要删除词中的字母
- 命名的描述性随着作用域扩大而增强, 如 几行的作用域可以用 n 作为控制变量, 而成员变量则不可以
- 驼峰命名法中, 缩写词应当做一个单词, 首字母大写, 其余不大写
- 模板参数中类型参数遵从类型命名规则, 非类型参数遵从变量命名规则

## 7.2 文件名
- 小写 + 下划线且足够特殊, 如`my_useful_class.cc`
- 拓展名为`.cc` 或 `.h` , 且 xxx.cc , xxx.h, class xxx 应该一一配对
- 只被包含的文件应以 .inc 为拓展名
- 不要与 /usr/include 下文件名重复

## 7.3 类名
- 词首字母大写, 无下划线 `ClassName`
- 适用 类, 结构体, 类型别名, 枚举, 模板类型参数

## 7.4 变量
- 小写 + 下划线 :  `my_variable`
- 类数据成员, 后加下划线 :  `my_member_variable_`
- 结构体数据成员, 当作一般变量 :  `my_struct_variable`
- 常量, 静态存储期的变量, 全局变量, 前加k, 词首字母大写 :  如 `kMyConstName`, 存在 `kExample_0_0` 以下划线做区分

## 7.5 函数
- 每个词首字母大写, 无下划线 :  `FuncName()`
- 对于类或命名空间作用域中暴露出来的常量也要用函数的命名规则, 因为要让他们是跟着 API 的, 因此要让他们看上去像函数一样使用
- get, set 成员函数要与数据成员对应 : `my_variable()` , `set_my_variable()`

## 7.6 命名空间
- 小写 + 下划线, 不要过度使用缩写
- 顶层的命名空间要参照项目名称, 内部命名空间取名要独特以防止冲突, 尤其对于在同一命名空间下工作的不同团队
- 注意避免内嵌的命名空间与已被广泛使用的顶层命名空间 "撞名" , 因为名字的查找规则会产生奇怪的构建问题尤其是 : 不要给内嵌命名空间命名为 std
- 命名空间中的代码, 应当存放于和命名空间的名字匹配的文件夹或其子文件夹中, 注意命名空间不能过深

## 7.7 枚举
- 枚举值遵循常量命名法
- 历史遵循过宏命名法

## 7.8 宏	
全部大写, 以下划线分隔

## 7.9 例外
- 如果你要对一个类似与已存在的 C/C++ 实体命名, 你可以仿照存在的命名风格如 : 
- bigopen() : 参照 open() 函数
- uint : 参照类型别名typedef
- bigpos : 参照 pos 类或结构体
- sparse_hash_map : 参照 STL 容器命名
- LONGLONG_MAX : 参照 INT_MAX 宏

# 8. 注释
## 8.1 关于源文件的注释
### 关于版权与作者
- 版权声明 (比如, Copyright 2008 xxxx Inc.) 
- 许可证 (比如, Apache 2.0, BSD, LGPL, GPL)
- 作者 (标识文件的原始作者)
### 关于文件内容
- 如果头文件包含很多抽象, 文件注释应当含有这些抽象的关系的简要介绍, 1 到 2 句就够了, 对于抽象的各个部分详细内容属于类注释而非文件注释
- 不要在 .cc 文件中复制 .h 的注释, 没有意义

## 8.2 关于类的注释
- 类是做什么的以及 正确使用方式 (可用一小段代码展示出来)
- 要特别注意说明类在多线程环境下相关假设 : 类对象是否可以被多线程访问, 访问规则和常量的使用方式
- .h 文件要对所声明的类的功能和用法作简单说明
- .cc 文件通常包含了更多的实现细节或算法技巧
```c++
// Iterates over the contents of a GargantuanTable.
// Example:
//    std::unique_ptr<GargantuanTableIterator> iter = table->NewIterator();
//    for (iter->Seek("foo"); !iter->done(); iter->Next()) {
//      process(iter->key(), iter->value());
//    }
class GargantuanTableIterator {
  ...
};
```
## 8.3 关于函数的注释
- 函数声明的注释描述函数的用法
- 函数定义的注释描述函数的具体操作

### 函数声明
- 简单且显而易见的函数声明与定义不用注释
- 使用叙述式 (第三人称) 说明函数功能
- 函数的输入输出是什么, 可以在注释中用 反引号 标出方便文档生成工具识别
- 引用参数的生命周期, 即函数调用期间对象是否需要保持引用参数, 是否会释放这些参数
- 函数开辟的内存是否要由调用者释放
- 参数是否可以为 NULL
- 是否存在函数使用上的性能隐患
- 如果函数是可重入的, 其同步前提是什么
```c++
// Returns an iterator for this table, positioned at the first entry
// lexically greater than or equal to `start_word`. If there is no
// such entry, returns a null pointer. The client must not use the
// iterator after the underlying GargantuanTable has been destroyed.
//
// This method is equivalent to:
//    std::unique_ptr<Iterator> iter = table->NewIterator();
//    iter->Seek(start_word);
//    return iter;
std::unique_ptr<Iterator> GetIterator(absl::string_view start_word) const;
```

- 避免不言而喻的注释, 比如对于 override 不要重复注释相同的功能(大部分情况不需要额外注释)
- 对于构造, 析构函数来说其功能不言而喻, 但要对于构造的参数(比如是否接管了指针的所有权)和析构的清理过程要有说明, 对于平凡情况可以不必注释

### 函数定义
- 注释说明函数功能和实现要点, 比如编程技巧, 实现的大致步骤, 或解释如此实现的理由, 为什么前半部分要加锁而后半部分不需要
- 不要 从 .h 文件或其他地方的函数声明处直接复制注释, 简要重述函数功能是可以的, 但注释重点要放在如何实现上

## 8.4 关于变量的注释
- 大部分变量的名字足够解释, 但是有些情况需要额外注释

### 成员变量
- 对于任何变量如果不能通过名字和类型描述清除, 必须额外注释 比如 : 特殊值, 与其他成员的关系, 特殊的生命周期
- 对于可以接受 nullptr 或 -1 的警戒值, 须加以说明
### 全局变量
- 所有全局变量都需要明确注释
- 描述为他们是什么, 用于什么, 为什么需要

## 8.5 关于实现的注释
- 在实现中需要对 有技巧性的, 隐晦的, 有趣的或重要的部分进行注释
- 对于复杂的代码块需要头注释 
- 对于特殊的行语句, 需要行注释, 行注释行尾空两格

## 8.6 关于函数参数的注释
- 对于被多个函数用到的字符串常量可以用常量替代, 用名字解释意义
- 同理, 对于布尔值, 可以通过枚举类替换
- 对于多个选项参数可以抽象为一个选项类, 有助于减少参数数量, 且参数的意义可以通过 setter 和 类常量表达出来
- 对于复杂的表达式尽量用命名的变量替换
- 必要的情况需要对参数进行注释
```c++
ProductOptions options;
options.set_precision_decimals(7);
options.set_use_cache(ProductOptions::kDontUseCache);
const DecimalNumber product =
    CalculateProduct(values, options, /*completion_callback=*/nullptr);
```

## 8.7 不要重复注释
- 不要注释代码显而易见的行为, 尤其对于充分理解 C++ 的读者来说
- 要不在高一层次说明为什么这样做, 或者实现自注释
```c++
// (obvious!)
// Find the element in the vector.
if (std::find(v.begin(), v.end(), element) != v.end()) {
  Process(element);
}
// (high level !)
// Process "element" unless it was already processed.
if (std::find(v.begin(), v.end(), element) != v.end()) {
  Process(element);
}

//(self documented !)
if (!IsAlreadyProcessed(element)) {
  Process(element);
}
```

## 8.8 标点符号, 拼写和语法
- 注释应当是可读的文本, 带有正确的大小写和标点符号
- 完整的语句比语句段更有可读性

## 8.9 TODO
- TODO 注释要使用全大写的字符串 TODO, 且在每行开头标明 TODO
- TODO 之后的括号里标明 姓名,有关人员标识, 邮箱, BUG ID等
- 在详情中写下问题出现的环境描述, 具体的修复时间
- DEPRECATED标 记某接口为弃用状态, 放在接口声明前, 需要修改调用点行。
```c++
// TODO(kl@gmail.com): Use a "*" here for concatenation operator.
// TODO(xxxx): xxxx. Fix by YYYY-MM-DD
// DEPRECATED(xxxx): xxxx 
```

# 9. 格式
## 9.1 行长
- 行长不超过80, 例外如下 :
    - 不好分隔的注释如 url 等
    - 超过 80 个字符的字符串常量 (测试用)
    - #include 包含较长的路径
    - 头文件保护可以超过
    - using 申明

## 9.2 非ASCII字符
- 面向用户的文字不应该出现在源码中, 因此在源码中出现非 ASCII 字符的情况少之又少
- 但是在处理其他语言文件或者单元测试代码中会经常出现, 这种时候需要用到 UTF-8 编码
- 可以在字符串中使用 UTF-8 的 
    - 十六进制编码 如 `u8"\xEF\xBB\xBF"`(UTF-8 BOM)
    - 码点编码 如 `u8"\uFEFF"`(UTF-8 BOM)
- 少在源码中出现非 ASCII 字符, 因为编译器不把它识别位 UTF-8 会出现问题
- 不应该使用 char16_t 和 char32_t 因为他们不是为了 UTF-8 而设计的字符类型, 而且也不该使用 wchar_t 除非你要与 Windows API 打交道

## 9.3 缩进
- 只用空格缩进
- 每次缩进 2 个空格

## 9.4 函数声明和定义
- 返回类型和函数名在同一行, 参数尽量在同一行可以根据数量调整
```c++
// 1. 同一行
// 左括号 ( 始终与函数名在同一行, 且与函数名之间没有空格, 与第一个参数没有空格
// 左花括号 { 始终与函数声明的最后一行同行, 右花括号始终独自成行
// 右括号 ) 与 左花括号 { 始终有一个空格
ReturnType ClassName::FunctionName(Type par_name1, Type par_name2) {
  DoSomething();
  ...
}

// 2. 参数对齐
// 所有形参需要对齐
ReturnType ClassName::ReallyLongFunctionName(Type par_name1, Type par_name2,
                                             Type par_name3) {
  DoSomething();
  ...
}
// 如果无法在同一行放下参数需要缩进 4 个空格, 且每行放一个参数
// 如果无法将返回类型与函数名放到一块直接分开, 且不缩进
ReallyReallyReallyReallyReallyReallyLongReturnType 
LongClassName::ReallyReallyReallyLongFunctionName(
    Type par_name1,  // 4 space indent
    Type par_name2,
    Type par_name3) {
  DoSomething();  // 2 space indent
  ...
}

// 3. 参数如果没有在实现中用到, 对于声明和实现都可以直接吞掉参数名(明显的)
// 不明显的参数仍然需要注释
class Foo {
 public:
  Foo(const Foo&) = delete;  // 不可能用到直接忽略
  Foo& operator=(const Foo&) = delete;
};
class Circle : public Shape {
 public:
  void Rotate(double radians) override;  // 有可能用到需要加上参数名
};
void Circle::Rotate(double /*radians*/) {}  // 不明显的被忽略的参数名

// 4. 对于宏 和 Attributes 的拓展应该出现在声明和实现的返回类型前
ABSL_MUST_USE_RESULT bool IsOk();

// 短小的内联函数可以特殊
Foo(int b) : Bar(), baz_(b) {} // 大括号里面是空的话，不加空格。 void Reset()
void Reset() { baz_ = 0; } // 用括号把大括号与实现分开。
```

## 9.5 Lambda 表达式
```c++
// 1. 在一行中的 Lambda
// 捕获列表中 & 与 x 没有空格
// 注意尾置返回类型的写法
int x = 0;
auto x_plus_n = [&x](int n) -> int { return x + n; }

// 2. 多行中的 Lambda
// 注意参数对齐, 函数体和右括号的缩进
std::set<int> to_remove = {7, 8, 9};
std::vector<int> digits = {3, 9, 1, 8, 4, 7, 1};
digits.erase(std::remove_if(digits.begin(), digits.end(), [&to_remove](int i) {
               return to_remove.find(i) != to_remove.end();
             }),
             digits.end());
```

## 9.6 浮点数字面值
- 浮点数字面值一定有小数点, 小数点两边都有数值, 即使用 E 记号也要遵循 (目的是 浮点数字面值和 E 记号的浮点数字面值不与整数字面值搞混)
- 可以将一个整型数的字面值直接赋值给浮点数
- 注意带有 E 记号的字面值一定是浮点数
```c++
float f = 1.0f;
float f2 = 1;   // Also OK
long double ld = -0.5L;
double d = 1248.0e6;
```

## 9.7 函数调用
- 要么一行写完函数调用, 要么在圆括号里对参数分行, 要么参数另起一行且缩进四格
- 如果没有其它顾虑的话, 尽可能精简行数, 比如把多个参数适当地放在同一行里
- 最基本的准则就是可读性至上
```c++
// 一行调用
bool retval = DoSomething(argument1, argument2, argument3);

// 如果同一行放不下, 可断为多行, 后面每一行都和第一个实参对齐
// 左圆括号后和右圆括号前不要留空格：
bool retval = DoSomething(averyveryveryverylongargument1,
                          argument2, argument3);

// 参数也可以放在次行, 缩进四格：
if (...) {
  ...
  ...
  if (...) {
    DoSomething(
        argument1, argument2,  // 4 空格缩进
        argument3, argument4);
  }
```

- 为了可读性尽量不要把每个参数都独立成行, 把多个参数放在同一行以减少函数调用所需的行数, 除非影响到可读性
- 如果一些参数本身就是略复杂的表达式, 且降低了可读性, 那么可以直接创建临时变量描述该表达式, 并传递给函数
```c++
int my_heuristic = scores[x] * y + bases[x];
bool retval = DoSomething(my_heuristic, x, y, z);

// 或者放着不管, 补充上注释
bool retval = DoSomething(scores[x] * y + bases[x],  // Score heuristic.
                          x, y, z);

// 如果某参数独立成行, 对可读性更有帮助的话, 那也可以如此做
// 如果一系列参数本身就有一定的结构, 可以酌情地按其结构来决定参数格式：
// 通过 3x3 矩阵转换 widget.
my_widget.Transform(x1, x2, x3,
                    y1, y2, y3,
                    z1, z2, z3);
```

## 9.8 花括号列表
- 与函数调用的参数列表格式相同
```c++
// 一行下, 花括号与名字之间没有空格
return {foo, bar};
functioncall({foo, bar});
std::pair<int, int> p{foo, bar};

// 与参数的缩进一致
SomeFunction(
    {"assume a zero-length name before {"},
    some_other_function_parameter);
SomeType variable{
    "This is too long to fit all in one line"};

SomeType variable{
    some, other, values,
    {"assume a zero-length name before {"},
    SomeOtherType{  // 子参数的缩进也是一致风格
        "Very long string requiring the surrounding breaks.",
        some, other, values},
    SomeOtherType{"Slightly shorter string",
                  some, other, values}};

// 赋值情况下的缩进
MyType m = {
    superlongvariablename1,
    superlongvariablename2,
    {short, interior, list},
    {interiorwrappinglist,
     interiorwrappinglist2}};
```

## 9.9 条件语句
```c++
// 1. 标准的格式
// 注意 if ( 和 ) { 的空格
// 条件表达式与括号之间没有空格
if (condition) {
  DoOneThing(); 
  DoAnotherThing();
// 对于每个 else if 或 else 都要保持类似函数体的格式
} else if (int a = f(); a != 3) {  
  DoAThirdThing(a);
} else {
  DoNothing();
}

// 2. 例外(历史原因) 的格式, 都是针对简短语句, 没有额外 else 的条件语句
// 个人认为 必须要有 花括号
if (x == kFoo) return new Foo();

if (x == kBar)
  return new Bar(arg1, arg2, arg3);

if (x == kQuz) { return new Quz(1, 2, 3);

// 表达式太长 则 必须添加花括号
if (condition1 &&
    condition2)
  DoSomething();
```

## 9.10 循环 与 switch 语句
```c++
// 1. switch 语句整体需要用 花括号
switch (var) {
// 2. case block 的花括号可有可无, 完全取决于个人喜好
//    用了就要保证一致的风格, 注意 '0:' 之间没有空格, ': {' 之间有空格
  case 0: {  // 2 space indent
    ...      // 4 space indent
    break;
  }
  case 1: {
    ...
    break;
  }
  default: {
// 3. 如果有没有处理的枚举值则必须要有 default 标签
//    如果断定 default 永远没有执行到需要加上 assert(false)
    assert(false);  
  }
}
```

- 需要在不明显的 fall-through 情况下明确注释出来
```c++
switch (x) {
  case 41:  // 1. 空语句标签没有必要额外注明
  case 43:
    if (dont_be_picky) {
      // 2. 额外注明 fall through
      // ABSL_FALLTHROUGH_INTENDED;
    } else {
      CloseButNoCigar();
      break;
    }
  case 42:
    DoSomethingSpecial();
    // ABSL_FALLTHROUGH_INTENDED;
  default:
    DoSomethingGeneric();
    break;
}
```

- 单语句的循环 花括号可有可无 (个人倾向加上)
- 空语句的循环 需要用以下方式标明 (个人倾向第二种)
```c++
while (condition) {
  // 注释标明
}
for (int i = 0; i < kSomeNumber; ++i) {}  // 无空格的一对花括号标明
while (condition) continue;  // continue; 标明
```

- for 语句在每个分号之后有一个空格
```c++
for ( ; i < 5; ++i)
```

## 9.11 指针引用表达式
- `.`, `->`, `*`, `&` 之后没有空格
- 修饰符是否紧贴标识符都可以 (个人倾向后置)
```c++
// 紧贴标识符, 空格前置
char *c;
const std::string &str;
int *GetPointer();
std::vector<char *>

// 不紧贴标识符, 空格后置
char* c;
const std::string& str;
int* GetPointer();
std::vector<char*>  // 在模板参数中, 后置的空格被忽略
```

- 注意, 上述风格要与原有的文件保持一致
- 可以在一行定义多个变量, 但是其中不能有任何修饰符
```c++
// 可以定义多个变量
int x, y;

// 不允许有修饰符出现, 且风格需要统一
int x, *y;  
int* x, *y;  
```

## 9.12 布尔表达式
- 如果一个布尔表达式超过 标准行宽, 断行方式要统一一下
- 可以让逻辑运算符置于行末来分行
- 必要加 () 增加可读性, 但是不要滥用
- 不要用词语形式的 and 和 compl
```c++
if (this_one_thing > this_other_thing &&
    a_third_thing == a_fourth_thing &&
    yet_another && last_one) {
  ...
}
```

## 9.13 返回值
```c++
// 在不需要的情况下不要加 '( )'
return result;

// 对于布尔表达式 或者 赋值语句可以加上
return (some_long_condition &&
        another_condition);
return (x = a);
```

## 9.14 变量与数组初始化
- 可以使用 `=` , `()` , `{}`
```c++
int x = 3;
int x(3);
int x{3};
std::string name = "Some Name";
std::string name("Some Name");
std::string name{"Some Name"};
```

- 存在 std::initializer_list 的构造函数时需要注意, 非空列表会优先选择此构造函数, 而空列表会优先选择默认构造函数, 如果要确保调用不含有列表的构造函数, 使用 `()` 而非 `{}`
- 列表初始化会防止窄化转化发生
```c++
std::vector<int> v(100, 1);  // A vector containing 100 items: All 1s.
std::vector<int> v{100, 1};  // A vector containing 2 items: 100 and 1.
```

## 9.15 预处理命令
```c++
// 置于行首, 不缩进
  if (lopsided_score) {
#if DISASTER_PENDING      
    DropEverything();
// 没有必要加空格
# if NOTIFY               
    NotifyClient();
# endif
#endif
    BackToNormal();
  }
```


## 9.16 类
- 访问控制符依次序是 public, protected, private
- 访问控制符每个都缩进 1 个空格
- 遵照上述的声明顺序
```c++
// 注意继承的格式 : 前后都有空格, 两个类名在同一行
class MyClass : public OtherClass {
 public:      // 访问控制符每个都缩进 1 个空格
  MyClass();  // 正常语句缩进 2 个空格
  explicit MyClass(int var);
  ~MyClass() {}

  void SomeFunction();
  void SomeFunctionThatDoesNothing() {
  }

  void set_some_var(int var) { some_var_ = var; }
  int some_var() const { return some_var_; }
// 访问控制符之间应当隔一行, 小类可以忽略这条规定, 访问控制符整体前后不应留下空行

 private:
  bool SomeInternalFunction();

  int some_var_;
  int some_other_var_;
};
```

## 9.17 构造函数
- 初始化列表应当与构造函数在同一行, 或者 以 4 格缩进
```c++
// 同一行
MyClass::MyClass(int var) : some_var_(var) {
  DoSomething();
}

// 在 冒号前缩进 4 格
MyClass::MyClass(int var)
    : some_var_(var), some_other_var_(var + 1) {
  DoSomething();
}

// 如果 初始化列表会跨越多行, 则每个参数独占一行并与第一个参数对齐
MyClass::MyClass(int var)
    : some_var_(var),             // 4 格缩进
      some_other_var_(var + 1) {  // 对齐
  DoSomething();
}

// 合适的情况下, 右括号与左括号可以在同一行
MyClass::MyClass(int var)
    : some_var_(var) {}
```

## 9.18 名字空间
- 命名空间中的内容不要增加额外的缩进层次
- 嵌套命名空间时，每命名空间都独立成行

## 9.19 水平留白
- 注意每行都应当没有 空格后缀
### 一般情况
```c++
void f(bool b) {  // ) 与 { 之间始终有空格
  ...
int i = 0;  // 分号前没有空格

// 参数列表与内容之间的空格可有可无
int x[] = { 0 };
int x[] = {0};

// 继承列表和初始化列表中的 : 两旁都应该有空格
class Foo : public Bar {
 public:
  Foo(int b) : Bar(), baz_(b) {}  // 直接没有空格
  void Reset() { baz_ = 0; }  // 短小的内联函数的 block 之间有空格
  ...
```

### 条件与循环
```c++
if (b) {          // 注意 if 与 { 之间的空格
} else {          // 注意 else 两边的空格
}
while (test) {}   // 空语句块中间没有空格, 可以与条件语句放在同一行, 注意之间的空格
switch (i) {
for (int i = 0; i < 5; ++i) {

// 也可以在 条件与循环的括号中增加空格, 但是请保持一致风格
switch ( i ) {
if ( test ) {
for ( int i = 0; i < 5; ++i ) {
    
// 第一个空条件需要有一个空格
for ( ; i < 5 ; ++i) {
  ...

// rang-for 语句中的 分号两旁都要有空格
for (auto x : counts) {
  ...
}
switch (i) {
  case 1:         // 标签与分号之间没有空格
    ...
  case 2: break;  // 如果只有一个语句, 可以直接与标签放在同一行, 注意之间有空格
```

### 操作符
```c++
// 赋值运算符之间有空格
x = 0;

// 其他二元运算符之间也需要有空格
// 除法的空格可以去掉
// 括号与括号内容之间没有空格
v = w * x + y / z;
v = w*x + y/z;
v = w * (x + z);

// 一元运算符与操作数没有空格
x = -5;
++x;
if (x && !y)
  ...
```

### 模板和类型转换
```c++
// `<...>`, `vector<`, `>(` 之间都没有空格
std::vector<std::string> x;
y = static_cast<char*>(x);

// char * 之间的空格是允许的, 但要保持一致
std::vector<char *> x;
```

- 不在万不得已, 不要使用空行
- return; 不是 return ;  没必要可以省略 return


## 9.20 垂直留白
- 减少空行的使用, 没有必要不要使用空行, 对空行的使用要保持吝啬, 基本的原则是一个屏幕上呈现的代码行数越多, 了解程序流程就越简单
- 尤其注意在两个函数之间不要使用超过一个以上的空行, 函数体开头与结尾不要用空行分隔
- 在代码块中的空行应当发挥一个语句段落的作用, 区分两种差别过大想法或者过程
- 空行使用的某些通用规则如下
    - 函数体内开头或结尾的空行可读性微乎其微
    - 在多重 if-else 块里加空行或许有点可读性
    - 在注释行与代码行之间增加空行可以增加可读性, 因为注释行的增加意味着另一种思想的开始, 空行有助于区分
    - 命名空间内容与注释之间的空行有助于区分内容与命名空间结构, 尤其当命名空间的第一个声明语句有注释行的时候, 这是上述规则的一个特例

# 10. 例外
## 10.1 不符合规范的代码
- 对于现有不符合既定编程风格的代码可以网开一面
- 当你修改使用其他风格的代码时, 为了与代码原有风格保持一致可以不使用本风格,  如果不放心, 可以与代码原作者或现在的负责人员商讨
- 记住, 一致性 也包括原有的一致性

## 10.2 Windows 代码*
如果你习惯使用 Windows 编码风格, 这儿有必要重申一下某些你可能会忘记的指南:

- 不要使用匈牙利命名法 (比如把整型变量命名成 iNum). 使用 Google 命名约定, 包括对源文件使用 .cc 扩展名.
- Windows 定义了很多原生类型的同义词 (YuleFox 注: 这一点, 我也很反感), 如 DWORD, HANDLE 等等. 在调用 Windows API 时这是完全可以接受甚至鼓励的. 即使如此, 还是尽量使用原有的 C++ 类型, 例如使用 const TCHAR * 而不是 LPCTSTR.
- 使用 Microsoft Visual C++ 进行编译时, 将警告级别设置为 3 或更高, 并将所有警告(warnings)当作错误(errors)处理.
- 不要使用 #pragma once; 而应该使用 Google 的头文件保护规则. 头文件保护的路径应该相对于项目根目录 (Yang.Y 注: 如 #ifndef SRC_DIR_BAR_H_, 参考 #define 保护 一节).
- 除非万不得已, 不要使用任何非标准的扩展, 如 #pragma 和 __declspec. 使用 __declspec(dllimport) 和 __declspec(dllexport) 是允许的, 但必须通过宏来使用, 比如 DLLIMPORT 和 DLLEXPORT, 这样其他人在分享使用这些代码时可以很容易地禁用这些扩展.

然而, 在 Windows 上仍然有一些我们偶尔需要违反的规则:

- 通常我们 禁止使用多重继承, 但在使用 COM 和 ATL/WTL 类时可以使用多重继承. 为了实现 COM 或 ATL/WTL 类/接口, 你可能不得不使用多重实现继承.
- 虽然代码中不应该使用异常, 但是在 ATL 和部分 STL（包括 Visual C++ 的 STL) 中异常被广泛使用. 使用 ATL 时, 应定义 _ATL_NO_EXCEPTIONS 以禁用异常. 你需要研究一下是否能够禁用 STL 的异常, 如果无法禁用, 可以启用编译器异常. (注意这只是为了编译 STL, 自己的代码里仍然不应当包含异常处理).
- 通常为了利用头文件预编译, 每个每个源文件的开头都会包含一个名为 StdAfx.h 或 precompile.h 的文件. 为了使代码方便与其他项目共享, 请避免显式包含此文件 (除了在 precompile.cc 中), 使用 /FI 编译器选项以自动包含该文件.
- 源头文件通常命名为 resource.h 且只包含宏, 这一文件不需要遵守本风格指南.

- 提高 warning 级别`-Werror -Wall -Wextra -pedantic`
- 使用 /FI 编译器选项以自动包含要编译的文件