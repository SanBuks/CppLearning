#pragma once
#include "Disc_quote.h"

class Bulk_quote : public Disc_quote{
public:
	using Disc_quote::Disc_quote;  // 没有数据成员 直接继承父类构造函数
	Bulk_quote()=default;
	Bulk_quote(const Bulk_quote &);
	Bulk_quote &operator=(const Bulk_quote &)&;

	Bulk_quote(Bulk_quote &&) noexcept ;
	Bulk_quote &operator=(Bulk_quote &) & noexcept ;

	double net_price(std::size_t ) const override;

	virtual Bulk_quote* clone() const & override { return new Bulk_quote(*this); }
	virtual Bulk_quote* clone() && override { return new Bulk_quote(std::move(*this)); }
};

double Bulk_quote::net_price(std::size_t cnt) const {
	if(cnt>=quantity) return cnt*(1-discount)*price;
	else return cnt*price;
}
Bulk_quote::Bulk_quote(const Bulk_quote &rhs):Disc_quote(rhs){}
Bulk_quote &Bulk_quote::operator=(const Bulk_quote &rhs)&{
	if(this==&rhs)
		return *this;
	Disc_quote::operator=(rhs);
	return *this;
}
Bulk_quote::Bulk_quote(Bulk_quote &&rhs) noexcept : Disc_quote(std::move(rhs)) {}
Bulk_quote &Bulk_quote::operator=(Bulk_quote &rhs) & noexcept {
	if(this==&rhs)
		return *this;
	Disc_quote::operator=(std::move(rhs));
	return *this;
}
