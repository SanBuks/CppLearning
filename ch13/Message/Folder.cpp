#include <iostream>
#include "Folder.h"
void Folder::addMsg(Message *mp){
	messages.insert(mp);
}

void Folder::remMsg(Message *mp){
	messages.erase(mp);
}

void Folder::print(){
	std::cout<<"Has "<<messages.size()<<" messages : \n";
	for(auto m:messages){
		m->print();
		std::cout<<"\n";
	}
}
