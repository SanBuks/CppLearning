#include <iostream>
struct SmallInt{
	friend SmallInt operator+(const SmallInt&, const SmallInt&);
	SmallInt(int i=0):val(i){}
	operator int() const { return val; } 
	size_t getval() const { return val; }
private:
    std::size_t val;
};

SmallInt operator+(const SmallInt& lhs, const SmallInt& rhs){
	int a=lhs.val+static_cast<int>(rhs.getval());
	return SmallInt(a);
}

struct LongDouble {
	LongDouble operator+(const SmallInt &rhs){
		double a=val+static_cast<double>(rhs.getval());
		return LongDouble(a);	
	}
	LongDouble(double d=0.0):val(d){}
	operator double(){ return val; }
	operator float(){ return static_cast<float>(val); }
	double val;
};

LongDouble operator+(LongDouble &lhs, double rhs){
	double a=lhs.val+rhs;
	return LongDouble(a);	
}

int main(){
	SmallInt si; 
	LongDouble ld;
	//ld = si + ld;
	ld = ld + si;
	double d = si+static_cast<SmallInt>(3.14);
	std::cout<<d<<std::endl;
	return 0;
}
