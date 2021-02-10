#include "Query_base.h"
#include "../Query/Query.h"

QueryResult WordQuery::eval(const TextQuery &t) const { return t.query(query_word); }

string WordQuery::rep() const { 
	return query_word; 
}

QueryResult NotQuery::eval(const TextQuery &text) const {
	auto result=query->eval(text);
	auto ret_lines=make_shared<set<size_t>>(); 

	auto beg=result.begin();
	auto end=result.end();

	auto sz=result.get_file()->size();

	for(size_t n=0; n!=sz; ++n){
		if(beg==end || *beg!=n )
			ret_lines->insert(n);
		else if(beg!=end)  // && *beg==n
			++beg;
	}

	return QueryResult(rep(), ret_lines, result.get_file());
}

string NotQuery::rep() const { 
	return "~("+query->rep()+")"; 
}

Query operator~(const Query &operand){
	return shared_ptr<Query_base>(new NotQuery(operand.q));
}

QueryResult BetweenQuery::eval(const TextQuery &text) const {
	auto result=query->eval(text);
	auto ret_lines=make_shared<set<size_t>>(); 
	for(auto beg=result.begin(); beg!=result.end(); ++beg){
		if( (low>high) || (*beg>=low && *beg<=high) )
			ret_lines->insert(*beg);
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

string BetweenQuery::rep() const {
	ostringstream oss;
	oss<<"(Between("<<query->rep()<<")["<<low<<","<<high<<"])";
	return oss.str();
}

Query get_between(size_t low, size_t high, const Query &operand){
	return shared_ptr<Query_base>(new BetweenQuery(low, high, operand.q));
}
