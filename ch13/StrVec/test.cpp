#include <iostream>
#include "StrVec.h"

int main(){
	StrVec sv;
	sv.push_back("123");
	sv.push_back("456");
	sv.push_back("789");
	for(auto it=sv.begin(); it!=sv.end(); ++it)
		std::cout<<*it<<"\n";

	return 0;
}
