#include <iostream>
#include <string>
#include "Folder.h"
#include "Message.h"

int main(){
	Folder f1;
	Message m1(std::string("123456"));
	Message m2(std::string("654321"));

	m1.save(f1);
	m2.save(f1);
	f1.print();

	Message m3(m1);
	f1.print();
	
	m3.remove(f1);
	f1.print();

	m3=std::move(m2);
	f1.print();

	return 0;
}
