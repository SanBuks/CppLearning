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
