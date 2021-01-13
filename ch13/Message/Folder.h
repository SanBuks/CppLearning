#pragma once
#include "Message.h"
class Folder{
private:
	std::set<Message*> messages;
public:
	void addMsg(Message *);
	void remMsg(Message *);
	void print();
};
