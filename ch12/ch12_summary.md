# 第十二章 动态内存与智能指针
## 1. 概述
- 程序用堆来存储动态分配的对象,一般会产生三个问题: 忘记释放内存, 同一块内存释放两次 和 产生野指针
- 一般出于三种原因使用动态内存: 对象个数未知, 类型未知, 需要共享数据 
- 用shared_ptr, unique_ptr 和 weak_ptr 帮助管理内存, 定义在`<memory>`中

## 2. 智能指针
### shared\_ptr通用用法

|unique与shared通用用法|解释|
|---|---|
|shared_ptr/unique_ptr\<T> p1(T* p = nullptr)| 返回保存指针的智能指针, 指向T类型 |
|if(p); \*p; p->mem;|通过智能指针判断是否为空或者访问对象|
|p.get();|获取智能指针中保存的指针|
|swap(p1,p2);|交换智能指针中保存的指针|

|shared用法|解释|
|---|---|
|make_shared\<T>(args);|初始化智能指针并返回|
|shared_ptr\<T> p(q(,d)|拷贝初始化, 调用对象d替代delete|
|p=p2;|递增p2的计数, 递减p原来的计数 |
|p.unique(); p.use_count();|测试当前计数值, 一般做reset的检测|

- shared_ptr 保存引用计数,记录有多少个其他智能指针指向同一个对象,赋值或值返回 与销毁会增减计数

### 直接管理内存
- 通过 new 手动分配对象,但注意对象的默认初始化问题
```c++
int *p1=new int; // 动态分配的内置类型 未初始化值未定义
string *p2=new string; // 动态分配的类类型 调用默认构造函数初始化
vector<int> *p3=new vector<int>{1,2,3,4,5,6};  // 列表初始化
auto *p4=new auto(obj); // 分配与obj相同类型相同值的对象,注意obj只能有一个
const int *p5=new const int(3); // 动态分配const对象,返回值必须是指向const的指针,且分配对象必须初始化
```
- 通过 new 手动分配对象, 会抛出`bad_alloc`异常 可以通过 `new (std::nothrow) T();` 来避免抛出异常, 返回空指针
> `nothrow` 和 `bad_alloc` 定义在 `<new>`中

- 通过 delete 释放内存, 注意不可多次释放, 不可释放非new分配的内存, 可以为释放后的指针置nullptr来提供有限保护
- 当引用计数为0则会调用析构函数释放分配的对象

### shared_ptr 与 new

|shared_ptr其他用法|解释|
|---|---|
|shared_ptr\<T>p(q(,d));|接管new分配的内存, 注意是explicit的不可用=<br/>(调用对象d替代delete)|
|shared_ptr\<T>p(u);|接管unique分配的内存, 将u置空|
|p.reset(); p.reset(q(,d));|如果计数为1则释放且p置空,若传递内置q则会指向q(调用d替代delete)|

- 不同shared_ptr接管相同手动分配的内存则各自计数为1, 存在风险如下: 
```c++
void func(shared_ptr<int> p);  // 将内置指针传递临时对象后会在返回时自动销毁
shared_ptr<int> a(21);  
int *ap=a.get();
{
	shared_ptr<int> b(ap);  // get()的指针被另外一个shared_ptr接管
}							// 在作用于结束时也会自动销毁
```

- 智能指针会在异常抛出后自动释放,手动分配如果未被捕获会导致内存泄漏
```c++
void func(){
	auto it=make_shared<int>(24);
	// ..发生异常, func中未捕获
}// 跳出后it自动释放内存
void func(){
	auto it=new int(24);
	// ..发生异常, func中未捕获
	delete it;
}// 跳出后it未被释放发生内存泄漏
```

- 可以通过传递删除器 `shared_ptr p(q,d);` 自动管理哑类
```c++
void end_connection(connection *p){ disconnect(*p); } // 注意删除器参数必定是智能指针保存的指针类型
void f(dest &d){
	connection c=connect(&d);
	shared_ptr<connection> p(&c, end_connection);
	// 发生异常会自动释放哑类
}
```

### unique_ptr
- `unique_ptr<int> p(new int(22));` 只能指向一个对象, 必须初始化绑定到new分配的对象上
- 不支持拷贝构造, 不支持赋值, 可以通过特殊操作进行转移, 作为返回值返回时执行移动拷贝

|unique_ptr用法|解释|
|---|---|
|unique_ptr\<T(,D)> p(d);|定义一个空unique_ptr,删除器的类型为D,传递一个删除器d|
|u.release();|返回管理的指针,u设置为空|
|u=nullptr; u.reset(nullptr); u.reset(q);| 释放u的对象; 将p设置为空; 接管动态分配的q |

### weak_ptr
- `weak_ptr`绑定到`shared_ptr`后不会改变引用计数, 销毁时不管是否有`weak_ptr`绑定, 可以通过lock判断`weak_ptr`是否为空

|weak_ptr用法|解释|
|---|---|
|weak_ptr\<T> w(sp);|用shared_ptr初始化一个weak_ptr|
|w=p|p是一个shared_ptr或者weak_ptr|
|w.reset(), use_count()|置空, 返回sp的引用计数|
|w.expired()|shared_ptr的use_count()=0返回真|
|w.lock()|如果expired为真返回空shared_ptr<br/>否则返回一个指向对象的shared_ptr(引用计数+1)|


## 4. 动态数组
### 手动分配
- 手动分配数组返回一个指针, 对于动态分配的内存不能调用begin(),end()函数获取迭代器
- 分配0个数数组返回一个空指针, 价与尾后指针
- `delete [] p;` 逆序释放元素,  一定加上`[]`释放动态数组,否则未定义

```c++
typedef int arrayT[6];
int *p1=new int[get_size()]; // 默认初始化 未定义
int *p2=new arrayT(); // 值初始化为0
int *p3=new arrayT{1,2,3,4,5}; // 列表初始化 剩余一个值初始化为零
int *p4=new arrayT{1,2,3,4,5,6,7};  // 抛出 bad_array_new_length 异常<new>头文件中

unique_ptr<int[]> up(new int[10]()); //可以通过unique_ptr管理手动分配的数组
// <int[]> 表达类型是一个数组
up[4]=21; // 可以通过下标访问数组,但不支持成员访问运算符(. / ->)
up.release();  // 默认调用delete [] 释放数组

shared_ptr<int> sp(new int[10](), // 可以通过shared_ptr管理手动分配的数组
	[](int *p) { delete [] p;} ); // 但是必须提供删除器
*(sp.get()+1)=22; // 不支持下标访问,只能通过get返回内置指针进行操作
```

### allocator类
- allocator将分配内存和构造分离, 先分配较大内存然后按需构造对象(付出一定开销, 节省一定内存)
- 必须先构造后才能使用元素, 否则未定义
```c++
allocator<string> a;  // 创建allocator对象
auto const p=a.allocate(n); // 分配n个对象大小内存,返回第一个元素内存的指针
auto q=p; a.construct(q++,"123"); // 在指针处按参数构造
a.destory(--q); // 释放对象
a.deallocate(p,n); // 回收内存
```

- 可以通过拷贝或填充未初始化的内存:

|函数|作用|
|---|---|
|uninitialized_copy(b,e,p);|拷贝迭代器[b,e)范围元素到p指针开始指向的未构造内存位置,返回尾后位置|
|uninitialized_copy_n(b,n,p);|拷贝迭代器b开始n个元素到p指针开始指向的未构造内存位置,返回尾后位置|
|uninitialized_fill(b,e,t);|在迭代器(指针)[b,e)范围元素构造与t相同的元素,返回尾后位置|
|uninitialized_fill_n(b,n,t);|在迭代器(指针)b开始构造n个t相同的元素,返回尾后位置|