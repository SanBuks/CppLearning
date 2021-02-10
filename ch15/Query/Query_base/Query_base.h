#pragma once
#include "../TextQuery/TextQuery.h"
#include "../UsingTools.h"

class Query;
class Query_base{
	friend class Query;  // 包装类 统一接口
public:
	// 继承类可以通过shared_ptr调用rep和eval, 必须让rep 和 eval 开放 
	// Query_base 中可以不存放Query实体, 实现impl
	virtual QueryResult eval(const TextQuery&) const =0;
	virtual std::string rep() const =0;
protected:
	virtual ~Query_base()=default;
private:
	//virtual QueryResult eval(const TextQuery&) const =0;
	//virtual std::string rep() const =0;
};

class WordQuery: public Query_base{
	friend class Query;
private:
	WordQuery(const std::string &s):query_word(s){}

	QueryResult eval(const TextQuery &t) const override; 
	string rep() const override; 

	string query_word;  // 查询的词
};


class NotQuery: public Query_base{
	friend Query operator~(const Query &);
private:
	NotQuery(shared_ptr<Query_base> q) : query(q){}

	string rep() const override; 
	QueryResult eval(const TextQuery &) const override;

	shared_ptr<Query_base> query;
};

class BetweenQuery: public Query_base{
	friend Query get_between(size_t , size_t , const Query &);
private:
	BetweenQuery(size_t l, size_t h, shared_ptr<Query_base> q): low(l), high(h), query(q){}

	string rep() const override; 
	QueryResult eval(const TextQuery &) const override;
	size_t low; 
	size_t high;
	shared_ptr<Query_base> query;
};
