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
