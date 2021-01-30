#include "Sales_data.h"

std::ostream &operator<<(std::ostream &os, const Sales_data &item){
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
std::istream &operator>>(std::istream &is, Sales_data &item){
	is>>item.bookNo>>item.units_sold>>item.revenue;
	if(!is) item=Sales_data();
	return is;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs){
	Sales_data sum=lhs;  
	sum+=rhs;
	return sum;   		 
}
Sales_data& Sales_data::operator+=(const Sales_data &rhs){
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
Sales_data& Sales_data::operator=(const std::string &s){
	bookNo=s;
	units_sold=0;
	revenue=0.0;
	return *this;
}

bool operator==(const Sales_data & lhs, const Sales_data &rhs){
	return lhs.isbn()==rhs.isbn() &&
		   lhs.units_sold==rhs.units_sold &&
		   lhs.revenue==rhs.revenue;
}
bool operator!=(const Sales_data & lhs, const Sales_data &rhs){ return !(lhs==rhs); }
