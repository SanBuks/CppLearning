#pragma once
#include <string>
#include <iostream>

class Sales_data{
	friend std::istream &read(std::istream &, Sales_data &);
	friend std::ostream &print(std::ostream &, const Sales_data &);
public:
	Sales_data(const std::string &s = "") : bookNo(s){}
	Sales_data(const std::string &s, unsigned n, double price) : bookNo(s), units_sold(n), revenue(price * n){}

	Sales_data(std::istream &is = std::cin){
		read(is, *this);
	}

	std::string isbn() const { return bookNo; }
	inline double avg_price() const { 
		return (units_sold) ? revenue / units_sold : 0;
	}
	Sales_data &combine(const Sales_data &);

private:
	// isbn号
	std::string bookNo;
	// 销售数量
	unsigned units_sold = 0;
	// 总销售金额
	double revenue = 0.0;
};

Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);