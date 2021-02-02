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
> 
```c++
```
