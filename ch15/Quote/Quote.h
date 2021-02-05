#pragma once
#include <iostream>
#include <utility>

class Quote{
private:
	std::string bookNo;  // ISBN 编号
protected:
	double price=0.0;  // 不打折的原价格
public:
	Quote()=default;
	Quote(const std::string &book, const double &sales_price):
		bookNo(book), price(sales_price){}

	Quote(const Quote &);
	Quote &operator=(const Quote&)&;
	
	Quote(Quote &&) noexcept ;
	Quote &operator=(Quote &&) & noexcept ;

	virtual ~Quote()=default;

	// 返回购买n本书后应付的总价格
	virtual double net_price(std::size_t n) const { return n*price; }
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() && { return new Quote(std::move(*this)); }

	virtual void debug(){ std::cout<<"bookNo: "<<bookNo<<" price: "<<price; }
	std::string isbn() const { return bookNo; }
};

double print_total(std::ostream &os, const Quote &item, size_t n){
	double ret=item.net_price(n);
	os<<"ISBN: "<<item.isbn()<<" sold: "<<n<<" total due: "<<ret<<std::endl;
	return ret;
}


Quote::Quote(const Quote &rhs):bookNo(rhs.bookNo),price(rhs.price){}
Quote &Quote::operator=(const Quote &rhs)&{
	if(this==&rhs)
		return *this;
	bookNo=rhs.bookNo;
	price=rhs.price;
	return *this;
}

Quote::Quote(Quote &&rhs) noexcept : bookNo(std::move(rhs.bookNo)), price(rhs.price){}
Quote &Quote::operator=(Quote &&rhs) & noexcept {
	if(this==&rhs)
		return *this;
	bookNo=std::move(rhs.bookNo);
	price=rhs.price;
	return *this;
}
