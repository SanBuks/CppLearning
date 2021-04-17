# 第 十九 章
### 19.03
>已知存在如下的类继承体系，其中每个类分别定义了一个公有的默认构造函数和一个析构函数：下面哪个 dynamic_cast 将失败？
```c++
class A { /* ... */};
class B : public A { /* ... */};
class C : public B { /* ... */};
class D : public B, public A { /* ... */};

A *pa = new C;
B *pb = dynamic_cast<B*>(pa);

B *pb = new B;
C *pc = dynamic_cast<C*>(pb);

A *pa = new D;
B *pb = dynamic_cast<B*>(pa);
```

参考 19.04

### 19.04\*
> 使用上一个练习定义的类改写下面的代码，将表达式\*pa 转换成类型C&：
```c++
#include <iostream>
#include <typeinfo>

class A{ 
public : 
	A()=default;
	virtual ~A(){} 
};

class B: public A{ 
public : 
	B()=default;
	virtual ~B(){} 
};

class C: public B{ 
public : 
	C()=default;
	virtual ~C(){} 
};


class D: public B, public A{ 
public : 
	D()=default;
	virtual ~D(){} 
};

int main(){
	A *pc=new C; // 成功
	if(dynamic_cast<B*>(pc)){ std::cout<<"C->B : success"<<std::endl; }
	else { std::cout<<"C->B : failure"<<std::endl; }

	B *pb=new B;  // 转换失败, pb的 the most derived object 是 B类型
	if(dynamic_cast<C*>(pb)){ std::cout<<"B->C : success"<<std::endl; }
	else { std::cout<<"B->C : failure"<<std::endl; }

/*
	A *pd=new D; // D重复继承A的部分, 产生歧义
	if(dynamic_cast<B*>(pd)){ std::cout<<"D->B : success"<<std::endl; }
	else { std::cout<<"D->B : failure"<<std::endl; }
*/

	return 0;
}
```

### 19.05
> 在什么情况下你应该用 dynamic_cast 替代虚函数？

通过基类指针或引用执行某个派生类操作且该操作不是虚函数时使用


### 19.06\*
> 编写一条表达式将 Query\_base 指针动态转换为 AndQuery 指针。分别使用 AndQuery 的对象以及其他类型的对象测试转换是否有效。打印一条表示类型转换是否成功的信息，确保实际输出的结果与期望的一致。
```c++
// 动态转换测试的函数封装在 Query类中, 在其他查询类中增加Query友元
void Query::dynamicRTest(){
	shared_ptr<WordQuery> pl(new WordQuery("wl"));
	shared_ptr<WordQuery> pr(new WordQuery("wr"));

	shared_ptr<WordQuery> wq(new WordQuery("wq"));
	toRAndQueryDynamicTest(*wq);

	shared_ptr<NotQuery> nq(new NotQuery(wq));
	toRAndQueryDynamicTest(*nq);

	shared_ptr<BetweenQuery> bq(new BetweenQuery(1, 1, wq));
	toRAndQueryDynamicTest(*bq);
	
	shared_ptr<OrQuery> oq(new OrQuery(pl, pr));
	toRAndQueryDynamicTest(*oq);

	shared_ptr<AndQuery> aq(new AndQuery(pl, pr));
	toRAndQueryDynamicTest(*aq);
}

void Query::toRAndQueryDynamicTest(Query_base &p){
	try{
		AndQuery &ap=dynamic_cast<AndQuery &>(p);
		cout<<typeid(p).name()<<" -> "<<typeid(ap).name()<<" : success "<<std::endl;
	}catch(const std::bad_cast &){
		cout<<typeid(p).name()<<" -> "<<typeid(AndQuery).name()<<" : faliure "<<std::endl;
	}
}

void Query::dynamicPTest(){
	shared_ptr<WordQuery> wp(new WordQuery("wp"));
	shared_ptr<WordQuery> pl(new WordQuery("wl"));
	shared_ptr<WordQuery> pr(new WordQuery("wr"));

	Query_base *p=new WordQuery("wq");
	toPAndQueryDynamicTest(p);

	p=new NotQuery(wp);
	toPAndQueryDynamicTest(p);

	p=new BetweenQuery(1, 1, wp);
	toPAndQueryDynamicTest(p);
	
	p=new OrQuery(pl, pr);
	toPAndQueryDynamicTest(p);

	p=new AndQuery(pl, pr);
	toPAndQueryDynamicTest(p);
}

void Query::toPAndQueryDynamicTest(Query_base *p){
	if(AndQuery *ap=dynamic_cast<AndQuery *>(p))
		cout<<typeid(*p).name()<<" -> "<<typeid(*ap).name()<<" : success "<<std::endl;
	else cout<<typeid(*p).name()<<" -> "<<typeid(AndQuery).name()<<" : faliure "<<std::endl;
	delete p;
}
```

```bash
# 结果 : 
----------Pointer dynamic_cast Test----------
9WordQuery -> 8AndQuery : faliure 
8NotQuery -> 8AndQuery : faliure 
12BetweenQuery -> 8AndQuery : faliure 
7OrQuery -> 8AndQuery : faliure 
8AndQuery -> 8AndQuery : success 
----------Reference dynamic_cast Test----------
9WordQuery -> 8AndQuery : faliure 
8NotQuery -> 8AndQuery : faliure 
12BetweenQuery -> 8AndQuery : faliure 
7OrQuery -> 8AndQuery : faliure 
8AndQuery -> 8AndQuery : success
```


### 19.07
> 编写与上一个练习类似的转换，这一次将 Query_base 对象转换为 AndQuery 的引用。重复上面的测试过程，确保转换能正常工作。

见１9.06

### 19.08
> 编写一条 typeid 表达式检查两个 Query_base 对象是否指向同一种类型。再检查该类型是否是 AndQuery。
```c++
bool operator==(const Query_base &lhs, const Query_base &rhs){
	return (typeid(lhs)==typeid(rhs)) && (typeid(lhs)==typeid(AndQuery));
}
```

### 19.09\*
> 编写与本节最后一个程序类似的代码，令其打印你的编译器为一些常见类型所起的名字。如果你得到的输出结果与本书类似，尝试编写一个函数将这些字符串翻译成人们更容易读懂的形式。
```c++
#include <iostream>
#include <string>
#include <typeinfo>
#include <stdexcept>

class Sales_data{};

class Base{
friend bool operator==(const Base &, const Base &);
private:
	int data;
public:
	Base(int a=10):data(a){}
protected: 
	virtual bool equal(const Base &) const;
};

bool operator==(const Base &lhs, const Base &rhs){
	return typeid(lhs)==typeid(rhs) && lhs.equal(rhs);
}

bool Base::equal(const Base &rhs) const {
	return this->data==rhs.data;
}

class Derived : public Base{
private:
	int data;
public:
	Derived(int a=10, int c=20):Base(a), data(c){}
protected: 
	bool equal(const Base &) const override;
};

bool Derived::equal(const Base &rhs) const {
	auto r=dynamic_cast<const Derived &>(rhs);
	return Base::equal(r) && this->data==r.data;
}

int main(){
	int arr[10];
	Derived d;
	std::cout << typeid(42).name() << ", "
			  << typeid(arr).name() << ", "
			  << typeid(Sales_data).name() << ", "
			  << typeid(std::string).name() << ", "
			  << typeid(p).name() << ", "
			  << typeid(*p).name() << std::endl;

	return 0;
}

// i, A10_i, 10Sales_data, NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, P4Base, 7Derived
```

### 19.10\*
> 已知存在如下的类继承体系，其中每个类定义了一个默认公有的构造函数和一个虚析构函数。下面的语句将打印哪些类型名字？
```c++
#include <iostream>
#include <typeinfo>
#include <stdexcept>

using std::cout;
using std::endl;

class A { 
public:
	A()=default;
	virtual ~A(){}
};

class B : public A { 
public:
	B()=default;
	virtual ~B(){}
};

class C : public B {
public:
	C()=default;
	virtual ~C(){}
};

int main(){
	A *pa = new C;
	cout << typeid(pa).name() << endl;
	// P1A

	C cobj;
	A& ra1 = cobj;
	cout << typeid(&ra1).name() << endl;
	// P1A

	B *px = new B;
	A& ra2 = *px;
	cout << typeid(ra2).name() << endl;
	// 1B	
    return 0;
}
```