#pragma once
#include "../Query_base/Query_base.h"

class Query{
	friend Query operator~(const Query &);
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);
	friend Query get_between(size_t , size_t , const Query &);
public: 
	Query(const std::string &);
	QueryResult eval(const TextQuery &t) const; 
	string rep() const;
private:
	Query(std::shared_ptr<Query_base> query):q(query){}
	std::shared_ptr<Query_base> q;  // 指向继承体系中Query
};

