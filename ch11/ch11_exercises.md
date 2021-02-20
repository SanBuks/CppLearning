# 第十一章
### 11.01
> 描述map和vector的不同。

- map 是关联容器保存 `pair<T1, T2>` vector 是顺序容器保存特定类型对象
- 访问map对象, 如果关键字不存在则会创建关键字的pair和初识值, 而vector则会发生越界 

### 11.02
> 分别给出最适合使用list、vector、deque、map以及set的例子。

list : 线程队列
deque : 车辆排序队列
map : 电话本
vector : 保存一般信息

### 11.03
> 编写你自己的单词计数程序。
```c++
#include <iostream>
#include <string>
#include <map>

int main(){
	std::string word;
	std::map<std::string, int> mp;
	while(std::cin>>word)
		++mp[word];
	for(const auto&it : mp)
		std::cout<<"\""<<it.first<<"\"  occur times : "<<it.second<<std::endl;
	return 0;
}
```

### 11.04
> 扩展你的程序，忽略大小写和标点。例如，"example."、"example,"和"Example"应该递增相同的计数器。
```c++
#include <iostream>
#include <string>
#include <cctype>
#include <map>

int main(){
	std::string word;
	std::map<std::string, int> mp;
	while(std::cin>>word){
		std::string str;	
		for(const auto &letter : word){
			if(ispunct(letter)) continue;
			if(isupper(letter)) str+=tolower(letter);
			else str+=letter;
		}
		++mp[str];
	}
	for(const auto&it : mp)
		std::cout<<"\""<<it.first<<"\"  occur times : "<<it.second<<std::endl;
	return 0;
}
```

### 11.05
> 解释map和set的区别。你如何选择使用哪个？

元素存在键值关系选择map, 元素没有键值关系只关乎唯一且是否存在选择set

### 11.06
> 解释set和list的区别。你如何选择使用哪个？

set 基本实现为红黑树, list实现为列表, 前者兼顾修改和查询的效率, 后者修改效率高应用于数据改动频繁的情景

### 11.07
> 定义一个map，关键字是家庭的姓，值是一个vector，保存家中孩子（们）的名。编写代码，实现添加新的家庭以及向已有家庭中添加新的孩子。
```c++
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

int main(){
	std::string fname, names, strline;
	std::map<std::string, std::vector<std::string>> fms;

	while(getline(std::cin, strline)){
		std::istringstream iss(strline);		
		iss>>fname;
		while(iss>>names) 
			fms[fname].push_back(names);
	}

	for(const auto &it : fms){
		std::cout<<it.first<<" : ";
		for(const auto &name : it.second)
			std::cout<<name<<" ";
		std::cout<<std::endl;
	}

	return 0;
}
```

### 11.08
> 编写一个程序，在一个vector而不是一个set中保存不重复的单词。使用set的优点是什么？
```c++
#include <iostream>
#include <string>
#include <set>
#include <vector>

int main(){
	std::string word;
	std::set<std::string> st;
	std::vector<std::string> v;
	while(std::cin>>word)
		st.insert(word);
// set 比 vector 增加的查询成本低
	for(const auto &it : st)
		v.push_back(it);
	
	for(const auto &it : v)
		std::cout<<it<<" ";

	return 0;
}
```

### 11.09
> 定义一个map，将单词与一个行号的list关联，list中保存的是单词所出现的行号。
```c++
std::map< std::string, std::list<std::size_t> > mp;
```

### 11.10*
> 可以定义一个vector\<int>::iterator 到 int 的map吗？list\<int>::iterator 到 int 的map呢？对于两种情况，如果不能，解释为什么。

- vector 提供随机访问元素的功能, 其迭代器是随机访问迭代器, 提供 < 功能, 可以作为关键字
- list 其迭代器是双向迭代器, 没有提供 < 比较, 不可作为关键字

### 11.11*
> 不使用decltype 重新定义 bookstore。
```c++
using Less=bool (*)(const Sales_data &, const Sales_data &);

std::set<Sales_data, Less> mp( 
    [](const Sales_data &lhs, const Sales_data &rhs){
        return lhs.isbn()<rhs.isbn();
        });
```

### 11.12
> 编写程序，读入string和int的序列，将每个string和int存入一个pair 中，pair保存在一个vector中。
```c++
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int main(){
	string word; int nums;
	vector<pair<string,int>> v;

	while(cin>>word>>nums)
		v.push_back({ word, nums});

	for(const auto &it : v)
		cout<<it.first<<" "<<it.second<<endl;

	return 0;
}
```

### 11.13
> 在上一题的程序中，至少有三种创建pair的方法。编写此程序的三个版本，分别采用不同的方法创建pair。解释你认为哪种形式最易于编写和理解，为什么？
```c++
v.push_back(pair<string,int>(word, nums));
v.push_back(make_pair(word, nums));
```

### 11.14
> 扩展你在11.2.1节练习中编写的孩子姓达到名的map，添加一个pair的vector，保存孩子的名和生日。
```c++
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <utility>

int main(){
	std::string fname, names, birth, strline;
	std::map<std::string, std::vector<std::pair<std::string, std::string>> > fms;

	while(getline(std::cin, strline)){
		std::istringstream iss(strline);		
		iss>>fname;
		while(iss>>names>>birth) 
			fms[fname].push_back( {names, birth} );
	}

	for(const auto &it : fms){
		std::cout<<it.first<<" : ";
		for(const auto &item : it.second)
			std::cout<<item.first<<" "<<item.second<<" ";
		std::cout<<std::endl;
	}

	return 0;
}
```

### 11.15
>对一个int到vector\<int>的map，其mapped_type、key_type和 value_type分别是什么？
```c++
mapped_type : vector<int> 
key_type : int
value_type : pair<int, vector<int> >
```

### 11.16
> 使用一个map迭代器编写一个表达式，将一个值赋予一个元素。
```c++
map<int, int> mp{ {1, 2}, {2, 3}};
map.begin()->second=3;
```

### 11.17*
> 假定c是一个string的multiset，v 是一个string 的vector，解释下面的调用。指出每个调用是否合法：
```c++
copy(v.begin(), v.end(), inserter(c, c.end()));  // 正确, 可以作为目的地址
copy(v.begin(), v.end(), back_inserter(c));   // 错误, multiset没有push_back操作
copy(c.begin(), c.end(), inserter(v, v.end()));  // 正确, multiset可以作为源
copy(c.begin(), c.end(), back_inserter(v));   // 正确, 同上
```

### 11.18
> 写出第382页循环中map_it 的类型，不要使用auto 或 decltype。
```c++
std::map<std::string, std::size_t>::const_iterator map_it=
											word_count.cbegin();
```

### 11.19*
> 定义一个变量，通过对11.2.2节中的名为 bookstore 的multiset 调用begin()来初始化这个变量。写出变量的类型，不要使用auto 或 decltype。
```c++
using Less=bool (*)(const Sales_data &, const Sales_data &);
std::multiset<Sales_data, Less>::iterator val=bookstore.begin();
```

### 11.20
> 重写11.1节练习的单词计数程序，使用insert代替下标操作。你认为哪个程序更容易编写和阅读？解释原因。
```c++
#include <iostream>
#include <string>
#include <cctype>
#include <map>

int main(){
	std::string word;
	std::map<std::string, int> mp;
	while(std::cin>>word){
		std::string str;	
		for(const auto &letter : word){
			if(ispunct(letter)) continue;
			if(isupper(letter)) str+=tolower(letter);
			else str+=letter;
		}
		// 用 insert 方法比较简洁明了
		auto result=mp.insert({str, 1});
		if(!result.second)
			++result.first->second;
	}
	for(const auto&it : mp)
		std::cout<<"\""<<it.first<<"\"  occur times : "<<it.second<<std::endl;
	return 0;
}
```

### 11.21
> 假定word_count是一个string到size_t的map，word是一个string，解释下面循环的作用：
```c++
while (cin >> word)
	++word_count.insert({word, 0}).first->second;
	// 不断递增 word 计数, 是上题方法的简写 
```

### 11.22
> 给定一个map\<string, vector\<int>>，对此容器的插入一个元素的insert版本，写出其参数类型和返回类型。
```c++
std::pair<std::string, std::vector<int>> // 元素类型
std::pair<std::map<std::string, std::vector<int>>::iterator, bool>  // 返回类型
```

### 11.23
> 11.2.1节练习中的map 以孩子的姓为关键字，保存他们的名的vector，用multimap 重写此map。
```c++
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
int main(){
	std::string fname, names, strline;
	std::multimap<std::string, std::vector<std::string>> fms;

	while(getline(std::cin, strline)){
		std::istringstream iss(strline);		
		iss>>fname;

		std::vector<std::string> v;
		while(iss>>names)
			v.push_back(names);
			
		fms.emplace( make_pair(fname, v) );
	}

	for(const auto &it : fms){
		std::cout<<it.first<<" : ";
		for(const auto &name : it.second)
			std::cout<<name<<" ";
		std::cout<<std::endl;
	}
	return 0;
}
```

### 11.24
> 下面的程序完成什么功能？
```c++
map<int, int> m;
m[0] = 1;
// 在map类型对象m中创建 {0,0}元素后 将该元素 mapped\_type值 修改为1
```

### 11.25
> 对比下面的程序与上一题程序
```c++
vector<int> v;
v[0] = 1;
// 产生越界错误
```

### 11.26
> 可以用什么类型来对一个map进行下标操作？下标运算符返回的类型是什么？请给出一个具体例子——即，定义一个map，然后写出一个可以用来对map进行下标操作的类型以及下标运算符将会返会的类型。
```c++
// map, unorder_map 可以进行下标操作
std::map<string, int> mp{ {"123", 1}, {"321", 2}, {"231", 3} };
auto val1=mp["123"]; // string-int 
```

### 11.27
> 对于什么问题你会使用count来解决？什么时候你又会选择find呢？

需要知道某关键字元素的个数用 count, 判断关键字元素是否存在用find

### 11.28
> 对一个string到 int的vector 的map，定义并初始化一个变量来保存在其上调用find所返回的结果。
```c++
std::map<std::string, std::vector<int>>::iterator val=mp.find("123");
```

### 11.29\*
> 如果给定的关键字不在容器中，upper_bound、lower_bound 和 equal_range 分别会返回什么？
```c++
lower_bound : 返回 第一个不小于给定关键字的迭代器 
upper_bound : 返回 第一个大于给定关键字的迭代器 
equal_range : 返回 {lower_bound(k), upper_bound(k)} pair
```

### 11.30
> 对于本节最后一个程序中的输出表达式，解释运算对象pos.first->second的含义。

pos.first-> : 访问迭代器所指对象即 pair 元素
pos.first->second : 访问 pair元素的 second 数据项

### 11.31
> 编写程序，定义一个作者及其作品的multimap。使用find在multimap中查找一个元素并用erase删除它。确保你的程序在元素不在map 中时也能正常运行。

### 11.32
> 使用上一题定义的multimap编写一个程序，按字典序打印作者列表和他们的作品。
```c++
#include <iostream>
#include <string>
#include <map>

int main(){
	std::string name, bookname, line, erasename="Jack";
	std::multimap<std::string, std::string> mp;
	while(std::cin>>name){
		getline(std::cin, bookname);
		bookname=bookname.substr(1);
		mp.emplace(make_pair(name, bookname));
	}

	for(auto it=mp.begin(); it!=mp.end(); ++it)
		std::cout<<it->first<<" : "<<it->second<<std::endl;

	auto it=mp.find(erasename);
	if(it!=mp.end())
		mp.erase(erasename);
	std::cout<<"-------------------"<<std::endl;

	for(auto it=mp.begin(); it!=mp.end(); ++it)
		std::cout<<it->first<<" : "<<it->second<<std::endl;
	return 0;
}
```

### 11.33\*
> 实现你自己版本的单词转换程序。
```c++
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
```

### 11.34
> 如果你将transform 函数中的find替换为下标运算符，会发生什么情况？

会自动创建mapped\_type 为空串的转换规则, 最终产生错误

### 11.35\*
> 在buildMap中，如果进行如下改写，会有什么效果？
```c++
trans_map[key] = value.substr(1);  // 使用最后一次出现的转换规则
//改为
trans_map.insert({key, value.substr(1)});  // 使用第一次出现的转换规则
```

### 11.36
> 我们的程序并没检查输入文件的合法性。特别是，它假定转换规则文件中的规则都是有意义的。如果文件中的某一行包含一个关键字、一个空格，然后就结束了，会发生什么？预测程序的行为并进行验证，再与你的程序进行比较。
```c++
if(value.size()>1)
	(*trans_map)[key]=value.substr(1);
else throw runtime_error("no rules for "+key);
// 对转换规则作出判断 如果 " 转换规则" 字符串大小<=1 则抛出异常
```

### 11.37
> 一个无序容器与其有序版本相比有何优势？有序版本有何优势？

无序元素集合中 无序关联容器查找特定元素性能高于有序版本关联容器
有序关联容器不必维护哈希表, 且元素始终保持有序

### 11.38
> 用 unordered\_map 重写单词计数程序和单词转换程序。

略


