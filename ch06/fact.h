#include <cassert>
#include <stdexcept>
#include <iostream>
#include <climits>
#include <cstdlib>
#include <limits>

// 判断补码相乘是否溢出
inline bool tmult_ok(long x, long y){
	long p = x * y;
	return !x || (p / x == y);
}

// 阶乘
unsigned long fact(unsigned long);
