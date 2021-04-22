#include <iostream>

class A{
public:
	A(){}
	inline void print();
private:
	int a = 3;

};

inline void A::print(){ std::cout<<a; }

int main(){
	A a;
	a.print();
	return 0;
}
