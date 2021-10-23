# 12.01
> 在此代码的结尾，b1 和 b2 各包含多少个元素？
```c++
StrBlob b1;
{
	StrBlob b2 = {"a", "an", "the"};
	b1 = b2;
	b2.push_back("about");  // 各4个
}
```

# 12.02
> 编写你自己的StrBlob 类，包含const 版本的 front 和 back

参考[]()

# 12.03*
> StrBlob 需要const 版本的push_back 和 pop_back吗？如需要，添加进去。否则，解释为什么不需要。

不需要, `push_back` 与 `pop_back` 改变类的数据, 不该设置constness语义, 其次const成员函数不能在编译上限制改变data所指元素

# 12.04
> 在我们的 check 函数中，没有检查 i 是否大于0。为什么可以忽略这个检查？

i是无符号数, 模运算规定了边界

# 12.05*
> 我们未编写接受一个 initializer_list explicit 参数的构造函数。讨论这个设计策略的优点和缺点。

优点 : 不会发生隐式类型转换, 所写即所得, 清晰明白
缺点 : 需要临时变量时需要显示定义一个StrBlob, 其次不会发生隐式转换导致`StrBlob str2={"123", "234", "345"};`形式出错无法调用拷贝构造函数


# 12.06
> 编写函数，返回一个动态分配的 int 的vector。将此vector 传递给另一个函数，这个函数读取标准输入，将读入的值保存在 vector 元素中。再将vector传递给另一个函数，打印读入的值。记得在恰当的时刻delete vector。
```c++
#include <iostream>
#include <new>
#include <vector>
std::vector<int> *createVector(){
	return new(std::nothrow)std::vector<int>;
}
void print(std::vector<int> *p){
	for(auto it=p->cbegin(); it!=p->cend(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"\n";
}
void process(std::vector<int> *p){
	if(!p){ std::cout<<"new error!\n"; return;}	
	int curr;
	while(std::cin>>curr)
		p->push_back(curr);
	print(p);
	delete p;
	p=nullptr;
}
int main(){
	auto it=createVector();
	process(it);
	return 0;
}
```

# 12.07
> 重做上一题，这次使用 shared_ptr 而不是内置指针。
```c++
#include <iostream>
#include <memory>
#include <vector>
std::shared_ptr<std::vector<int>> createVector(){
	return std::make_shared<std::vector<int>>();
}
void print(std::shared_ptr<std::vector<int>> p){
	for(auto it=p->cbegin(); it!=p->cend(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"\n";
}

void process(std::shared_ptr<std::vector<int>> p){
	int curr;
	while(std::cin>>curr)
		p->push_back(curr);
	print(p);
}
int main(){
	auto it=createVector();
	process(it);
	return 0;
}
```

# 12.08*
> 下面的函数是否有错误？如果有，解释错误原因。
```c++
bool b() {
	int* p = new int;
	// ...
	return p;
}
```

出错, 指针p被强制类型转化成bool型后不能被正确释放, 产生内存泄漏 

# 12.09
> 解释下面代码执行的结果。
```c++
int *q = new int(42), *r = new int(100);
r = q;  // r被赋值前没有释放内存导致内存泄漏
auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
r2 = q2; // r2被赋值前计数器减1为零, 自动释放内存, 安全
```

# 12.10
> 下面的代码调用了第413页中定义的process 函数，解释此调用是否正确。如果不正确，应如何修改？
```c++
shared_ptr<int> p(new int(42)); // p 引用计数: 1
process(shared_ptr<int>(p));	// p 引用计数: 2
								// p 引用计数: 1 正确
```

# 12.11
> 如果我们像下面这样调用 process，会发生什么？
```c++
process(shared_ptr<int>(p.get()));  
// 发生野指针错误, 智能指针p所分配的内存被临时对象给释放了, 
```

# 12.12
> p 和 sp 的定义如下，对于接下来的对 process 的每个调用，如果合法，解释它做了什么，如果不合法，解释错误原因：
```c++
auto p = new int();
auto sp = make_shared<int>();
process(sp);  // 合法
process(new int());  // 不合法, 智能指针以手动分配内存为单一参数的构造函数是explicit
process(p);  // 不合法, 理由同上, 且p会成野指针
process(shared_ptr<int>(p));  // 不合法, p会成野指针
```

# 12.13
> 如果执行下面的代码，会发生什么？
```c++
auto sp = make_shared<int>();
auto p = sp.get();
delete p;  // sp 成了野指针
```

# 12.14
> 编写你自己版本的用 shared_ptr 管理 connection 的函数。

# 12.15*
> 重写上一题的程序，用 lambda 代替end_connection 函数。
```c++
#include <iostream>
#include <memory>
#include <exception>
struct destination{};
struct connection{};

connection connect(destination *p){
	std::cout<<"connect ! \n";
	return  connection();  // 值返回一个默认构造的connection
} 

void disconnect(connection conn){
	std::cout<<"disconnect ! \n";	
}

void end_connection(connection *conn){ // 注意 删除器参数必须是 T* 类型
	disconnect(*conn);
}

void f(destination &d){
	connection conn=connect(&d);
	//std::shared_ptr<connection> p(&conn, end_connection);
	std::shared_ptr<connection> p(&conn, [](connection *p){ disconnect(*p); } );

	// throw std::exception();
}

int main(){
	destination dd;
	f(dd);
	return 0;
}
```

# 12.16
> 如果你试图拷贝或赋值 unique_ptr，编译器并不总是能给出易于理解的错误信息。编写包含这种错误的程序，观察编译器如何诊断这种错误。
```bash
# 拷贝初始化
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
  std::unique_ptr<int> p=q;
                         ^
In file included from /usr/include/c++/8/memory:80,
                 from test.cpp:2:
/usr/include/c++/8/bits/unique_ptr.h:394:7: note: declared here
       unique_ptr(const unique_ptr&) = delete;
       ^~~~~~~~~~

# 赋值
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
  p=q;
    ^
In file included from /usr/include/c++/8/memory:80,
                 from test.cpp:2:
/usr/include/c++/8/bits/unique_ptr.h:395:19: note: declared here
       unique_ptr& operator=(const unique_ptr&) = delete;
                   ^~~~~~~~
```

# 12.17
> 下面的 unique_ptr 声明中，哪些是合法的，哪些可能导致后续的程序错误？解释每个错误的问题在哪里。
```c++
int ix = 1024, *pi = &ix, *pi2 = new int(2048);
typedef unique_ptr<int> IntP;
IntP p0(ix); // 错误, int不是内置指针
IntP p1(pi);  // 错误, pi不是手动分配的内存
IntP p2(pi2);  // 正确, 但是pi2有可能变成野指针
IntP p3(&ix);  // 错误, 同p1
IntP p4(new int(2048));  // 正确
IntP p5(p2.get());  // 错误, p2可能会变成野指针
```

# 12.18
> shared_ptr 为什么没有 release 成员？

- release函数返回所管理的指针, 并将本身设置为空, shared_ptr存在引用计数, 不会直接置空
- 存在类似的reset函数, 但是会先检查引用计数再做释放操作

# 12.19*
> 定义你自己版本的 `StrBlobPtr`，更新 `StrBlob` 类，加入恰当的 `friend` 声明以及 `begin` 和 `end` 成员。
```c
// StrBlob.h
#pragma once
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include "StrBlobPtr.h"
class StrBlob{
	friend class StrBlobPtr;
public:
	typedef std::vector<std::string>::size_type size_type;
private:
	std::shared_ptr<std::vector<std::string>>data;	
	void check(size_type i, const std::string &msg) const;
public:
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	bool empty() const { return data->empty(); }
	size_type size() const { return data->size(); }

	void push_back(const std::string &t){ data->push_back(t); }
	void pop_back();
	std::string &front();
	std::string &back();
	const std::string &front() const;
	const std::string &back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
};

// StrBlon.cpp
#include "StrBlob.h"
StrBlob::StrBlob()
	:data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il)
	:data(std::make_shared<std::vector<std::string>>(il)){}

void StrBlob::check(size_type i, const std::string &msg) const {
	if(i>=data->size())
		throw std::out_of_range(msg);
}
void StrBlob::pop_back(){
	check(0, "pop back on empty StrBlob");
	data->pop_back();
}
std::string & StrBlob::front(){
	check(0, "front on empty StrBlob");
	return data->front();
}
std::string & StrBlob::back(){
	check(0, "back on empty StrBlob");
	return data->back();
}
const std::string & StrBlob::front() const {
	check(0, "const front on empty StrBlob");
	return data->front();
}
const std::string & StrBlob::back() const {
	check(0, "const back on empty StrBlob");
	return data->back();
}
StrBlobPtr StrBlob::begin(){ return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end(){ return StrBlobPtr(*this, data->size()); }

// StrBlobPtr.h
#pragma once
#include "StrBlob.h"
class StrBlob;
class StrBlobPtr{
private:
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
public:
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a, size_t sz=0);
	std::string & deref() const;
	StrBlobPtr& incr();
	bool operator!=(const StrBlobPtr &rhs);
};

// StrBlobPtr.cpp
#include "StrBlob.h"
#include "StrBlobPtr.h"
StrBlobPtr::StrBlobPtr(StrBlob &a, size_t sz):wptr(a.data), curr(sz){}
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const{
	auto ret=wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if(i>=ret->size())
		throw std::out_of_range(msg);
	return ret;
}
std::string & StrBlobPtr::deref() const{
	auto def=check(curr, "deref past end");
	return (*def)[curr];
}
StrBlobPtr & StrBlobPtr::incr(){
	curr++;
	return *this;
}
bool StrBlobPtr::operator!=(const StrBlobPtr &rhs){
	auto lsp=wptr.lock();
	auto rsp=rhs.wptr.lock();
	if(!lsp || !rsp) throw std::runtime_error("StrBlobPtr nullptr!");
	return (lsp==rsp)&&(curr!=rhs.curr);
}
```

# 12.20
> 编写程序，逐行读入一个输入文件，将内容存入一个 StrBlob 中，用一个 StrBlobPtr 打印出 StrBlob 中的每个元素。
```c++
void readFile_test(){
	std::ifstream ifs("data");
	StrBlob strb;
	if(!ifs){ std::cout<<"open file error!\n"; return ; }
	std::string str;
	while(ifs>>str)
		strb.push_back(str);
	ifs.close();
	for(auto it=strb.begin(); it!=strb.end(); it.incr())
		std::cout<<it.deref()<<" ";
}
```

# 12.21
> 也可以这样编写 StrBlobPtr 的 deref 成员，你认为哪个版本更好？为什么？
```c++
std::string& deref() const {
	return (*check(curr, "dereference past end"))[curr];
}
```

前者, 简洁明了, debug好追踪

# 12.22
> 为了能让 StrBlobPtr 使用 const StrBlob，你觉得应该如何修改？定义一个名为ConstStrBlobPtr 的类，使其能够指向 const StrBlob。
```c++
// ConstStrBlobPtr.cpp
ConstStrBlobPtr::ConstStrBlobPtr(const StrBlob &a, size_t sz):wptr(a.data), curr(sz){}
const std::string & ConstStrBlobPtr::deref() const{
	auto def=check(curr, "deref past end");
	return (*def)[curr];
}
// StrBlob.cpp
ConstStrBlobPtr StrBlob::cbegin(){ return ConstStrBlobPtr(*this); }
ConstStrBlobPtr StrBlob::cend(){ return ConstStrBlobPtr(*this, data->size()); }
// 其余与StrBlobPtr类似
```

# 12.23*
> 编写一个程序，连接两个字符串字面常量，将结果保存在一个动态分配的char数组中。重写这个程序，连接两个标准库string对象。
```c++
#include <iostream>
#include <cstring>
#include <string>
int main(){
	const char *p1="123456";
	const char *p2="78910";
	char *p=new char[std::strlen(p1)+std::strlen(p2)+1];
	auto pp=p;
	for(auto qq=p1; (*qq)!='\0'; ++qq) *pp++=*qq; // strcat(p, p1);
	for(auto qq=p2; (*qq)!='\0'; ++qq) *pp++=*qq; // strcat(p, p2);
	*pp++='\0';
	std::cout<<p1<<'\n';
	std::cout<<p2<<'\n';
	std::cout<<p<<'\n';
	
	std::string s1("abcdefg");
	std::string s2("hijklmn");
	strcpy(p, (s1+s2).c_str());
	std::cout<<s1<<'\n';
	std::cout<<s2<<'\n';
	std::cout<<p<<'\n';
	
	delete [] p;
	return 0;
}
```

# 12.24*
> 编写一个程序，从标准输入读取一个字符串，存入一个动态分配的字符数组中。描述你的程序如何处理变长输入。测试你的程序，输入一个超出你分配的数组长度的字符串。
```c++
#include <iostream>
#include <cstring>
#include <string>
const size_t DEFAULT_SIZE=10;
int main(){
	std::string str; size_t size=DEFAULT_SIZE;
	char *p=new char[DEFAULT_SIZE];
	while(std::cin>>str){
		if(str.size()>=size){
			char *newp=new char[size*=2];
			delete p;
			p=newp;
		}
		std::strcpy(p, str.c_str());
		std::cout<<p<<'\n';
	}
	delete [] p;
	return 0;
}
```

# 12.25
> 给定下面的new表达式，你应该如何释放pa？
```c++
int *pa = new int[10];
```

`delete [] pa;`

# 12.26
> 用 allocator 重写第427页中的程序。
```c++
#include <iostream>
#include <string>
#include <memory>
const int n=5;
int main(){
	std::string s, *q;
	std::allocator<std::string> alloc;
	auto const p=alloc.allocate(n);
	q=p;
	while(std::cin>>s && q!=p+n)
		alloc.construct(q++, s);
	while(q!=p){
		std::cout<<*(--q)<<" ";
		alloc.destroy(q);
	}
	alloc.deallocate(p, n);	
	return 0;
}
```

# 12.27*
> TextQuery 和 QueryResult 类只使用了我们已经介绍过的语言和标准库特性。不要提前看后续章节内容，只用已经学到的知识对这两个类编写你自己的版本。
```c++
// TextQuery.h
#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "QueryResult.h"
class TextQuery{
private:
	shared_ptr<vector<string>> files;
	map<string, shared_ptr< set<size_t>>> mp;
public:
	TextQuery(ifstream &);
	QueryResult query(const string &str) const;
};
TextQuery::TextQuery(ifstream &ifs):files(new vector<string>){
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

// QueryResult.h
#pragma once
#include <iostream>
#include "UsingTools.h"
class QueryResult{
	friend ostream& print(ostream&, const QueryResult &);
private:
	string wordSearch;
	shared_ptr<set<size_t>> lines;
	shared_ptr<vector<string>> files; 
public:
	QueryResult(string s, shared_ptr<set<size_t>> p, 
			shared_ptr<vector<string>> f)
				:wordSearch(s),  lines(p), files(f){}
};
ostream& print(ostream &os, const QueryResult &qr){
	os<<qr.wordSearch<<" occurring times : "<<qr.lines->size()<<"\n";
	for(auto it : *qr.lines)
		os<<"\t (line "<<it+1<<")" <<(*qr.files)[it]<<"\n";
	return os;
}
```

# 12.28*
> 编写程序实现文本查询，不要定义类来管理数据。你的程序应该接受一个文件，并与用户交互来查询单词。使用vector、map 和 set 容器来保存来自文件的数据并生成查询结果。
```c++
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
```

# 12.29
> 我们曾经用do while 循环来编写管理用户交互的循环。用do while 重写本节程序，解释你倾向于哪个版本，为什么？

个人认为 while-do 思考方式可以减少死循环发生可能性

# 12.30
> 定义你自己版本的 TextQuery 和 QueryResult 类，并执行12.3.1节中的runQueries 函数。

参考 12.27

# 12.31
> 如果用vector 代替 set 保存行号，会有什么差别？哪个方法更好？为什么？

vector需要自己解决重复问题, 浪费效率

# 12.32
> 重写 TextQuery 和 QueryResult类，用StrBlob 代替 `vector<string>` 保存输入文件。
```c++
// StrBlob.h 增加函数	
std::string &operator[](size_type t){ return (*data)[t]; };
// 其余参照12.27 更改相应vector<string>
```

# 12.33
> 在第15章中我们将扩展查询系统，在 QueryResult 类中将会需要一些额外的成员。添加名为 begin 和 end 的成员，返回一个迭代器，指向一个给定查询返回的行号的 set 中的位置。再添加一个名为 get_file 的成员，返回一个 shared_ptr，指向 QueryResult 对象中的文件。
```c++
set<size_t>::iterator begin(){ return lines->begin(); }
set<size_t>::iterator end(){ return lines->end(); }
shared_ptr<StrBlob> get_file(){ return files; }
```
