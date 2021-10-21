# 1. 概述 
- 泛型算法不会改变容器的元素个数, 但是会改变元素的值和次序, 同时依赖元素的类型的操作
- 头文件一般为 `<algorithm> <numeric>`

## 算法形参模式
|算法型参模式|解释|
|---|---|
|alg(b,e,args)       |[b,e)表示范围|
|alg(b,e,pre)        |pre表示谓词|
|alg(b,e,dest,args)  |dest表示输出起始位置|
|alg(b,e,b2,args)    |b2表示输第二个范围起始位置|
|alg(b,e,b2,e2,args) |[b2,e2)表示第二个范围|

## 算法命名模式

|算法命名模式|解释|
|---|---|
|alg_if(b,e,pre)    |用if表示存在谓词形参|
|alg_copy(b,e,dest) |用copy表示将结果拷贝到dest中|

# 2. 算法列表

|算法参数|返回值|注意事项|
|---|---|---|
|find(cbit, ceit, val)            |返回 target_it/ceit        |依赖==, 有find_if, find_not_if|
|count(cbit, ceit, val)           |返回 val_num               |依赖==, 有count_if|
|accumulate(cbit, ceit, init)     |返回 acc_num               |依赖+, init|
|equal(cbit, ceit, cbit1)         |返回 is_equal              |依赖==, 有重载|
|fill(bit, eit, val)              |返回 void                  |依赖=, 有fill_n(back_inserter, 返回eit)|
|copy(bit,eit,bit1)               |返回 eit1                  |依赖=, 有copy_if, copy_backward, copy_n|
|replace(bit,eit,val1,val2)       |返回 last_target_eit       |依赖=, 有replace_if, replace_copy|
|sort(bit, eit, bpre)             |返回 void                  |依赖</bpred, 有 stable_sort, |
|partition(bit, eit, upre)        |返回 first_range_eit       |依赖upred, 有stable_partition |
|unique(bit,eit)                  |返回 nodup_range_eit       |依赖==|
|for_each(bit, eit, pre)          |返回 pred                  |依赖pred|
|transform(bit, eit, bit1, pre)   |返回 transformed_range_eit |依赖pred|

# 3. lambda表达式
- 谓词: 可调用表达式, 返回可作为条件的值, 按谓词的参数个数可分为一元谓词和二元谓词 
- 可调用表达式: 调用调用对象的表达式, 调用对象包含函数, 函数指针, 重载调用运算符的类和 lambda 表达式
- lambda 表达式: 表示一个可调用代码单元, 一个未命名的内联函数
```c++
auto it = [capture_list] (parameter_list) mutable -> return_type {....};
// 定义一个有名的 lambda 对象, 其中 lambda 由捕获列表, 形参列表, 置尾返回类型, 函数体构成
auto it = [] { return 42;};
// 最简洁写法 省略形参列表 -> 空参
//          省略返回类型 -> 根据返回值推测返回类型 (也可能是void)
```

- lambda 不含有默认实参, 实参与型参数目必须相同
- lambda 只需要捕获局部指明的变量, static和函数体外对象不用捕获
- lambda 表达式的实质: 
```c++
auto it = [sz1, &sz2] (int a, int b) mutable -> return_type { return a + b + sz1 + sz2; };
// 等价为
class Lambda {
  Lambda(int sz1, int &sz2) : sz1_(sz1), sz2_(sz2) {}
  
  // mutable可以使值捕获改变原来的值
  int operator(int a, int b) { return a + b + sz1_ + sz1_; }
  // 没有 mutable 修饰则默认函数调用为 const (原因 是要保证每次调用 lambda 输出结果要一致)
  // int operator(int a, int b) const { return a + b + sz1_ + sz1_; }

 private:
  int sz1_;
  int &sz2_;
};
auto it = Lambda anonymous(sz1, sz2);
// 关于值捕获: lambda 定义时已经对 值捕获对象 进行了拷贝, 后续捕获对象的更改不改变 lambda 捕获的值
// 关于引用捕获: 捕获对象的生存周期影响 lambda 的使用, 当 lambda 作为对象返回时(改变作用域), 不能含有引用捕获 
//             尽量避免捕获指针或者引用
```

|捕获形式|捕获规则|
|---|---|
|\[&var1,var2...]   |明确指定每个捕获形式|
|\[&/=]             |默认捕获变量变量为引用捕获或值捕获|
|\[this]            |引用捕获|
|\[&,var1,var2...]  |默认捕获变量变量为引用捕获, var1, var2必须为值捕获|
|\[=,&var1,&var2...] |默认捕获变量变量为值捕获, var1, var2必须为引用捕获|

# 4. 参数绑定
- bind 函数: 定义在`<functional>`中, 接受可调用对象, 生成新的可调用对象, 对参数进行了转换
- 站位符\_n: 定义在 std::placeholders 中, 代表新的调用对象的第 n 个参数
```c++
auto f = bind(func_name, a, b, _2, c, _1);
auto f_ref = bing(func_name, ref(a), cref(b), _2, c, _1);

f(x, y); 
// 等价 调用
func_name(a, b, y, c, x);

f_ref(x, y);
// 等价 调用
func_name(ParagmType &p1, const ParagmType &p2, ...)
```

# 5. 迭代器
## 插入迭代器
```c++
// 插入迭代器是一种 迭代器适配器, 属于输出迭代器
// 采用 与迭代器相同的操作形式完成 插入操作, 与一般泛型算法适配
// 对 插入迭代器 采用 ++, *() 操作不会改变任何状态, 仍然返回本身
auto it1 = back_insert(vec);          // vec 支持 push_back, 在 vec 后端插入
auto it2 = front_insert(vec);         // vec 支持 push_front, 在 vec 前端插入
auto it3 = inserter(vec, it_begin);   // vec 支持 insert, 在 vec 的 it_begin 之前插入
```

## 流迭代器
```c++
// istream_iterator 是一种 流迭代器, 属于输入迭代器
istringstream iss("1 2 3 4 5 6");
istream_iterator<int> is_end;                        // 默认为 尾后迭代器
istream_iterator<int> is_it(iss);                    // 创建时第一个元素已经准备好, 其余元素懒惰求值
istream_iterator<int> is_it_another(iss);            // 前提为同一类型, 两者都为尾后迭代器或者两者都绑定到同一源上
std::cout << (is_it_another == is_it) << "\n";       // 结果 为 1
while (is_it != is_end && is_it_another != is_end) {
  std::cout << "target is " << *is_it++ << " ";      // 输入迭代器保证 每次递增后, 对应的元素先以求出 
  std::cout << "another is " << *is_it_another++ << " ";
}

// ostream_iterator 是一种 流迭代器, 属于输出迭代器
ostream_iterator<int> os_it(cout);                   // 没有 默认为 尾后迭代器
ostream_iterator<int> os_it(cout, "|");              // 没有 默认为 尾后迭代器, 可以传送一个 C 风格字符数组指针
vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8};
for (const auto &item : vec) {
  // os_it = item;                                   // 简单形式
  *os_it++ = item;                                   // 递增 和 *() 操作 都返回 os_it, 风格推荐与上述保持一致
}
```

## 反向迭代器
```c++
// reverse_iterator 是一种 迭代器适配器, 属于双向迭代器
// vec.rbegin() 指向 最后元素 vec.rend() 指向 首前位置 it++ 移动到前一个位置 it-- 相反

string s("123456");
// it -> 5
auto it = s.crbegin() + 1;

// it.base() 转换为正常迭代器 注意指向的是 it 的后一个位置
// it -> 6
auto it_common = it.base();
```

## 迭代器类别
- 迭代器按照类别分为 5 种, 支持操作由少到多, 从上到下排列(如表), 下层包含上层操作 (输出迭代器例外, 可看作输入迭代器的补集)
- 每个算法要求迭代器的最低操作支持不同, 编译器有时不会给出警告
- 每个容器的迭代器种类也不一样, 如 vector, array, deque, string 为随机, list 双向, forward_list 前向

|迭代器|功能|支持的操作|算法举例|
|---|---|---|---|
|输入迭代器 |只读,单遍扫描,只能递增 |++,var=\*it,var=it->m,==,!= |find,accumulate|
|前向迭代器 |读写,多遍扫描,只能递增 |input&output                |replace|
|双向迭代器 |读写,多遍扫描,能递增减 |input&output,--             |reverse|
|随机迭代器 |读写,多遍扫描,能递增减 |<,<=,>,>=,[],+-             |sort|
|输出迭代器 |只写,单遍扫描,智能递增 |++,\*it=var                 |copy,ostream_iterator|

# 6. 特定容器算法
- list, forward_list其迭代器类别不是随机访问迭代器, 通用版本算法会造成过高代价, 因此定义了几种特殊算法

|特定容器算法|注意事项|
|---|---|
|lst.merge(lst2)         |有序移动合并,依赖<,有pred重载|
|lst.remove(val)         |移除, 依赖==,有remove_if版本|
|lst.reverse()           |反转|
|lst.sort()              |排序,依赖<,有pre重载|
|lst.unique()            |唯一化,依赖==,有pre重载|
|lst.splice(p,lst2)      |将lst2所有元素按原顺序移动到p之前的位置,两个链表类型相同且不是同一个|
|lst.splice(p,lst2,p2)   |将lst2从p2所指元素移动到p之前的位置,可以是相同链表|
|lst.splice(p,lst2,b,e)  |将lst2[b,e)范围元素按原顺序移动到p之前的位置,p不在范围中,可以是相同链表|
|flst.splice_after(args) |移动到p之后, args同上|

```c++
list<int> lst1{1, 2, 3};;
list<int> lst2{100, 101, 102, 103};
lst1.splice(lst1.begin(), lst2);                                // 100 101 102 103 1 2 3
lst1.splice(lst1.begin(), lst2, lst2.begin());                  // 100 1 2 3
lst1.splice(lst1.begin(), lst2, ++lst2.begin(), --lst2.end());  // 101 102 1 2 3
```