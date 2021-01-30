# 第十四章 重载运算符与类型转换

### 1. 基本概念
- 重载运算符: 名字是运算符的特殊函数 如 `A &operator+(const A &a, const A &b);`除operator()外不能有默认实参
- 根据参数数量分为一元和二元运算符(调用运算符除外), 如果是成员函数则数量减一(默认第一个绑定为自身)
```c++
d1+d2;  // 非成员函数调用方法
operator+(d1,d2); // 同上
d1+=d2; // 调用成员函数 符合赋值一般是成员函数
d1.operator+=(d2); // 同上
```
- 不应重载 : `&&` `||` `,` (求值顺序无法保留) `&`(作用于类存在特殊含义)
- 不能重载 : `::` `.*` `.` `? :` 新的运算符, 内置类型运算符
- 应保留 : 原优先级用法, 原返回值类型, 操作含义一致, 操作类别对应 
- 内置成员函数 : `=` `[]` `()` `->` `复合赋值` `自增自减` `解引用` 
- 一般函数 : 算术运算符, 判断相等运算符, 关系运算符, 位运算符, 包含混合,对称的关系

### 2. 一般重载运算符
#### 输入和输出运算符
- 包含标准流对象所以函数都为非成员
- 输出需要减少格式控制给用户空间
- 输入需要在一次输入完成后检查流的状态, 发生错误则需要将输入的对象置于安全状态
- 输入时需要检查文本格式, 可以通过设置流的标识控制输入流程
```c++
class A{
friend std::ostream &operator<<(std::ostream &os, const Sales_data &item);  // 输出重载
friend std::istream &operator>>(std::istream &is, Sales_data &item);  // 输入重载
};  
```

#### 算术运算符
> 参数大都为常量引用

- 非成员函数, 注意委托赋值运算符
```c++
Sales_data operator+(const Sales_data & lhs, const Sales_data &rhs){
	Sales_data sum=lhs;  // 拷贝构造
	sum+=rhs;  // 委托赋值运算符(节省)
	return sum;  // 值返回
}
```
#### 判断相等运算符
- 非成员函数, 一般同时定义`!=` 和`==`,且委托其中一个
```c++
bool operator==(const Sales_data & lhs, const Sales_data &rhs);
bool operator!=(const Sales_data & lhs, const Sales_data &rhs){
	return !(lhs==rhs);
}
```

#### 比较运算符
- 非成员函数, 类存在严格弱序, 严格弱序与==产生结果一致
#### 赋值运算符
- 成员函数, 注意赋值需要先将原对象销毁
```c++
StrVec &StrVec::operator=(std::initializer_list<std::string> il){
	auto newdata=alloc_n_copy(il.begin(), il.end());
	free();
	elements=newdata.first;
	first_free=cap=newdata.second;
	return *this;
}
```
#### 下标运算符
- 成员函数, 通常会定义两个版本, 返回常量引用和返回普通引用
```c++
std::string &operator[](size_t n){ return elements[n]; }
const std::string &operator[](size_t n){ return elements[n]; }
```
#### 递增递减运算符
- 成员函数, 前置返回引用, 后置返回值 
```c++
StrBlobPtr& StrBlobPtr::operator--(){
	curr--;
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}
StrBlobPtr StrBlobPtr::operator--(int){  // (int) 标志为后置, 编译器默认提供0为参数
	auto ret=*this; // 保存之前状态
	--*this;
	return ret;
}
// p.operator++(0); 显示调用后置运算符
```

#### 访问运算符
- 成员函数, 其中箭头运算符保留成员访问的含义 如 `pointer->mem;`
	- 内置指针则等价于`(*pointer).mem;` 
	- 类对象等价于`pointer.operator()->mem`  返回值为指针则同上否则递归结算到指针或错误信息
```c++
std::string & operator*() const {
    auto def=check(curr, "deref past end");
    return (*def)[curr];
}
std::string * operator->() const {
    return & this->operator*();
}
```

### 3. 调用运算符
- 成员函数, 定义了调用运算符的类称作调用对象, 可以像函数一样地调用它, 也可以运用到泛型算法中
- lambda表达式是函数对象, 产生相应的类, 类中含有相应的数据成员对应捕获的类型值, 如果是值捕获则不改变原来的初识值, 调用函数为const
- 标准库的函数对象如 `plus<A> plusobj;` 可以简化自定义的流程, 其中调用对应类的操作符完成相应操作, 特别的, 可以对指针地址进行比较
- function模板类解决多种调用对象类型不一的问题
```c++
function<int(int, int)> f1	
=add;      // 函数指针
=Divide(); // 函数类无名对象
=[](const int &e){ return 0; } // lambda表达式
map<string, function<int(int, int)>> mp;
// 存放重载函数对象时会发生命名冲突, 可以通过使用指针或lambda解决
```
> 函数对象定义在`<functional>`头文件中

### 4. 类型转换与重载
#### 用户定义的类型转换
- 类 类型转换 :
	- 转换构造函数 ( 单参数 ) : arg -> classobj
	- 类型转换运算符 ( type() ) : classobj -> type
- 隐式的用户定义类型转换可以发生在内置类型转换之前或之后, 并一起使用
```c++
class SmallInt{...}; // 定义了 int -> SmallInt -> int
SmallInt si=3.14; // 3.14 -> int -> SmallInt
si+3.14; // si -> int -> double
```

- 显示类型转换 `explicit operator int() const { return val; }` 防止意外转换发生, 调用`static_cast<int>(si)` 进行转换
> 显示类型转换有一个例外, 表达式被用于条件会隐式调用类型转换, 根据此特性将 `bool()` 定义为`explicit`

#### 类型转换运算符
- 成员函数, const, 无参, 无显示返回类型
```c++
operator type() const { ... return typeA; }
// 1. type即隐式返回类型
// 2. type不可为数组类型, 函数类型, 因为无法作为返回类型
// 3. typeA类型必须符合type
```

#### 避免二意性
- 相同路经转换 : 
```c++
class A{}; // 定义了 B->A的转换构造函数
class B{}; // 定义了 B->A的类型转换运算符
A ff(const A &b); B b;
ff(b); // 发生歧义只能显示
// f(A(b));
// f(b.operatorA());
```

- 同目标转换 : 
```c++
struct Integral {
	int a=10;
	operator double() const { return 10; }
	operator short() const { return 10; }
};

void f1(int ld) { std::cout<<ld<<std::endl; }
void f2(long long ld) { std::cout<<ld<<std::endl; }

int main(){
	Integral ci;
	f1(ci);	  // short 发生整型提升优于算数类型转换 没有歧义
	f2(ci);	  // 都发生算数类型转换 产生歧义
	return 0;
}
```

- 同源转换 : 
```c++
class A{}; // 定义了 int -> A
class B{}; // 定义了 int -> B
void ff(const A &);
void ff(const B &);
ff(10); // 发生int转换的重载歧义
/* --------------------------------------- */
class A{};  // 定义了 double -> A
class B{}; // 定义了 int -> B
void ff(const A &);
void ff(const B &);
ff(10); 
// 参数 10 需要转换, 寻找匹配过程中定级为最后一级即自定义的类型转化
// 其中 int -> B 优先级高与 int -> double -> A
```

> 避免两个类发生同路经转换, 避免重复定义目标是算术类型的类型转换, 避免两个类发生重载

- 成员函数和非成员函数重载
```c++
friend A operator+(const A &lhs, const A &rhs);
A operator+(const A &rhs);
A a3=a1+a2; // 发生歧义
```
