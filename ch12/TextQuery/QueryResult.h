#pragma once
#include <iostream>
#include "UsingTools.h"
#include "../StrBlob/StrBlob.h"
class QueryResult{
	friend ostream& print(ostream&, const QueryResult &);
private:
	string wordSearch;
	shared_ptr<set<size_t>> lines;
	shared_ptr<StrBlob> files; //shared_ptr<vector<string>> files; 
public:
	QueryResult(string s, shared_ptr<set<size_t>> p, 
			shared_ptr<StrBlob> f)  // vector<string>
				:wordSearch(s),  lines(p), files(f){}
	set<size_t>::iterator begin(){ return lines->begin(); }
	set<size_t>::iterator end(){ return lines->end(); }
	shared_ptr<StrBlob> get_file(){ return files; }
};

ostream& print(ostream &os, const QueryResult &qr){
	os<<qr.wordSearch<<" occurring times : "<<qr.lines->size()<<"\n";
	for(auto it : *qr.lines)
		os<<"\t (line "<<it+1<<")" <<(*qr.files)[it]<<"\n";
	return os;
}
