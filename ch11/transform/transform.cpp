#include <map>
#include <set>

#include <string>

#include <memory>

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

shared_ptr<map<string, string>> buildMap(ifstream &map_file){
	auto trans_map=make_shared< map<string, string> >();
	string key, value;
	while( map_file>>key && getline(map_file, value)){
		if(value.size()>1)
			(*trans_map)[key]=value.substr(1);
		else throw runtime_error("no rules for "+key);
	}

	cout<<"Transform rules are : "<<endl;
	for(const auto &e : *trans_map)
		cout<<e.first<<" -> "<<e.second<<endl;
	cout<<"---------------------------\n";
	return trans_map;
}

const string &transform(const string &s, shared_ptr<map<string, string>> ptr){
	auto it=ptr->find(s);
	if(it!=ptr->end()) return it->second;
	else return s;
}

void word_transform(ifstream &map_file, ifstream &input){
	auto trans_map=buildMap(map_file);
	string text;
	while(getline(input, text)){
		istringstream line(text);
		string word;
		bool firstWord=true;
		while(line>>word){
			if(firstWord) firstWord=false;
			else cout<<" ";
			cout<<transform(word, trans_map);
		}
		cout<<endl;
	}
}

int main(){
	ifstream map("rules");
	ifstream txt("text");
	if(map&&txt) word_transform(map, txt);
	else cout<<"open file failure\n";
	return 0;
}
