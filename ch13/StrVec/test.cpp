#include <iostream>
#include "StrVec.h"

int main(){
	StrVec sv;
	sv.push_back("123");
	sv.push_back("456");
	sv.push_back("789");
	StrVec svv(sv);
	svv={"123","654","789"};
	for(auto it=svv.begin(); it!=svv.end(); ++it)
		std::cout<<*it<<"\n";
	return 0;
}
