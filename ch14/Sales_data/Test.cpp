#include <iostream>
#include "Sales_data.h"
void plus_test(){
	Sales_data t1, t2;	
	std::cin>>t1>>t2;

	Sales_data result=t1+t2; 
	std::cout<<result<<std::endl;

	result="bigbook";
	std::cout<<result<<std::endl;
}
int main(){
	Sales_data t;
	std::cin>>t;
	std::string str=static_cast<std::string>(t);
	std::cout<<str;
	return 0;
}
