#pragma once
#include <iostream>
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
	virtual void debug(){ std::cout<<"bookNo: "<<bookNo<<" price: "<<price; }
	std::string isbn() const { return bookNo; }
};

double print_total(std::ostream &os, const Quote &item, size_t n){
	double ret=item.net_price(n);
	os<<"ISBN: "<<item.isbn()<<" sold: "<<n<<" total due: "<<ret<<std::endl;
	return ret;
}
