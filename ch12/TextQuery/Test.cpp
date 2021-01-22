#include <fstream>
#include "TextQuery.h"
void runQueries(ifstream &ifs){
	TextQuery tq(ifs);
	ifs.close();
	while(true){
		cout<<"Enter word to look for, or q to quit : \n";
		string s;
		if(!(cin>>s) || s=="q") break;
		print(cout, tq.query(s));
	}
}

ifstream& loadFiles(){
	static ifstream ifs;	
	while(true){
		cout<<"Enter filename to load, or q to quit : \n";
		string s;
		if(cin>>s){
			if(s=="q") exit(1);
			ifs.open(s);	
			if(ifs){
				return ifs;
			}else cout<<"load file failure!\n"; 
		}else cout<<"read filename failure!\n"; 
	}
}

int main(){
	while(true){
		auto &ifs=loadFiles();
		runQueries(ifs);
	}
	return 0;
}
