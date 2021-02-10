#pragma once
#include "Query_base.h"

class BinaryQuery: public Query_base{
protected:
	BinaryQuery(shared_ptr<Query_base> l, shared_ptr<Query_base> r, string s):
		lhs(l), rhs(r), opSym(s){ }

	std::string rep() const override; 

	shared_ptr<Query_base>lhs; 
	shared_ptr<Query_base>rhs;
	string opSym;
};

class OrQuery: public BinaryQuery{
	friend Query operator|(const Query &, const Query &);
	OrQuery(shared_ptr<Query_base> l, shared_ptr<Query_base> r): BinaryQuery(l, r, "|"){ }
	QueryResult eval(const TextQuery &) const; 
};

class AndQuery: public BinaryQuery{
	friend Query operator&(const Query &, const Query &);
	AndQuery(shared_ptr<Query_base> l, shared_ptr<Query_base> r): BinaryQuery(l, r, "&"){ }
	QueryResult eval(const TextQuery &) const; 
};
