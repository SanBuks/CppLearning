#include "Query.h"

Query::Query(const string &s): q(new WordQuery(s)){}
QueryResult Query::eval(const TextQuery &t) const { return q->eval(t); }
string Query::rep() const { return q->rep(); }

ostream &operator<<(ostream &os, const Query &query){ return os<<query.rep(); }
