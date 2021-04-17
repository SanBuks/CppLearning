### 2. RTTI
#### dynamic\_cast
- 使用形式 : 
    - `dynamic_cast<type *>(e)` :  e是有效指针
    - `dynamic_cast<type &>(e)` : e是左值
    - `dynamic_cast<type &&>(e)` : e不是左值, 必须为右值
- 要求 : 一般 e 是多态类, 要对转换结果进行及时处理
- 返回值 : 如果成功返回对应类型, 如果失败返回 空指针(指针类型) 或 (抛出std::bad_cast \<typeinfo>) 


#### 转换规则
1. e类型与type相同 或者 e类型多出cv性质 ( 与\static_cast相同增加cv性质 )
2. e是值为null的任意类型指针, 结果为值为null的type指针
3. type是指向Base的指针或引用, e类型是指向Derived的指针或引用, 在Derived中Base是确切且公有部分可访问, 结果为指针或引用指向 在Derived对象中的 Base 类 subobject 对象
4. e是指向多态类的指针或引用, type是void指针, 结果为 指向most derived object的指针或引用
5. e是指向多态类的指针或引用, type是指向Derived类的引用或指针 运行时检查执行: 
    - 针对e, the  most derived object首先检测出来, 针对此对象, 如果e是指向Derived的公有基类的指针或引用 而且 这个被Derived指针或绑定的对象是唯一从 e的subobject 派生出来, 结果转换为指向Derived对象的指针或引用 (向下转化, 范围为 [ type(e), type(the most derived object) ] )
    - 另一个情况, 这个被Derived指针或绑定的对象不是唯一从 e的subobject 派生出来, 则存在基类的二意性, 结果也转换为指向Derived对象的指针或引用 (向侧方向转换)
    - 其他情况则检查失败返回空指针或者std::bad\_alloc
6. 在构造函数或者析构函数中转换时, e所指的对象在构造函数或析构函数中, 则被视为所在类型的the most derived object, 如果e的静态类型不是指向构造或析构函数所在类型或其基类的指针或引用, 结果未定义

#### typeid
- 返回对象 :  type\_info类 或 type\_info公有派生类对象的常量引用, 记录类型的信息
- 作用对象 : 
    - 忽略顶层const,如果是 
    - 引用以其绑定类型为准 
    - 会保留数组类型
    - typeid(&ref) 以静态类型准
> 作用对象不是类类型或是不包含虚函数的类则编译期直接返回静态类型, 如果是定义了包含至少一个虚函数的类的左值, 运行期返回动态类型
```c++
if(typeid(*bp)==typeid(*dp)) {} // 如果指针非法抛出 bad_typeid 异常
if(typeid(ClassName)==typeid(*bp)) {}
if(typeid(bp)==typeid(dp)) {}  // 如果比较指针, 怎比较两者静态类型, 注意避免这种情况
```

#### 继承体系下 RTTI
```c++
class Base{
friend bool operator==(const Base &, const Base &);
protected: 
	virtual bool equal(const Base &) const;
};
// 实际的比较工作包含 typeid
bool operator==(const Base &lhs, const Base &rhs){
	return typeid(lhs)==typeid(rhs) && lhs.equal(rhs);
}

// 将其他比较工作委托给 equal
bool Base::equal(const Base &rhs) const {
	...
}

class Derived : public Base{
protected: 
	bool equal(const Base &) const override; // 注意 
};

// 首先转换为派生类型, 因为 首先 typeid(lhs)==typeid(rhs) 后, 再调用永远不会失败
// 然后调用基类equal 然后 比较自身数据成员
bool Derived::equal(const Base &rhs) const {
	auto r=dynamic_cast<const Derived &>(rhs);
	return Base::equal(r) && ...;
}
```

#### typeinfo
- 没有默认构造函数, 拷贝赋值操作删除, 只能通过typeid运算符生成(常量)
- t.name() 返回对象类名C风格字符串
- t.before(v) 判断t是否位于v前, 顺序依赖与编译器
- == , != 比较运算符 