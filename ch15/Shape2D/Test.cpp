#include "Rectangular.h"

int main(){
	Rectangular r1;
	Rectangular r2("00001", "brect", 10.0, 20.0, -20.0, 20.0, 90.0);
	r1.printInfo();
	std::cout<<std::endl;
	r2.printInfo();
	return 0;
}
