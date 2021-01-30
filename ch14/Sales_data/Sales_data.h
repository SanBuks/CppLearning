#pragma once

#include <iostream>
#include <cstring>

class Sales_data{
friend std::ostream &operator<<(std::ostream &os, const Sales_data &item);
friend std::istream &operator>>(std::istream &is, Sales_data &item);
friend Sales_data operator+(const Sales_data & lhs, const Sales_data &rhs);
friend bool operator==(const Sales_data & lhs, const Sales_data &rhs);
friend bool operator!=(const Sales_data & lhs, const Sales_data &rhs);
protected:
	std::string bookNo;
	unsigned units_sold=0;  // 销售量
	double revenue=0.0;  // 总销售额
	double avg_price() const { return (units_sold!=0 ? revenue/units_sold : 0); }
	
public:
	Sales_data()=default;
	Sales_data(const std::string &s, unsigned n, double p):bookNo(s), units_sold(n), revenue(p){}
	explicit Sales_data(const std::string &s):bookNo(s){}
	explicit Sales_data(std::istream &);

	std::string isbn() const { return bookNo; }
	Sales_data& operator+=(const Sales_data &);
	Sales_data& operator=(const std::string &);
	
	explicit operator std::string() const { return bookNo; }
	explicit operator double() const { return revenue; }
};
