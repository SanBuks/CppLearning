#pragma once
#include "Quote.h"
class Disc_quote:public Quote{
protected:
	std::size_t quantity=0;  // 折扣适用的购买量
	double discount=0.0;    // 折扣
public:
	Disc_quote()=default;
	Disc_quote(const std::string &book, const double &p, std::size_t qty, const double &disc):
		Quote(book, p), quantity(qty), discount(disc){}

	Disc_quote(const Disc_quote &);
	Disc_quote &operator=(const Disc_quote &)&;

	Disc_quote(Disc_quote &&) noexcept;
	Disc_quote &operator=(const Disc_quote &&) & noexcept ;

	double net_price(std::size_t ) const=0;

	void debug() override { 
		Quote::debug();
		std::cout<<" quantity: "<<quantity<<" discount: "<<discount; 
	}
};

Disc_quote::Disc_quote(const Disc_quote &rhs):
	Quote(rhs), quantity(rhs.quantity), discount(rhs.discount) {} 
Disc_quote &Disc_quote::operator=(const Disc_quote &rhs) & {
	if(this==&rhs)
		return *this;
	Quote::operator=(rhs);
	quantity=rhs.quantity;
	discount=rhs.discount;
	return *this;
}

Disc_quote::Disc_quote(Disc_quote &&rhs) noexcept : 
	Quote(std::move(rhs)), quantity(rhs.quantity), discount(rhs.discount) {}

Disc_quote &Disc_quote::operator=(const Disc_quote &&rhs) & noexcept {
	if(this==&rhs)
		return *this;
	Quote::operator=(std::move(rhs));
	quantity=rhs.quantity;
	discount=rhs.discount;
	return *this;
}
