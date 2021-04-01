# Effective CPP 总结
## 1. 让自己熟悉CPP
1. 语言联邦
	- C语言 : 面向过程
	- 封装, 继承, 多态 : 面向对象
	- STL, 模板 : 泛型编程
2. 用const而不是define来替换魔数, 因为const对象会进入编译的符号表, 编译过程中提供额外信息
3. 用inline template函数替换宏函数避免宏展开的错误
4. 类内静态成员初始化后可作数组定义下标
	- 一般类内声明, 类外定义(cpp中)
	- 如果类内初始化则 必须 
		- constexpr 修饰 
		- 是字面值类型 
		- 初识值是常量表达式
		- 类外需定义一次不必初始化
5. enum hack 替换 类内初始化, 也可坐数组下标, 且不是对象没有地址 
6. 尽量使用const
	- 尽量限制用户对参数的改动
	- 作为const 返回值放止作为左值 (&&限定符)
	- const 成员函数会因为对象是否const而发生重载
	- logical const理念 : const 成员函数可以修改对象的bits, 前提是用户侦测不出来的情况下, 使用mutable限定这些bits
	- 避免const和non-const成员函数重复
```c++
const char &operator[](std::size_t posi) const { 
	return text[posi];
}
char &operator[](std::size_t posi) { 
	return const_cast<char &>(
		static_cast<const A&>(*this)[posi]
		);
}
// 反过来不可以, 因为 const 成员函数不应该去掉 *this 的 const 限定
```

7. 定义对象时候一定赋予初识值完成初始化
	- 尽量使用初识值列表初始化 
	- 初识值列表按声明顺序初始化, 基类成员先被初始化
8. non-local static 对象在不同编译单元的依存问题
```c++
// c++ 未规定跨编译单元 non-local static 对象的初始化顺序
// a.cpp
inline A &getA(){ // singleton保证初始化顺序
	static A a;  // 将 non-local 变为 local
	return a;
}

// b.cpp
A aa=getA();
```

	- 会产生多线程不安全, 需要在单线程启动阶段手工调用所有 return reference 函数
## 2. 构造,析构和赋值运算
1. 空类自动创建 default ctor, dctor, copy ctor 和 copy = , 调用时才自动创建
	- dctor默认为non-virtual 除非父类有virtual dctor
	- 如果数据成员是const或者引用 则相关合成拷贝函数为删除状态
2. 阻止copy
	- 将相关操作设为private, 且不实现, 类外无法访问, 类中产生链接错误
	- 或者继承 Uncopyable类
	- C++11 `=deleted` ;
```c++
class Uncopyable{
protected: // 避免被创建
	Uncopyable(){}
	~Uncopyable(){}  // 不一定为virtual 减少数据内存
private:
	Uncopyable(const Uncopyable &);
	Uncopyable &operator=(const Uncopyable &);
};
class A : private Uncopyable{...}; // private 蕴含 基于某类机制上实现出来
```

3. 派生类对象由基类(实现多态的基类)指针删除, 如果基类析构函数是non-virtual结果未定义
	- 可能派生类数据没有销毁, 产生局部销毁
	- 非实现多态的基类析构函数如果是virtual反而增加机器字长大小的vptr
	- 如果有virtual函数则析构函数声明为virtual
	- string, vector, list等等STL容器没有virtual dctor
4. 实现多态的基类可以是纯虚基类
```c++
class Base{
public:
	virtual ~Base()=0;
};
Base :: ~Base(){} // 注意增加析构函数的定义
```

5. 析构函数不鼓励抛出异常, 因为容器销毁时会发生多个异常抛出产生未定义情况
	- 捕获异常, 记录信息, 然后终止程序
	- 吞下异常, 记录信息
	- 最好设定新的close成员函数和closed标志, 给用户提供处理析构异常的机会, 然后析构函数中采取上两种之一操作
6. ctor和dtor中不要用虚函数
	- 基类中调用虚函数不会下降到派生类中,调用虚函数参考析构和构造所在类 
	- 注意ctor和dtor中的子函数也不能使用虚函数
	- 相关运行期类型信息也是基类类型
```c++
// Base中将相关虚函数变为非虚函数, 通过派生类的所传递的信息来处理
class Derived : public Base{
	Derived() : Base(createLogString()){...}
private:
	static std::string createLogString();
};
```

7. operator=写法
	- return \*this;
	- 处理自赋值 : 先复制再删除 或者 copy and swap
8. ctor, copy ctor, operator =, 非标准 operator = 密切注意每个数据成员(改动的和新加的)
	- 在派生类中务必加上基类的相关拷贝操作
	- 如果存在重复代码可以新建 private: init() 减少重复, 不能互相调用(不符合语义)
```
D::D(const D &rhs):B(rhs),....{}
D& D::operator=(const D &rhs){
	B::operator=(rhs);
	...
	return *this;
}
```

## 3. 对象管理资源
1. RAII(Resource Acquisition Is Initialization) 
	- `auto_ptr` 被复制时会被置空, C++11中被 `unique_ptr` 取代
	- `shared_ptr` 等智能指针对于默认对内置数组调用 delete 会产生错误
	- `delete [] arrname;`  一般对数组名不进行别名声明, 否则一定检查是否要加上[], 或者尽量用vector
```c++
unique_ptr<int[]> up(new int[10]()); //可以通过unique_ptr管理手动分配的数组
shared_ptr<int> sp(new int[10](), // 可以通过shared_ptr管理手动分配的数组
	[](int *p) { delete [] p;} ); // 但是必须提供删除器
```

2. 资源管理类的拷贝行为
	- 禁止复制
	- 引用计数 (shared\_ptr)
	- 深复制
	- 转移资源 (unique\_ptr)
```c++
class Lock{
public:
	Lock(Mutex *pm) : mutexPtr(pm, unlock){ 
		lock(mutexPtr.get()); 
	}
private:
	std::shared_ptr<Mutex> mutexPtr;
};
```

3. 资源管理类一般要提供底层指针
	- smartPtr.get() 返回底层指针
	- operator() 自定义隐式转换得到底层指针
4. 以独立语句将 newed 对象放入智能指针中防止表达式求值顺序未定义问题

## 4. 设计与声明
1. 让接口容易被使用,不易被误用
	- Date d(2000,1,30); -> Date d(Year(2000), Month(1), Day(30));
