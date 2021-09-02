#include "fact.h"
#include <stdexcept>

unsigned long fact(unsigned long n) {
	unsigned long fact = 1;
	while (n > 0) {
		if (tmult_ok(fact, n)) {
			fact *= n;
			--n;
		} else {
            throw std::runtime_error("fact over flow!");
        }
	}
	return fact;
}