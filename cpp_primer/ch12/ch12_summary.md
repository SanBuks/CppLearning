# 1. 概述
## 1.1 大致内存分类
- 静态内存: 局部 static 对象, 类 static 对象 和 全局对象
- 栈内存: 函数内非 static 对象
- 堆: 动态分配的对象

## 1.2 堆使用的痛点问题
- 忘记释放内存: 内存泄漏
- 同一块内存释放多次: 未定义, 可能无意释放了其他对象的内存
- 使用野指针: 未定义, 可能无意对其他对象的内存进行了操作

- 一般出于三种原因使用动态内存: 对象个数未知, 类型未知, 需要共享数据 
- 用shared_ptr, unique_ptr 和 weak_ptr 帮助管理内存, 定义在`<memory>`中

# 2. 智能指针
## 2.1 shared\_ptr 与 unique\_ptr 通用用法
```c++
// shared_ptr 和 unique_ptr 公用操作
unique_ptr<vector<int>> up(new vector<int>{1, 2, 3});  // 指向 分配的对象
unique_ptr<vector<int>> up_empty;                      // 指向 空指针
if (up && !up->empty()) {                              // 与 内置指针类似操作
  const auto &vec = *up;
  const vector<int> *raw_pointer = up.get();           // 获取内部管理指针
  cout << vec[0] << " " << (*raw_pointer)[1] << "\n";  // 1 2
}

swap(up, up_empty);                                    // 交换
cout << (up ? 1 : 0) << "\n";                          // 0
cout << (*up_empty)[2] << "\n";                        // 3
```

## 2.2 shared\_ptr 特殊用法
```c++
// shared_ptr 特殊操作
// shared_ptr 保存引用计数,记录有多少个其他智能指针指向同一个对象, 赋值, 值返回会增加计数
//                                                    离开作用域自动销毁会减少计数
// 注意 保存在容器中的智能指针遗留问题, 需要手动 erase 不需要保存对象的指针
shared_ptr<vector<int>> sp1 = make_shared<vector<int>>(10, 2);  // 根据 构造函数的参数 动态分配
shared_ptr<vector<int>> sp2(sp1);                               // 拷贝构造 增加 引用计数
shared_ptr<vector<int>> sp3 = make_shared<vector<int>>();
sp3 = sp2;                                                      // 拷贝减少 sp3 引用计数, 增加 sp2 引用计数
std::cout << sp3.unique() << " " << sp3.use_count() << "\n";    // 引用计数是否是一, 引用计数个数
                                                                // 3 3
```

## 2.3 直接管理内存
### new 使用方式
```c++
// 1. 通过 new 手动分配对象方式 (需要注意对象的默认初始化问题)
int *p_default_initialization = new int;                             // 随机值
int *p_value_initialization1 = new int();                            // 值初始化为 0
int *p_value_initialization2 = new int{};                            // 值初始化为 0
auto *p_vec_default = new std::vector<int>;                          // auto 简化声明, 调用默认构造函数
const auto *p_const_vec = new const std::vector<int>;                // auto 简化声明, 分配 const 对象对象
auto *p_vec_initialization_list = new std::vector<int>{1, 2, 3, 4};  // auto 简化声明, 列表初始化
//auto *p4=new auto(obj);                                            // auto 简化声明, auto 只能有一个 

// 2. new 分配会抛出异常 bad_alloc
// 2.1 通过 try-catch 捕获异常
#include <new>
try {
  int *p = new int(2);
} catch (std::bad_alloc &ex) {
  throw ex; 
}
// 2.2 定位 new 避免抛出异常
#include <new>
// 传递 nothrow 对象给 new 抑制抛出异常
int *p = new (std::nothrow) int(2);
if (!p) {
  std::cout << "alloc failed\n"; 
  return ;
}
```

### delete 使用方式
```c++
// 1. delete 表达式
int *p = new (std::nothrow) int(2);
delete p;           // 释放单个元素

int *p_array = new (std::nothrow) int[10]{0};
delete [] p_array;  // 释放多个元素


// 2. delete 的问题
delete [] p_array;  // 多次释放      未定义
int *q;
delete q;           // 释放非分配内存 未定义
dosomething(p);     // 使用野指针    未定义

p_array = nullptr;  // 删除后置空 只能提供有限保护, 同时会隐藏逻辑BUG
                    // 本人推荐不置空, 而是通过 AddressSanitizer 等工具检测内存 UAF
```

## 2.4 shared\_ptr 与 new
### shared\_ptr 接管所有权
```c++
int *p_array_shared = new int[100]{0};
int *p_array_shared_another = new int[100]{0};
int *p_int_unique = new int(0);
int *p_array_unique = new int[100]{0};
auto deleter = [](const int *p) {delete [] p;};

std::unique_ptr<int>    up1(p_int_unique);
std::unique_ptr<int []> up2(p_array_unique);
std::shared_ptr<int>    sp1(p_array_shared, deleter);         // 从 raw_pointer 接管所有权, 同时提供 deleter
std::shared_ptr<int>    sp2(sp1);                             // 从 sp 处共享所有权, 同时拷贝 deleter
if (*get_deleter<decltype(deleter)>(sp2) == deleter) {       
  std::cout << "same\n";                                     
}                                                            
                                                             
std::shared_ptr<int> sp3(std::move(up1));                     // 从 unique_ptr 接管所有权 (非数组类型)
std::shared_ptr<int> sp4(up2.release(), up2.get_deleter());   // 从 unique_ptr 接管所有权 
                                                              // 数组类型, C11 shared_ptr 不能保存 T []
sp1.reset(p_array_shared_another, deleter);                   // 释放 shared_ptr 所有权, 从 raw_pointer 接管所有权
```

### shared\_ptr 所有权问题
```c++
// 1. get() 会潜在造成所有权越界
void func(shared_ptr<int> p);  
shared_ptr<int> a(21);  
int *ap = a.get();
{
	shared_ptr<int> b(ap);  // get() 的指针被另外一个 shared_ptr 接管
}							// 在作用于结束时也会自动销毁
// 同理: 被接管后的 raw_pointer 再被使用也会造成越界

// 2. 智能指针 遵循 RAII, 会在异常抛出后自动释放, 手动分配如果未被捕获会导致内存泄漏
void func() {
  auto it = make_shared<int>(24);
// ..发生异常, func中未捕获
} 
// 跳出后it自动释放内存

void func() {
  auto it = new int(24);
// ..发生异常, func中未捕获
  delete it;
}  
// 跳出后 it 未被释放发生内存泄漏 
// 使用 try-catch + delete / error_code + goto

// 3. 传递删除器 `shared_ptr p(q,d);` 自动管理哑类
void end_connection(connection *p) {  // 删除器参数必是智能指针保存的指针类型
  disconnect(*p); 
}  
void f(dest &d) {
  connection c = connect(&d);
  shared_ptr<connection> p(&c, end_connection);
// 发生异常会自动释放哑类
}
```

## 2.5 unique\_ptr
```c++
// 1. 只能指向一个对象, 不支持拷贝构造, 不支持赋值, 必须初始化绑定到new分配的对象上
unique_ptr<A> up(new A(22), deleter);

// 2. 支持 移动构造, 移动赋值
unique_ptr<A> func() {
  return unique_ptr<A>(new A(22));
}

// 3. 可被置空, 或重新接管所有权
up = nullptr; 
u.reset(nullptr);
u.reset(q);

// 4. 返回所有权, 并置空
auto raw_pointer = u.release();
```

## 2.6 weak\_ptr
```c++
// weak_ptr 是与 shared_ptr 配对的 "弱管理对象" 

// 1. 绑定到`shared_ptr`后不会改变引用计数
wead_ptr<int> wp(sp);
wp = sp_another;           // wp_another
assert(wp.use_count(), 1);
wp.reset();
assert(wp.use_count(), 0);

// 2. 可判断 shared_ptr 所有权管理状态
wp.expired();              // 判断 use_count 是否为 0
auto sp_lokc = w.lock();   // 如果 expired 为真返回空 shared_ptr
                           // 返回一个指向对象的 shared_ptr (引用计数+1)
```

# 3. 动态数组
```c++
// 手动分配数组返回一个指针, 对于动态分配的内存不能调用 begin(), end()函数获取迭代器
typedef int arrayT[6];
int *p1 = new int[get_size()];          // 默认初始化 值未定义
int *p2 = new arrayT();                 // 值初始化为 0
int *p3 = new arrayT{1,2,3,4,5};        // 列表初始化 剩余一个值初始化为零
int *p4 = new arrayT{1,2,3,4,5,6,7};    // 超出内存限制, 抛出 bad_array_new_length 异常
                                        
int *p5 = new int[0];                   // 返回合法的非空指针, 等价为尾后指针, 不可解引用
                                        
                                        
delete [] p1;                           // 逆序释放元素, 一定加上 [], 否则未定义

unique_ptr<int[]> up(new int[10]());    // 可以通过 unique_ptr 管理手动分配的数组
up[4]=21;                               // 可以通过下标访问数组,但不支持成员访问运算符(. / ->)
up.release();                           // 默认调用 delete [] 释放数组

// shared_ptr<int[]> sp(new int[10]()); // shared_ptr 在 C++11 中不支持动态数组
shared_ptr<int> sp(new int[10](),       // shared_ptr 可以通过 提供删除器 管理手动分配的数组
                   [](int *p) { delete [] p;}); 
*(sp.get()+1)=22;                       // shared_ptr 在 C++11 中不支持下标访问, 只能通过 get 返回内置指针进行操作
```

## 4. allocator 类
### 基本使用
- allocator 将分配内存和构造分离, 先分配较大内存然后按需构造对象(付出一定开销, 节省一定内存)
- 必须先构造后才能使用元素, 否则未定义
```c++
allocator<string> a;           // 创建 allocator 对象
auto const p = a.allocate(n);  // 分配 n 个对象大小内存, 返回第一个元素内存的指针
auto q = p; 
a.construct(q++, "123");       // 在指针处按参数构造
a.destory(--q);                // 释放对象
a.deallocate(p,n);             // 回收内存
```

### 拷贝填充算法
```c++
size_t size = 3;
vector<string> vec{"1", "2", "3"};
allocator<string> alloc;

// 分配的指针一般作为 const 哨兵
auto const b = alloc.allocate(size);

// [b, e) -> [b, ...)
auto const e = uninitialized_copy(vec.begin(), vec.end(), b);
// [b, b + n) -> [b, ...)
auto const e = uninitialized_copy_n(vec.begin(), vec.size(), b);
// "1" - > [b, e)
auto const e = b + vec.size();
uninitialized_fill(b, e, "1");
// "1" -> [b, b + n)
auto const e = b + vec.size();
uninitialized_fill_n(b, vec.size(), "1");


cout << e - b << "\n";
for (auto p = b; p != e; ++p) {
  cout << *(p) << " ";
}

for (auto p = e; p != b;) {
  alloc.destroy(--p);
}
alloc.deallocate(b, e - b);
```