#include "TextQuery.h"

ostream& print(ostream &os, const QueryResult &qr){
	os<<qr.wordSearch<<" occurring times : "<<qr.lines->size()<<"\n";
	for(auto it : *qr.lines)
		os<<"\t (line "<<it+1<<")" <<(*qr.files)[it]<<"\n";
	return os;
}

TextQuery::TextQuery(ifstream &ifs):files(new vector<string>){ 
	string text;
	while(getline(ifs, text)){
		files->push_back(text);
		size_t no=files->size()-1;
		istringstream iss(text);
		string word;
		while(iss>>word){
			auto &line_ptr=mp[word]; // 检查 ptr to set 是否为空指针	
			if(!line_ptr) line_ptr.reset(new set<size_t>);
			line_ptr->insert(no);
		}
	}
}

QueryResult TextQuery::query(const string &str) const{
	static shared_ptr<set<size_t>> nodata(new set<size_t>);
	auto re=mp.find(str); // 一定是find查找不生成额外的指针	
	if(re==mp.end()) return QueryResult(str, nodata, files);  
	else return QueryResult(str, re->second, files);  
}
