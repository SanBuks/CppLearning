# 第 十五 章 习题
### 15.01
> 什么是虚成员？

- 在类内中声明为 virtual 的函数, 其中 virtual 可以修饰非构造非静态函数, 只能在类中声明
- 虚函数在派生类中隐式为派生类, 也可以被override, 在运行时根据对象类型的不同调用不同的虚函数

### 15.02
> protected 访问说明符与 private 有何区别？

- protected 禁止用户调用其成员, 可以让派生类函数和友元调用
- private 禁止用户调用其成员, 禁止派生类函数和友元调用

### 15.03
> 定义你自己的 Quote 类和 print_total 函数。

```c++
class Quote{
private:
	std::string bookNo;  // ISBN 编号
protected:
	double price=0.0;  // 不打折的原价格
public:
	Quote()=default;
	Quote(const std::string &book, const double &sales_price):
		bookNo(book), price(sales_price){}
	virtual ~Quote()=default;

	// 返回购买n本书后应付的总价格
	virtual double net_price(std::size_t n) const { return n*price; }

	std::string isbn() const { return bookNo; }
};

double print_total(std::ostream &os, const Quote &item, size_t n){
	double ret=item.net_price(n);
	os<<"ISBN: "<<item.isbn()<<" sold: "<<n<<" total due: "<<ret<<std::endl;
	return ret;
}
```

### 15.04
> 下面哪条声明语句是不正确的？请解释原因。
```c++
class Base { ... };
class Derived : public Derived { ... };  // 不可自继承
class Derived : private Base { ... }; // 正确
class Derived : public Base; // 声明不用派生列表
```

### 15.05
> 定义你自己的 Bulk_quote 类。
```c++
#pragma once
#include "Quote.h"

class Bulk_quote : public Quote{
private:
	std::size_t min_qty=0;
	double discount=0.0;
public:
	Bulk_quote()=default;
	Bulk_quote(const std::string &book, const double &p, std::size_t qty, const double &disc):
		Quote(book, p), min_qty(qty), discount(disc){}
	double net_price(std::size_t ) const override;
};

double Bulk_quote::net_price(std::size_t cnt) const {
	if(cnt>=min_qty) return cnt*(1-discount)*price;
	else return cnt*price;
}
```
### 15.06
> 将 Quote 和 Bulk_quote 的对象传给15.2.1节练习中的 print_total 函数，检查该函数是否正确。
```c++
#include <iostream>
#include "Bulk_quote.h"
#include "LBulk_quote.h"

int main(){
	Quote q("quote q", 23.3f);
	Bulk_quote bq("bulk_quote bq", 23.3f, 25, 0.2f); 
	LBulk_quote lbq("lbulk_quote lbq", 23.3f, 25, 80, 0.2f); 
	print_total(std::cout, q, 100);  
	print_total(std::cout, bq, 100);  
	print_total(std::cout, lbq, 100);  
	return 0;
}
```

### 15.07
> 定义一个类使其实现一种数量受限的折扣策略，具体策略是：当购买书籍的数量不超过一个给定的限量时享受折扣，如果购买量一旦超过了限量，则超出的部分将以原价销售。 
```c++
#pragma once
#include "Quote.h"

class LBulk_quote : public Quote{
private:
	std::size_t min_qty=0;
	std::size_t max_qty=0;
	double discount=0.0;
public:
	LBulk_quote()=default;
	LBulk_quote(const std::string &book, const double &p, 
			std::size_t miqty, std::size_t maqty, const double &disc):
			Quote(book, p), min_qty(miqty), max_qty(maqty), discount(disc){}
	double net_price(std::size_t ) const override;
};

double LBulk_quote::net_price(std::size_t n) const {
	if(n<min_qty) return n*price;
	if(n>=min_qty && n<=max_qty) return n*price*(1-discount);
	if(n>max_qty) return (n-max_qty)*price+max_qty*price*(1-discount);
}
```

### 15.08
> 给出静态类型和动态类型的定义。

- 静态类型在编译时已知, 是定义时声明的类型
- 动态类型在运行时才知, 表示内存中的对象类型

### 15.09
> 在什么情况下表达式的静态类型可能与动态类型不同？请给出三个静态类型与动态类型不同的例子。

通过指针和引用调用对象接口时, 例子略

### 15.10
> 回忆我们在8.1节进行的讨论，解释第284页中将 ifstream 传递给 Sales_data 的read 函数的程序是如何工作的。

std::istream 是 std::ifstream 的基类, 存在动态绑定

### 15.11
> 为你的 Quote 类体系添加一个名为 debug 的虚函数，令其分别显示每个类的数据成员。
```c++
// Quote.h
virtual void debug(){ std::cout<<"bookNo: "<<bookNo<<" price: "<<price; }
// Bulk_quote.h
void debug() override { 
    Quote::debug();
    std::cout<<" min_qty: "<<min_qty<<" discount: "<<discount; 
}
```

### 15.12
> 有必要将一个成员函数同时声明成 override 和 final 吗？为什么？

override 表示覆盖基类的虚函数
final 表示声明的虚函数不能被派生类覆盖
二者没有直接关系

### 15.13
> 给定下面的类，解释每个 print 函数的机理：在上述代码中存在问题吗？如果有，你该如何修改它？
```c++
class base {
public:
	string name() { return basename;}
	virtual void print(ostream &os) { os << basename; }
private:
	string basename;
};

class derived : public base {
public:
	void print(ostream &os) {   // 覆盖父类虚函数
		print(os);   // 修改为 base::print(os);
		os << " " << i; 
	}
private:
	int i;
};
```

### 15.14
> 给定上一题中的类以及下面这些对象，说明在运行时调用哪个函数：
```c++
base bobj; 		base *bp1 = &bobj; 	base &br1 = bobj;
derived dobj; 	base *bp2 = &dobj; 	base &br2 = dobj;

bobj.print();	// 静态 base		
dobj.print();	// 静态 derived

bp1->name();	// 静态 base 非虚函数
bp2->name();	// 静态 derived 非虚函数	

br1.print();    // 动态 base
br2.print();    // 动态 derived
```

### 15.15
> 定义你自己的 Disc_quote 和 Bulk_quote。
```c++
// Disc_quote
#pragma once
#include "Quote.h"
class Disc_quote:public Quote{
protected:
	double price=0.0;  
	std::size_t quantity=0;  // 折扣适用的购买量
	double discount=0.0;    // 折扣
public:
	Disc_quote()=default;
	Disc_quote(const std::string &book, const double &p, std::size_t qty, const double &disc):
		Quote(book, p), quantity(qty), discount(disc){}
	double net_price(std::size_t ) const=0;
	void debug() override { 
		Quote::debug();
		std::cout<<" quantity: "<<quantity<<" discount: "<<discount; 
	}
};

// Bulk_quote
#pragma once
#include "Disc_quote.h"
class Bulk_quote : public Disc_quote{
public:
	Bulk_quote()=default;
	Bulk_quote(const std::string &book, const double &p, std::size_t qty, const double &disc):
		Disc_quote(book, p, qty, disc){}
	double net_price(std::size_t ) const override;
};
double Bulk_quote::net_price(std::size_t cnt) const {
	if(cnt>=quantity) return cnt*(1-discount)*price;
	else return cnt*price;
}
```

### 15.16
> 改写你在15.2.2节练习中编写的数量受限的折扣策略，令其继承 Disc_quote。
```c++
#pragma once
#include "Disc_quote.h"

class LBulk_quote : public Disc_quote{
private:
	std::size_t max_qty=0;
public:
	LBulk_quote()=default;
	LBulk_quote(const std::string &book, const double &p, 
			std::size_t miqty, std::size_t maqty, const double &disc):
			Disc_quote(book, p, miqty, discount), max_qty(maqty){}
	double net_price(std::size_t ) const override;
	void debug() override { 
		Disc_quote::debug();
		std::cout<<" max_qty: "<<max_qty;
	}
};

double LBulk_quote::net_price(std::size_t n) const {
	if(n<quantity) return n*price;
	if(n>=quantity && n<=max_qty) return n*price*(1-discount);
	if(n>max_qty) return (n-max_qty)*price+max_qty*price*(1-discount);
	return 0;
}
```

### 15.17
> 尝试定义一个 Disc_quote 的对象，看看编译器给出的错误信息是什么？

cannot declare variable ‘dq’ to be of abstract type ‘Disc_quote’

### 15.18
> 假设给定了第543页和第544页的类，同时已知每个对象的类型如注释所示，判断下面的哪些赋值语句是合法的。解释那些不合法的语句为什么不被允许：
```c++
Base *p = &d1;  //d1 的类型是 Pub_Derv - 用户合法
p = &d2;		//d2 的类型是 Priv_Derv - 用户非法
p = &d3;		//d3 的类型是 Prot_Derv - 用户非法
p = &dd1;		//dd1 的类型是 Derived_from_Public	- 用户合法
p = &dd2;		//dd2 的类型是 Derived_from_Private - 用户非法
p = &dd3;		//dd3 的类型是 Derived_from_Protected - 用户非法
```

### 15.19
> 假设543页和544页的每个类都有如下形式的成员函数：
```c++
void memfcn(Base &b) { b = *this; }
Base *p = &d1;  //d1 的类型是 Pub_Derv - 派生类中合法
p = &d2;		//d2 的类型是 Priv_Derv - 派生类中合法
p = &d3;		//d3 的类型是 Prot_Derv - 派生类中合法
p = &dd1;		//dd1 的类型是 Derived_from_Public	- 派生类中合法
p = &dd2;		//dd2 的类型是 Derived_from_Private - 派生类中非法
p = &dd3;		//dd3 的类型是 Derived_from_Protected - 派生类中合法
```

### 15.20
> 编写代码检验你对前面两题的回答是否正确。

参考 summary

### 15.21
> 从下面这些一般性抽象概念中任选一个（或者选一个你自己的），将其对应的一组类型组织成一个继承体系：

(a) 图形文件格式（如gif、tiff、jpeg、bmp）
(b) 图形基元（如方格、圆、球、圆锥）
(c) C++语言中的类型（如类、函数、成员函数）


### 15.22
> 对于你在上一题中选择的类，为其添加函数的虚函数及公有成员和受保护的成员。
```c++
// Shape2D.h
#pragma once
#include <utility>
#include <string>
#include <iostream>

class Shape2D{
public:
	Shape2D(const std::string &i, const std::string &n):id(i), name(n){}
	Shape2D():id("00000"), name("Default_Name"){ } 
	~Shape2D(){}
	virtual double getArea() const =0; 
	virtual double getPerimeter() const =0;
	virtual void printInfo() const;
protected:
	std::string id;
	std::string name;
};
void Shape2D::printInfo()const{ std::cout<<"id: "<<id<<" name: "<<name<<std::endl; }

// Rectangular.h
#pragma once
#include "Shape2D.h"
class Rectangular: public Shape2D{
public:
	typedef std::pair<double, double> Coordinate;
	typedef std::pair<Coordinate, double> Position;

	Rectangular(const std::string &i, const std::string &n, 
			double len, double wid,  // size 
			double llxx, double llyy, double ang):  // position
			Shape2D(i,n), length(len), width(wid), llx(llxx), lly(llyy), angle(ang){}
	Rectangular():Shape2D(), length(0.0), width(0.0), llx(0.0), lly(0.0), angle(0.0){}

	double getArea() const override { return length*width; }
	double getPerimeter() const override { return 2*(length+width); }
	void printInfo() const override; 
	virtual Position getPosition() const { return {{llx, lly}, angle}; }
	
protected:
	double length, width;  // 长宽
	double llx, lly;  // 左下角坐标
	double angle;  // 逆时针最底边的角度
};

void Rectangular::printInfo() const { 
	Shape2D::printInfo();
	std::cout<<"length: "<<length<<" width: "<<width<<std::endl;
	std::cout<<"coordinate: "<<llx<<", "<<lly<<" angle: "<<angle<<std::endl;
}
```

### 15.23
> 假设第550页的 D1 类需要覆盖它继承而来的 fcn 函数，你应该如何对其进行修改？如果你修改之后 fcn 匹配了 Base 中的定义，则该节的那些调用语句将如何解析？
```c++
int fcn(int); -> int fcn();
// 对于 fcn()	的调用遵循动态绑定
```

### 15.24
> 哪种类需要虚析构函数？虚析构函数必须执行什么样的操作？

- 基类需要定义虚析构函数
- 先销毁属于自己的数据成员然后沿继承链不断向上重复过程

### 15.25
> 我们为什么为 Disc_quote 定义一个默认构造函数？如果去掉该构造函数的话会对 Bulk_quote 的行为产生什么影响？

Disc_quote 自定义了一个构造函数不会合成默认构造函数, 如果没有定义父类的默认构造函数则Bulk_quote 的默认构造函数无法调用

### 15.26
> 定义 Quote 和 Bulk_quote 的拷贝控制成员，令其与合成的版本行为一致。为这些成员以及其他构造函数添加打印状态的语句，使得我们能够知道正在运行哪个程序。使用这些类编写程序，预测程序将创建和销毁哪些对象。重复实验，不断比较你的预测和实际输出结果是否相同，直到预测完全准确再结束。
```c++
// 以 Disc_quote.h 为例
Disc_quote::Disc_quote(const Disc_quote &rhs):
	Quote(rhs), quantity(rhs.quantity), discount(rhs.discount){} 

Disc_quote::Disc_quote(const Disc_quote &&rhs):
	Quote(std::move(rhs)), quantity(std::move(rhs.quantity)), discount(std::move(rhs.discount)) noexcept {} 

Disc_quote &Disc_quote::operator=(const Disc_quote &rhs)&{
	if(this==&rhs)
		return *this;
	Quote::operator=(rhs);
	quantity=rhs.quantity;
	discount=rhs.discount;
	return *this;
}
Disc_quote &Disc_quote::operator=(const Disc_quote &&rhs)& noexcept {
	if(this==&rhs)
		return *this;
	Quote::operator=(std::move(rhs));
	quantity=std::move(rhs.quantity);
	discount=std::move(rhs.discount);
	return *this;
}
// 拷贝控制: 顺序从继承链顶至底
// 析构: 顺序从继承链底至顶
```

### 15.27
> 重新定义你的 Bulk_quote 类，令其继承构造函数。
```c++
class Bulk_quote : public Disc_quote{
public:
	using Disc_quote::Disc_quote;  // 没有数据成员 直接继承父类构造函数
	Bulk_quote()=default;
	Bulk_quote(const Bulk_quote&);
	Bulk_quote &operator=(const Bulk_quote&)&;
	double net_price(std::size_t ) const override;
};
```

### 15.28
>  定义一个存放 `Quote` 对象的 `vector`，将 `Bulk_quote` 对象传入其中。计算 `vector` 中所有元素总的 `net_price`。
```c++
void vector_test(){
	double sum=0.0;
	std::vector<std::shared_ptr<Quote>> vec;
	vec.push_back(std::make_shared<Quote>("Quote q", 50));
	vec.push_back(std::make_shared<Bulk_quote>("Bulk_quote bq", 23.3, 25, 0.2));
	for(const auto &it : vec)
		sum+=it->net_price(80);
	std::cout<<sum<<std::endl;  // $ = 5491.2
}
```

### 15.29
> 再运行一次你的程序，这次传入 Quote 对象的 shared_ptr 。如果这次计算出的总额与之前的不一致，解释为什么;如果一直，也请说明原因。

对象根据动态类型进行动态绑定, 执行Quote的虚函数, 产生不一样的总额

### 15.30
> 编写你自己的 Basket 类，用它计算上一个练习中交易记录的总价格。
```c++
#pragma once
#include <iostream>
#include <set>
class Basket{
public:
	void add_item(const Quote &sale){
		items.insert( std::shared_ptr<Quote>(sale.clone()) );
	}
	void add_item(Quote &&sale){
		items.insert( std::shared_ptr<Quote>(std::move(sale).clone()) );
	}
	double total_receipt(std::ostream &) const;
private:
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs){
		return lhs->isbn()<rhs->isbn();
	}
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};
double Basket::total_receipt(std::ostream &os) const{
	double sum=0.0;
	for(auto it=items.cbegin(); it!=items.cend(); it=items.upper_bound(*it))
		sum+=print_total(os, **it, items.count(*it));
	os<<"Total sum: "<<sum<<std::endl;
	return sum;
}
```