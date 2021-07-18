# 1. 顺序容器概述
## 1.1 类型

| 顺序容器 | 是否可变 | 是否随机 | 插入性能高的位置 | 访问方向 |
| --- | --- | --- | --- | --- |
| vector/string | 可变 | 随机 | 尾部 | 任意 |
| deque | 可变 | 随机 | 头尾 | 任意 |
| list | 可变 | 不随机 | 任意 | 双向 |
| forward\_list | 可变 | 不随机 | 任意 | 单向 |
| array | 不可变 | 随机 | - | 任意 |

- 顺序容器 : 提供 逻辑上线性存储 和 随机访问元素的能力, 区别在于访问与添加删除元素的性能
- 特殊的顺序容器 : 
    - `array<int, 10>` : 数组化的容器, 元素数量固定, 指明数量定义更安全, 可以被赋值更易用
    - `forward_list<int>` : 相当于手写链表, 无多余状态

## 1.2 选择依据
1. 需要随机访问, 元素小空间开销重要, 或者只需要头尾插删元素 用 deque 或 vector
2. 需要中间位置插删元素 用 list 或 forward_list
3. 存元素时需要各个位置插入,随后需要随机访问 可以 vector 尾插入后再排序 或 list存入后将元素拷贝到vector中
4. 最终的原则是看访问性能和插删性能哪个占使用情况的主导

# 2. 容器通用操作
## 2.1 类型别名
```c++
std::vector<int> vec {1, 2, 3, 4, 5, 6};
// 引用
std::vector<int>::reference v1 = vec[1];  
// 常量引用
std::vector<int>::const_reference v0 = vec[0];  
// 元素类型
std::vector<int>::value_type v2 = vec[2];  
// 元素数量类型
std::vector<int>::size_type size = vec.size();  
```

## 2.1 迭代器
```c++
std::vector<int> vec {1, 2, 3, 4, 5, 6};

// 两种迭代器 类型别名与获取方法
std::vector<int>::iterator it_begin = vec.begin();
std::vector<int>::const_iterator it_end = vec.cend();

// 左闭右开区间 与 循环判断写法
for ( ; it_begin != it_end; ++it_begin) {
    std::cout << *it_begin << "\n";
}

// 两种逆序迭代器 类型别名与获取方法
std::vector<int>::const_reverse_iterator it_rbegin = vec.crbegin();
std::vector<int>::reverse_iterator it_rend = vec.rend();

// 迭代器差值为有符号数
int length = vec.size();
std::vector<int>::difference_type diff = vec.end() - vec.begin();
assert(diff == length);
```


## 2.2 构造相关操作
```c++
// 默认构造函数
std::vector<int> dctor_vec;  // vec1.size() == 0
std::array<int, 10> dctor_arr;  // 默认初始化, 静态内存默认为0, 栈内存为随机值

// 拷贝构造, 赋值构造
std::vector<int> copy_vec(vec);  // 二者类型相同且元素类型也相同
std::array<int, 10> assign_vec = vec;  // 其中 vec4 元素的个数必须与 vec2 相同

// 列表拷贝构造, 列表赋值构造, 元素类型可以构造转化即可 
std::vector<int> initlist_copy_vec{1, 2, 3, 4};  // 列表初始化, 个数与列表相同
std::array<int, 10> initlist_assign_vec = {1, 2, 3, 4};  // 剩余的元素会值初始化, 但是初始化的元素个数必须小于指定的数目
std::array<AClass, 2> initlist_copy_vec_object{{1,2},{3,4}};  // 存在多个参数构造一个对象的情况

// 迭代器范围拷贝 (array 不适用), 不必要求类型相同只要元素类型可以转换即可
std::vector<int> vec{1, 2, 3, 4};
std::list<int> range_copy_vec(vec.cbegin(), vec.cbegin() + 2);

// 个数构造, 个数+元素构造 只用于顺序容器
std::vector<int> number_ctor_vec(3);  // explicit, string 不适用, 值初始化
std::vector<int> number_value_vec(3, 2);  // 没有默认构造函数则必须提供一个元素初始值
```

## 2.3 赋值
```c++
// 对象赋值 要求类型相同 
// 赋值过后, 左侧的对象被销毁, 指向其元素的指针, 引用和迭代器无效
std::array<int, 10> arr{1, 2, 3, 4};
std::array<int, 10> copy_arr;
copy_arr = arr;

// 列表赋值
std::string s;
s = {'a', 'b', 'c'};  // array 不适用

// 替换赋值 有别于普通的赋值, 替换只要求元素类型可转换和范围合理即可
assign_range_str.assign(str.begin(), str.end() - 2);  // 范围替换
assign_list_str.assign({'2', '3', '4'});  // 列表替换
assign_number_str.assign(10, 'c');  // 个数替换
```

## 2.4 交换
```c++
std::deque<int> deq1{1, 2, 3, 4, 5, 6};
std::deque<int> deq2{4, 3, 2, 1};
auto it = deq1.begin() + 4;

// 通用交换方式 
std::swap(deq1, deq2);  // 尽量用非成员函数版本, 有益于泛型编程
std::cout << *it;
// swap 不会使引用, 指针和迭代器失效 (string除外)
// array 会实打实地拷贝需要O(n)时间, 而其他容器需要O(1)时间
```

##  2.5 大小操作
```c++
// 是否为空
bool is_empty = lst.empty();
// 当前元素个数
int now_size = lst.size();  // forward_list 没有 size 函数
// 当前容器能够支持地最大元素个数
int max_size = lst.max_size();
// 64 位 g++ 下部分容器支持地最大元素个数
// vector<int> : 4611686018427387903
// vector<long> : 2305843009213693951
// list<int> : 768614336404564650
```

## 2.6 关系运算符
- exercise1-17
```c++
std::vector<int> a{1, 2, 3};
std::vector<int> b{3, 2, 1};

// 首先容器类型和元素类型一致, 会逐一比较每个元素大小和元素个数
std::cout << (a == b);  
// 首先容器类型和元素类型一致, 取决于第一个不相等元素的比较结果或者长度
std::cout << (a  < b);  
```

# 3. 顺序容器通用操作
## 3.1 增加
```c++
std::vector<Test> vec;
std::forward_list<Test> lst;
// 尾部插入， 尾部创建
vec.push_back(Test("2"));  // vector 没有尾部插入
vec.emplace_back("2");

// 头部插入， 头部创建
lst.push_front(Test("2"));  // forward_list 没有头部插入
lst.emplace_front("2");

// 任意位置插入, 任意位置创建 返回增加元素地迭代器
vec.insert(vec.begin(), Test("5"));  // 根据 vector 结构会影响性能
vec.emplace(vec.begin(), "6");

// 任意位置插入多个元素 返回第一个增加元素地迭代器
vec.insert(vec.begin(), 2, Test("5"));
// 任意位置列表元素
vec.insert(vec.begin(), {{"1"}, {"2"}, {"3"}, {"4"}});
// 任意位置插入范围元素 范围不能相同
vec.insert(vec.begin(), lst.begin(), lst.end());

// 插入会导致部分迭代器, 引用和指针失效详见 3.5
```

## 3.2 访问
```c++
std::list<Test> lst{{"1"}, {"2"}, {"3"}, {"4"}};
std::vector<Test> vec{{"1"}, {"2"}, {"3"}, {"4"}};

// 对于任意容器的访问都要判断有没有元素
// 访问没有元素的容器行为是未定义
if (!lst.empty()) {
    lst.front().name();  // 返回首元素引用
    lst.back().name();  // 返回尾元素引用 forward_list 没有此函数
}

if (!vec.empty()) {
    vec[0].name();  // 返回下标为0的的引用, 下标溢出则未定义
    vec.at(0).name();  // 返回下标为0的的引用, 下标溢出则抛出 out_of_range 异常
}
```

## 3.3 删除
```c++
std::list<Test> lst{{"1"}, {"2"}, {"3"}, {"4"}};
std::vector<Test> vec{{"1"}, {"2"}, {"3"}, {"4"}};

// 对于任意容器的删除都要判断有没有元素
// 删除没有元素的容器行为是未定义
if (lst.size() > 1) {
    lst.pop_front();  // vector/string 无此函数
    lst.pop_back();  // forward_list 无次函数
}

if (vec.size() > 3) {
    vec.erase(vec.begin() + 1);  // 返回指向删除元素后的迭代器
    vec.erase(vec.begin(), vec.end() - 1);  // 返回指向最后一个删除元素后的迭代器
    vec.clear();  // 清空
}

// 删除会导致部分迭代器, 引用和指针失效 详见3.5
```

## 3.4 大小管理
> 不适用于array 且部分操作会导致迭代器指针失效
```c++
std::list<Test> lst{{"1"}, {"2"}, {"3"}, {"4"}};
std::deque<Test> deq{{"1"}, {"2"}, {"3"}, {"4"}};
std::vector<Test> vec{{"1"}, {"2"}, {"3"}, {"4"}};

// 通用顺序容器的大小管理
lst.resize(10);  // 增加时, 多于元素会值初始化
lst.resize(10, {"3"});  // 增加时, 多余元素为{"3"}
lst.resize(1);  // 减小时, 多余的元素被舍弃

// vector, string 特有的大小管理
vec.reserve(30);  // 预留 30 个分配空间 (若数字小于当前容量则忽略)
vec.capacity();  // 显示当前容量

// vector, string 和 deque 特有的大小管理
vec.shrink_to_fit();  // 缩小容量到当前个数, 实际会存在忽略等情况
```

## 3.5 失效条件

| 顺序容器 | 增加元素 | 删除元素(默认删除元素的访问方式都会无效) |
| --- | --- | --- |
| vector/string | 重新分配 : 所有位置的所有访问方式都失效 <br/>未重新分配 : 插入位置及之后所有位置的所有访问方式都失效 |删除位置及之后所有位置的所有访问方式都失效 |
| list/forward\_list | 所有位置的所有访问方式都有效 | 所有位置的所有访问方式都有效 |
| deque | 非首尾插入 : 所有位置的所有访问方式都失效 <br/>首尾插 : 所有位置的迭代器失效, 其他访问方式未失效 | 非首尾删 : 所有位置的所有访问方式都失效 <br/>首删 : 若元素是最后元素, 尾后迭代器无效，其他位置的所有访问方式不受影响 <br/>尾删 : 尾后迭代器亦被非法化, 其他位置的所有访问方式不受影响 |

> 1. 注意在每个步骤中更新迭代器指针引用
> 2. 不要保存尾后迭代器，因为除 list 和 forward_list 外每次改动都会失效, 直接用 end() 快速更新

# 5. forward_list特殊操作
> 1. 迭代器不能逆序增加, 不支持 size操作, 不支持寻秩访问
> 2. 无 push_back / pop_back / back 操作

```c++
std::forward_list<Test> flst{{"1"}, {"2"}, {"3"}, {"4"}};
std::vector<Test> vec{{"1"}, {"2"}, {"3"}, {"4"}};

// 返回首前迭代器 单向列表 需要 前驱指针来进行操作
auto bbit = flst.before_begin();
auto cbbit = flst.cbefore_begin();

// 迭代器之后插入 返回最后一个插入元素的迭代器
auto resutl_it1 = flst.insert_after(bbit, {"2"});  // 元素插入
auto resutl_it2 = flst.insert_after(bbit, 3, {"2"});  // 个数插入
auto resutl_it3 = flst.insert_after(bbit, vec.begin(), vec.end());  // 范围插入
auto resutl_it4 = flst.insert_after(bbit, {{"1"}, {"2"}, {"3"}, {"4"}});  // 列表插入

// 在迭代器之后构造
auto resutl_it4 = flst.emplace_after(bbit, "3");

// 在迭代器之后删除 返回删除元素后的迭代器
auto resutl_it5 = flst.erase_after(flst.before_begin());
auto resutl_it6 = flst.erase_after(flst.before_begin(), flst.end());  // 范围删除
```

# 6. string特殊操作
## 特殊构造
- 数组构造 : string c(cp, n) 自数组cp位置拷贝构造n个char n小于数组个数
- string构造 : string c(str, pos) 自str的pos位置开始拷贝构造到结束
- string构造n字符 : string c(str, pos, n) 自str的pos位置拷贝构造n个字符,n>size则到末尾为止 
- substr拷贝构造 : string c=str.substr(pos,n) 自str的pos位置拷贝构造n个字符

## 插入或追加
- 下标插入多个字符 : str.insert(pos, n, '!'); 在pos位置处插入n个'!'字符  
- 下标插入数组 : str.insert(pos, cp); 在pos位置插入字符数组到'\0'之前(必须以空字符结尾)
- 下标插入字符串 : str.insert(pos, s); 在pos位置插入字符串s
- 下标插入指定长度字符串 : str.insert(pos, s, poss, n); 在pos位置插入从poss开始的字符串s的n个字符
- 末尾追加 : str.append("123");

## 删除或更替
- 下标删除多个字符 : str.erase(pos, n); 在pos位置开始删除n个字符到末尾为止 
- 更替 : str.replace(pos, n, "1234"); 在pos位置删除n个字符后插入"1234"字符串

## 查找
> 返回 string::size_type无符号类型, 如果没有找到返回 string::nops 即 const string::size_t 类型为-1 代表最大位置

- 查找字符串 : find(str2 (, pos=0) ); 返回第一个匹配的下标,从str的pos开始查找str2
- 查找字符 : find(c (, pos=0) ); 返回第一个匹配的下标, 从str的pos位置开始查找字符c
- 查找字符数组 : find(cp (, pos=0)); 返回第一个匹配的下标, 从str的pos位置开始查找字符数组cp
- 查找指定个数的字符数组 : find(cp , pos, n); 返回第一个匹配的下标, 从str的pos位置开始查找字符数组cp前n个值

> args表示匹配的范围, 如上

- find(args); rfind(args); 查找第一次(最后一次)匹配的下标
- find_first_of(args); find_last_of(args);  查找args中任意一个字符第一次(最后一)出现的
- find_first_not_of(args); find_last_not_of(args); 查找第一个(最后一个)不在args中的字符

## 比较
- 字符串比较 ： compare(str2);
- 字符串位置比较 : compare(pos1, n1, str2(,n2)); 从下标pos1开始n1个字符与str2(开头n2个字符)比较
- 空字符结尾的数组比较 : compare(cp);
- 数组位置比较 : compare(pos1, n1, cp(,n2)); 从下标pos1开始n1个字符与cp(开头n2个字符)比较

## 数值转化
- 转换为字符串 : to_string(val); 转换为浮点型或者int或更大整型
- 转换为整型 : stoi / stol / stoul / stoll /stoull (s, p, b); 返回s字符串内的数值, p是指向size_t的指针, b是基数
- 转换为浮点型 : stof / stod / stold (s, p); 返回s字符串内的数值, p是指向size_t的指针

## 替换
- 数组替换 : str.assign(cp, 7); 替换为数组的7个字符
- str.assign(pos, cp); 在pos位置替换为字符数组到'\0'之前(必须以空字符结尾)
![](https://img-blog.csdnimg.cn/20200815194721836.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNDgyMTk4,size_16,color_FFFFFF,t_70#pic_center)


# 7. 适配器
> 适配器接受一种容器类型,使之有其他的作用

## 通用操作
- 构造 : A\<T> a; A\<T, C\<T>> a; A\<T> a(c);  默认以某种容器创建适配器 ; 指定某种容器创建适配器 ; 拷贝某种容器创建适配器; 
- 类型别名 : size_type 元素个数类型 value_type 元素类型 container_type 容器类型
- 关系运算符 : 如 == , != , > , < 等 底层容器重载
- 其他函数 : empty() , size() , swap(a,b) 要求a,b 类型和底层容器类型一致

## 栈适配器
- 定义在\<stack>中,默认基于deque实现,且要求有尾部增删查操作,排除array和forward_list容器

---
- 弹出栈顶 : s.pop() 不返回元素的值
- 压入栈顶 : s.push(t); s.emplace(args); 
- 查看栈顶 : s.top(); 返回栈顶元素引用

## 队列适配器
- queue和priority_queue定义在\<queue>中
- queue需要头尾增删操作排除vector,array,forward_list,默认基于deque实现
- priority_queue需要尾部增删和随机访问操作排除list,array,forward_list,默认基于vector实现

----
- 弹出首元素 : s.pop() 不返回元素的值
- 压入队列末尾或者合适位置 : s.push(t); s.emplace(args); 
- 查看首元素 : s.front(); 返回首元素引用
- 查看尾元素 : s.back(); 返回尾元素引用 只用于queue
- 查看优先级最高元素 : s.top(); 返回优先级最高引用 只用于priority_queue
> priority_queue 在添加元素时会通过元素的大小关系寻找到合适位置进行插入

