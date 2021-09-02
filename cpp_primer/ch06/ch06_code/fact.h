#ifndef CH06_CH06_CODE_FACT_H_
#define CH06_CH06_CODE_FACT_H_
// 判断补码相乘是否溢出
inline bool tmult_ok(unsigned long x, unsigned long y) {
	long p = x * y;
	return !x || (p / x == y);
}

// 阶乘
unsigned long fact(unsigned long);
#endif