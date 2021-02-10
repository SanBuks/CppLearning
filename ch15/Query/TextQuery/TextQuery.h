#pragma once
#include "QueryResult.h"

class TextQuery{
private:
	shared_ptr<vector<string>> files;   // 按行存储全部文本
	map<string, shared_ptr< set<size_t>>> mp;   // word -> ptr to set of line_no
public:
	TextQuery(ifstream &);  // 从输入流获取文本
	QueryResult query(const string &str) const ;  // 查询单词
};

