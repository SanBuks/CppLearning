#include <iostream>
class B{
public: virtual void test(){};
};

class Dpub : public B{ };
class Dpro : protected B{ };
class Dpri : private B{ };

class Ddpub : public Dpub{
public: void test() override { 
			Dpub dpub; B &bd=dpub; 
			Ddpub ddpub; B &bdd=ddpub;
		} 
};
class Ddpro : public Dpro{
public: void test() override { 
			Dpub dpub; B &bd=dpub; 
			Ddpub ddpub; B &bdd=ddpub;
		} 
};
class Ddpri : public Dpri{
public: void test() override { 
			Dpub dpub; B &bd=dpub; 
			Ddpub ddpub; B &bdd=ddpub;
		} 
};

int main(){
	Ddpub ddpub; Ddpro ddpro; Ddpri ddpri;
	// 派生类的访问控制对间接派生类的可见性有影响
	// 间接派生类如何继承不影响可见性
	ddpub.test(); // public -> public -> public 可见 
	ddpro.test(); // public -> protected -> protected 可见 
	ddpri.test(); // public -> private -> private 直接派生类和本身都不可见 
	return 0;
}
