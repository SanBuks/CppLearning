#include "BinaryQuery.h"
#include "../Query/Query.h"

string BinaryQuery::rep() const { return "("+lhs->rep()+" "+opSym+" "+rhs->rep()+")"; }

QueryResult OrQuery::eval(const TextQuery &text) const {
	auto left=lhs->eval(text);
	auto right=rhs->eval(text);

	auto ret_lines=make_shared<set<size_t>>(left.begin(), left.end()); 
	ret_lines->insert(right.begin(), right.end());
	return QueryResult(rep(), ret_lines, left.get_file());
}

Query operator|(const Query &lhs, const Query &rhs){
	return std::shared_ptr<Query_base>(new OrQuery(lhs.q, rhs.q));
}

QueryResult AndQuery::eval(const TextQuery &text) const {
	auto left=lhs->eval(text);
	auto right=rhs->eval(text);

	auto ret_lines=make_shared<set<size_t>>(left.begin(), left.end()); 

	set_intersection(left.begin(), left.end(), right.begin(), right.end(), 
			inserter(*ret_lines, ret_lines->begin()));

	return QueryResult(rep(), ret_lines, left.get_file());
}

Query operator&(const Query &lhs, const Query &rhs){
	return std::shared_ptr<Query_base>(new AndQuery(lhs.q, rhs.q));
}
