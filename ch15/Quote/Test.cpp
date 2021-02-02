#include <iostream>
#include "Bulk_quote.h"
#include "LBulk_quote.h"

int main(){
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
	return 0;
}
