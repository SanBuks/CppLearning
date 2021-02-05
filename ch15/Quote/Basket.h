#pragma once
#include <iostream>
#include <set>
class Basket{
public:
	void add_item(const Quote &sale){
		items.insert( std::shared_ptr<Quote>(sale.clone()) );
	}
	void add_item(Quote &&sale){
		items.insert( std::shared_ptr<Quote>(std::move(sale).clone()) );
	}
	double total_receipt(std::ostream &) const;

private:
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs){
		return lhs->isbn()<rhs->isbn();
	}
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};
double Basket::total_receipt(std::ostream &os) const{
	double sum=0.0;
	for(auto it=items.cbegin(); it!=items.cend(); it=items.upper_bound(*it))
		sum+=print_total(os, **it, items.count(*it));
	os<<"Total sum: "<<sum<<std::endl;
	return sum;
}
