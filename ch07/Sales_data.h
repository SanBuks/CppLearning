#pragma once
#include <string>
class Sales_data{
public:
	std::string isbn() const { return bookNo; }
	double avg_price() const { 
		return (units_sold) ? revenue / units_sold : 0;
	}
	Sales_data &combine(const Sales_data &);

private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::ostream &, Sales_data &);
