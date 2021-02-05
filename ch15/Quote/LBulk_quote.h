#pragma once
#include "Disc_quote.h"

class LBulk_quote : public Disc_quote{
private:
	std::size_t max_qty=0;
public:
	LBulk_quote()=default;
	LBulk_quote(const std::string &book, const double &p, 
			std::size_t miqty, std::size_t maqty, const double &disc):
			Disc_quote(book, p, miqty, disc), max_qty(maqty){}

	LBulk_quote(const LBulk_quote&);
	LBulk_quote &operator=(const LBulk_quote&)&;

	LBulk_quote(LBulk_quote &&) noexcept ;
	LBulk_quote &operator=(LBulk_quote &&) & noexcept ;

	virtual LBulk_quote* clone() const &  override { return new LBulk_quote(*this); }
	virtual LBulk_quote* clone() && override { return new LBulk_quote(std::move(*this)); }

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

LBulk_quote::LBulk_quote(const LBulk_quote &rhs):Disc_quote(rhs), max_qty(rhs.max_qty){}
LBulk_quote &LBulk_quote::operator=(const LBulk_quote &rhs)&{
	if(this==&rhs)
		return *this;
	Disc_quote::operator=(rhs);
	max_qty=rhs.max_qty;
	return *this;
}

LBulk_quote::LBulk_quote(LBulk_quote &&rhs) noexcept :
	Disc_quote(std::move(rhs)), max_qty(rhs.max_qty){}
LBulk_quote &LBulk_quote::operator=(LBulk_quote &&rhs) & noexcept {
	if(this==&rhs)
		return *this;
	max_qty=rhs.max_qty;
	Disc_quote::operator=(std::move(rhs));
	return *this;
}
