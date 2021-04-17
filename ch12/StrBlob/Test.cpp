#include <fstream>
#include "StrBlob.h"
#include "SBPP.h"
void StrBlob_test(){
	StrBlob str1;
	StrBlob str2={"123", "234", "345"};
	str1=str2;
	for(auto it=str1.begin(); it!=str1.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"\n";

	str2.pop_back();
	str2.push_back("1111");
	for(auto it=str1.begin(); it!=str1.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"\n";

	std::cout<<str1.front()<<" ";
	std::cout<<str2.back()<<" ";
	std::cout<<"\n";
}

void readFile_test(){
	std::ifstream ifs("data");
	StrBlob strb;
	if(!ifs){ std::cout<<"open file error!\n"; return ; }
	std::string str;
	while(ifs>>str)
		strb.push_back(str);
	ifs.close();
	for(auto it=strb.begin(); it!=strb.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"\n"<<strb[1];
}

void StrBlobPtr_test(){
	StrBlob str={"123", "234", "345"};
	auto it=str.begin();
	std::cout<<*(it+(str.size()-1));
}

void SBPP_test(){
	StrBlob str={"123", "234", "345"};
	auto it=str.begin();
	SBPP sbpp(it+1);
	std::cout<<**sbpp<<std::endl;
	std::cout<<sbpp->getcurr()<<std::endl;
}

int main(){
	StrBlob str1;
	StrBlob str2={"123", "234", "345"};
	str1=str2;
	for(auto it=str1.begin(); it!=str1.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"\n";

	//StrBlob_test();
	//readFile_test();
	//StrBlobPtr_test();
	//SBPP_test();
	return 0;
}
