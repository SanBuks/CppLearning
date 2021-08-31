#include "fact.h"
#include <iostream>

unsigned long fact(unsigned long n){
	unsigned long fact = 1;
	while(n > 0){
		if(tmult_ok(fact, n)){
			fact *= n;
			--n;
		}else
			throw std::runtime_error("fact over flow!");
	}
	return fact;
}

void test(int a) {
  std::cout << a;
}

int main() {
  test(3.2);
  return 0;
}