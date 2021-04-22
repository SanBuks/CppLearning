#include "Sales_data.h"

Sales_data &Sales_data::combine(const Sales_data &rhs){
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

Sales_data add(const Sales_data &lhs, 
  const Sales_data &rhs){
	Sales_data result = lhs;
	result.combine(rhs);
	return lhs;
}

std::ostream &print(std::ostream &os, 
  const Sales_data &rhs){
	os << "isbn : " << rhs.isbn() << " average price is "
	   << rhs.avg_price() << "$ overall is " << rhs.revenue;
	return os;
}

std::istream &read(std::istream &is, Sales_data &rhs){
	double price;
	is >> rhs.bookNo >> rhs.units_sold >> price;
	rhs.revenue = price * rhs.units_sold;
	return is;
}