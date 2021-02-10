#pragma once
#include "../UsingTools.h"

class QueryResult{
	friend ostream& print(ostream&, const QueryResult &);
private:
	string wordSearch;  // 查询的单词
	shared_ptr<set<size_t>> lines;
	shared_ptr<vector<string>> files; 
public:
	QueryResult(string s, shared_ptr<set<size_t>> p, 
			shared_ptr<vector<string>> f)  // vector<string>
				:wordSearch(s),  lines(p), files(f){}
	set<size_t>::iterator begin(){ return lines->begin(); }
	set<size_t>::iterator end(){ return lines->end(); }
	shared_ptr<vector<string>> get_file(){ return files; }
};


