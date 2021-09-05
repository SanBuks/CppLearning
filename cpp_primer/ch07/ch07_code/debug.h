#pragma once
#include <iostream>
class Debug{
public:
    constexpr Debug(bool b = true) : hw(b), io(b), other(b){}
    constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o){}
    constexpr bool any() const { return hw | io | other; }

    void set_hw(bool b) const { hw = b; }
    void set_io(bool b) const { io = b; }
    void set_other(bool b) const { other = b; }

private:
    bool mutable hw;
    bool mutable io;
    bool mutable other;
};

void testDebug(){
	constexpr Debug debug(false, false, true);
	debug.set_other(false);
	std::cout << debug.any();
}