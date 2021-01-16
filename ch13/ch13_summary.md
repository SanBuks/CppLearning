# 第十三章 拷贝控制

### 1. 拷贝, 赋值与销毁
#### 拷贝构造函数
- 形式 : `ClassName (const ClassName&, int a=10 ... )` 第一个参数必为自身类型引用(一般为const), 其余参数都有默认实参
- 合成拷贝构造函数 : 逐一将非static成员拷贝到新对象中如 : 
	- 类成员 : 调用类成员的拷贝构造函数
	- 内置类型 : 直接复制
	- 数组类型 : 逐一将数组内元素拷贝到另一个数组
```c++
string s2=s1;  // 调用拷贝构造函数初始化
string s3="123";  // 隐式类类型转化后调用拷贝构造函数
// 拷贝构造函数存在隐式类型转化必须 非explicit
void f(vector<int>);
f(10); //错误vector<int> 是explicit构造的不能隐式类型转换
f(vector<int>(10)); // 必须显示声明
// 编译器优化时有时会跳过拷贝移动构造函数直接转化成等价的构造函数
```

- 调用场景 : 
	- 作为实参进行值传递
	- 非引用类型函数返回
	- 列表初始化数组或者聚合类
	- 容器push,insert操作等

#### 拷贝赋值运算符
- 形式 : `ClassName &operator=(const ClassName &)` 尽量保持内置类型赋值运算符一致, 返回本身引用`*this`.
- 合成拷贝赋值运算符 : 逐一将非static成员拷贝到新对象中, 情况与上述类似

#### 析构函数
- 形式 : `~ClassName(){}` 无参数, 无返回值, 析构函数唯一
- 过程 : 先执行函数体, 再按初始化顺序逆序销毁非static成员. 其中函数体执行收尾工作(如delete pointer), 而销毁过程为隐式, 内置类型成员则直接销毁, 若为其他类型则会调用其析构函数
- 合成析构函数 : 函数体为空, 自动销毁成员, 但是不能进行收尾工作
- 调用场景 : 
	- 变量离开作用域调用
	- 对象销毁, 类成员调
	- 容器或数组销毁, 元素调用
	- delete pointer 调用
	- 临时对象表达式结束时销毁 如 A( A("123") ); 括号内的临时对象拷贝后即销毁

#### 管理拷贝控制
- 首先判断一个类是否需要自定义析构函数, 如果需要则也需要自定义拷贝构造函数和拷贝赋值运算符
- 其次若需要自定义拷贝构造函数则也需要自定义拷贝赋值运算符, 未必需要自定义析构函数
- `=default` 显示要求合成的拷贝控制版本, 内部默认内联, 可以内部仅声明外部加限定防止内联
- `=delete` 定义为删除的函数,  第一次声明时限定, 可以对任何函数使用
- `private` 限制访问来阻止拷贝, 且只声明不定义成员函数合法
> 访问未定义的实体会产生链接错误, 访问不可访问对象产生编译错误

- 析构函数如果删除
	- 不可定义该类型 变量和临时变量
	- 不可定义包含该类成员的其他类 变量和临时变量
	- 可以动态分配上述类型对象, 但是不可delete p释放
- 合成拷贝控制为删除的场景 : 

|删除的合成拷贝控制|原因|
|---|---|
|析构函数|成员析构函数删除|
|拷贝构造函数|成员拷贝构造函数删除<br/>成员析构函数删除|
|拷贝赋值运算符|成员拷贝赋值运算符删除<br/>成员是const或引用类型|
|默认构造函数|成员析构函数删除<br/>类成员是const或引用没有类内初始化|

>  拷贝赋值运算符是否删除 与 拷贝构造函数删除的原因没有关系如下 : 

```c++
#include <iostream>
class A{
	int a=3;
public:
	// 合成的默认构造函数删除
	~A()=delete;  // 析构函数显示删除
	// 合成的拷贝构造函数删除
	// 合成的拷贝赋值函数?
	void print() { std::cout<<a<<'\n'; }
};
int main(){
	A *a=new A();	
	A *b=new A();
	*a=*b;  // 成功运行合成的拷贝构造函数
	a->print();
	b->print();
}
```

#### "值类" 和 "指针类"
- 行为像值的类 : 拷贝赋值运算符注意先拷贝内容再释放来解决和异常安全的问题
- 行为像指针的类 : 使用share_ptr或者自定义引用计数
```c++
// 表现像值一样类:
// 1. 拷贝构造写法:
HasPtr(const HasPtr &rhs):ps(new string(*rhs.ps)){}
// 2. 拷贝赋值运算符写法: 
HasPtr& operator=(const HasPtr &rhs){
	auto newp=new string(*rhs.ps);  // 首先复制一份指针所指内容
	delete ps;  // 防止自身赋值被意外释放掉
	ps=newp;  // 复制指针
	i=rhs.i;  // 直接复制非动态分配的成员
	return *this;
}
// 3. 析构函数写法:
~HasPtr(){ delete ps; }

// 表现像指针一样类(引用计数): 
// 1. 拷贝构造写法:
HasPtr(const HasPtr &rhs): ps(rhs.ps), use(rhs.use){ ++*use; }
// 2. 拷贝赋值运算符写法:
HasPtr& operator=(const HasPtr &rhs){
	++*rhs.use; // 首先增加被复制的对象引用次数防止自身复制
	if(--*use==0){  // 左侧对象引用计数减一 为零则释放
		delete ps; 
		delete use;
	}  
	ps=rhs.ps;  // 复制指针
	use=rhs.use;  // 复制引用计数指针 (已经增加计数)
	return *this;
}
// 3. 析构函数引用计数使用写法:
~HasPtr(){  // 析构函数注意只有在引用计数为零后才真正释放
	if(--*use==0){
		delete ps;
		delete use;
	}
}
```

#### 交换操作
- `std::swap` 实质等价为
```c++
A temp=v1;  // 拷贝构造函数 
v1=v2;  // 拷贝赋值运算符
v2=temp; // 拷贝赋值运算符 
// 创建一个临时对象, v1被拷贝2次 v2被拷贝1次
// 如果对象中含有分配的内存则产生了额外的成本
// 一般需要对资源管理的类进行额外的swap重载进行性能优化
```

- 自定义swap函数
```c++
// swap 的重载问题
class A{
	friend void swap(A &, A &);
	string ps;
	int i;
};
inline void swap(A &lhs, A &rhs){
	using std::swap; // 使 std::swap 可见
	swap(lhs.ps, rhs.ps); // 标准库模板与非模板swap发生重载 优先调用非模板函数
	swap(lhs.i, rhs.i);  // 函数查找的列外防止std::swap隐藏了非模板函数
    // 例外指的是 函数型参如果是类类型,类类型指针或者引用 除了在当前作用域,外层作用域查找函数名外还会在类定义的命名空间中查找相应的函数名
```

- 拷贝并交换技术 :  异常安全且正确处理自赋值
```c++
A& A::operator=(A rhs){  // 拷贝构造rhs作为一个副本 如果发生错误则不会进入函数体且处理了自赋值
	swap(*this, rhs);  // 交换数据成员
	return *this;  // 返回后临时对象rhs自动销毁
}
```

### 2. 两个实例
#### Message
```c++
/* 	
	Message 与 Folder 是多对多关系, 互相存放对应的指针 set
	Message 有 从具体Folder对象保存和删除的动作
	Message 在 拷贝控制过程中注意对应set的更新
*/
class Message{
	friend class Folder;  // Folder 可以直接访问Message的数据
	friend void swap(Message &, Message &);  // 自定义的交换操作
private: // 数据成员
	std::string contents;       // 内容
	std::set<Folder*> folders;  // 包含所有存有本消息的文件夹
public:  // 公共成员
	Message(const std::string &str=""):contents(str){}  // 默认构造函数
	~Message();  // 析构 注意对应folder对象保存信息的销毁
	Message(const Message &);  // 拷贝控制 注意对应folder对象保存信息的增加
	Message &operator=(const Message &);  // 赋值拷贝	
	Message(Message &&);  // 移动拷贝 更新folder对象可能会抛出异常
	Message &operator=(Message &&); // 移动赋值 更新folder对象可能会抛出异常
	
	void save(Folder &);  // 将本信息添加到指定文件夹中
	void remove(Folder &); // 将本信息从指定文件夹中删除
private:  // 工具函数用于拷贝控制	
	void add_to_Folders(const Message &); // 将本信息添加到包含另外信息的所有文件夹中
	void remove_from_Folders();  // 将本信息从所有文件夹中删除
	void move_Folders(Message *);  // 移动folders 
};
class Folder{
private:
	std::set<Message*> messages;
public:
	void addMsg(Message *);
	void remMsg(Message *);
};
```

#### StrVec
```c++
class StrVec{
private : // 数据成员
	std::string *elements;  // 指向第一个元素
	std::string *first_free;  // 指向第一个空余空间
	std::string *cap;  // 指向尾后
	static std::allocator<std::string> alloc;  // 动态内存分配器

public:  // 公共成员
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr){}
	~StrVec(){ free(); };
	StrVec(const StrVec &);
	StrVec &operator=(const StrVec &);
	StrVec(StrVec &&) noexcept;	
	StrVec &operator=(StrVec &&) noexcept;

	void push_back(const std::string &);  // 末尾增加元素
	void push_back(std::string &&); // 末尾增加元素 右值版本

	size_t size() const { return first_free-elements; }
	size_t capacity() const { return cap-elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }

private:  // 工具函数
	void chk_n_alloc(){ if(size()==capacity()) reallocate(); }
	std::pair<std::string *, std::string *> alloc_n_copy
		(const std::string *, const std::string *);  // 分配内存并构造范围内的拷贝
	void free();  // 释放内存
	void reallocate(); // 重新分配内存
```

### 3. 对象移动
> 移动解决对象被拷贝后就被销毁的性能浪费问题, 旧标准中容器元素必须能拷贝, 新标准中容器元素必须能拷贝或移动

#### 右值与左值
- 基本定义 : 左值右值描述表达式结果或对象的属性
	- 左值 : 结果或对象描述的是一个内存空间, 在作用域内持续存在, 可以被赋值使用
	- 右值 : 结果或对象描述的是一个值, 表达式结束后即被销毁, 不可被赋值使用
- 左右值引用 : 
	- 左值引用 : 某一个左值表达式结果或对象的别名 如赋值表达式结果等
	- 右值引用 : 某一个右值表达式结果或对象的别名 如字面值常量, 取地址符表达式等
> 右值引用的对象即将被销毁, 没有其他用户能够使用则导致右值引用的代码可以随意 '窃取' 该对象的数据
```c++
int a=3;  // a 是一个变量, 是左值
int &b=a; // b 是一个左值引用
int &&c=3;  // c 是一个右值引用
int &&d=c;  // 错误, c 作为变量表达式结果为左值
```

- 右值绑定左值 : 使用`int &&d=std::move(c);`可强制绑定到左值, 绑定后c对象除了被赋值和销毁不能再被使用或做与内容相关的操作(已被窃取, 内容不完整)

#### 移动拷贝控制
- 移动拷贝构造 : `A(A &&a) noexcept : p1(a.p1), p2(a.p2){ a.p1=a.p2=nullptr; }`
	- 型参非const, 因为右值被`窃取`数据, 一定会发生状态改变
	- 资源移动一般不会分配内存, 则不会发生异常, 通过`noexcept`告诉编译器, 防止为了异常安全而只调用拷贝构造
	- 资源移动后需要将型参置于能够被析构或有效状态 ( 能被重新赋值 )

- 移动赋值构造 :  `A& operator=(A &&rhs) noexcept{ if(this!=&rhs){...} return *this;}`
	- 需要检查自赋值情况, 防止使用`std::move`产生同源现象

#### 合成的移动控制
- 如果类自定义了任何一个拷贝控制, 则不会合成移动控制, 如果没有定义且每个非static数据成员都可移动(有对应移动操作)则会合成
- 移动控制永远不会隐式定义为删除, 除非显示声明为default, 但有数据成员不能被移动则会定义为删除, 除此之外还有以下情况 :

| 删除的合成移动控制 | 原因 |
| --- | --- |
| 移动构造函数 | 成员移动构造函数删除<br/>析构函数删除 |
| 移动赋值运算符 | 成员移动赋值运算符删除<br/>类成员是const或引用 |

#### 其他
- 拷贝控制和移动控制会发生重载, 没有移动控制使用std::move会调用拷贝控制
- 三五规则 : 自定义了五个中的一个函数则需要定义其他四个函数
- 移动迭代器 : 解引用产生左值变为产生右值, 通过`make_move_iterator(it)`转换为移动迭代器
- 成员函数也可以通过定义右值引用参数提升性能
- 引用限定符 : `str1+str2="123";` 对于右值进行了赋值, 为了限制该行为在自定义类中出现可以通过引用限定符来解决
```c++
A& operator(const A &) &;// 限制只有左值可以使用赋值运算符
A func() const &; // const 出现在限定符之前, 且限定符和const不能修饰static成员函数
A func() cosnt &&; // 同名且同参数类型的函数要么都加上引用限定或者都不加上引用限定
```
