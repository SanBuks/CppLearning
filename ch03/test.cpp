#include <iostream>
#include <vector>

int main(){
	int a;
	std::vector<int> v;
	while(std::cin>>a)
		v.push_back(a);

	for(const auto &it : v)
		std::cout<<it<<" ";

	std::cout<<std::endl;
	if(!v.empty()){
		if(v.size()>1) // 注意 只有一个元素用<= 会发生错误
			for(decltype(v.size()) b=0, e=v.size()-1; b<=e; ++b, --e) 
				std::cout<<v[b]+v[e]<<" ";
		else std::cout<<2*v[0];
	}
	return 0;
}
