#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "QueryResult.h"
#include "../StrBlob/StrBlob.h"

class TextQuery{
private:
	shared_ptr<StrBlob> files;//shared_ptr<vector<string>> files;
	map<string, shared_ptr< set<size_t>>> mp;
public:
	TextQuery(ifstream &);
	QueryResult query(const string &str) const;
};

TextQuery::TextQuery(ifstream &ifs):files(new StrBlob){ // vector<string>
	string text;
	while(getline(ifs, text)){
		files->push_back(text);
		size_t no=files->size()-1;
		istringstream iss(text);
		string word;
		while(iss>>word){
			auto &line_ptr=mp[word];	
			if(!line_ptr) line_ptr.reset(new set<size_t>);
			line_ptr->insert(no);
		}
	}
}

QueryResult TextQuery::query(const string &str) const{
	static shared_ptr<set<size_t>> nodata(new set<size_t>);
	auto re=mp.find(str);	
	if(re==mp.end()) return QueryResult(str, nodata, files);  
	else return QueryResult(str, re->second, files);  
}
