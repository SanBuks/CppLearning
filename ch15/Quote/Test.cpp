#include <iostream>
#include <memory>
#include <vector>
#include "Bulk_quote.h"
#include "LBulk_quote.h"
#include "Basket.h"

void print_total_test(){
	Quote q("quote q", 23.3f);
	q.debug();
	std::cout<<"\n";

	Bulk_quote bq("bulk_quote bq", 23.3f, 25, 0.2f); 
	bq.debug(); 
	std::cout<<"\n";

	LBulk_quote lbq("lbulk_quote lbq", 23.3f, 25, 80, 0.2f); 
	lbq.debug(); 
	std::cout<<"\n";
	
	print_total(std::cout, q, 100);  
	print_total(std::cout, bq, 100);  
	print_total(std::cout, lbq, 100);  
}

void cpcontrol_test(){
	LBulk_quote lbq("lbulk_quote lbq", 23.3f, 25, 80, 0.2f); 
	LBulk_quote lbq1=lbq;
	LBulk_quote lbq2;
	lbq2=lbq1;
	lbq2.debug();
	std::cout<<"\n";
	print_total(std::cout, lbq2, 100);
}  

void vector_test(){
	double sum=0.0;
	std::vector<std::shared_ptr<Quote>> vec;
	vec.push_back(std::make_shared<Quote>("Quote q", 50));
	vec.push_back(std::make_shared<Bulk_quote>("Bulk_quote bq", 23.3, 25, 0.2));
	for(const auto &it : vec)
		sum+=it->net_price(80);
	std::cout<<sum<<std::endl;  // $ = 5491.2
}

void basket_test(){
	Basket basket;	
	Quote m1("Quote m1", 20);

	for(int i=0; i<11; i++)
		basket.add_item(m1);
	for(int i=0; i<11; i++)
		basket.add_item(std::move(Quote("Quote q1", 50)));
	for(int i=0; i<11; i++)
		basket.add_item(std::move(Bulk_quote("Bulk_quote bq1", 23.3, 3, 0.2)));
	for(int i=0; i<11; i++)
		basket.add_item(std::move(LBulk_quote("LBulk_quote lbq1", 23.3, 4, 10, 0.2)));

	basket.total_receipt(std::cout);
}
int main(){
	//cpcontrol_test();
	//print_total_test();
	//vector_test();
	basket_test();
	return 0;
}
