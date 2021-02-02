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

