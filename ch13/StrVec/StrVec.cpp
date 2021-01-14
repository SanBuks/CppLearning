#include <utility>
#include <iterator>
#include "StrVec.h"
std::allocator<std::string> StrVec:: alloc;

StrVec::StrVec(StrVec &&s) noexcept:
	elements(s.elements), first_free(s.first_free), cap(s.cap){
	s.elements=s.first_free=s.cap=nullptr;	
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept{
	if(this!=&rhs){
		free();
		elements=rhs.elements;
		first_free=rhs.first_free;
		cap=rhs.cap;
		rhs.elements=rhs.first_free=rhs.cap=nullptr;	
	}
	return *this;
}

void StrVec::push_back(const std::string &s){
	chk_n_alloc();  // 首先检查是否满了
	alloc.construct(first_free++, s);
}

void push_back(std::string &&){
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}

std::pair<std::string *, std::string *> StrVec::
  alloc_n_copy(const std::string *b, const std::string *e){
	auto data=alloc.allocate(e-b);  // 根据迭代器范围分配内存
	return { data, std::uninitialized_copy(b, e, data) };  
	// 返回pair 第一个指向内存的第一个位置  第二个指向内存最后位置 同时完成拷贝初始化
}

void StrVec::free(){
	if(elements){
		for(auto p=first_free; p!=elements; )
			alloc.destroy(--p);
		alloc.deallocate(elements, cap-elements);
	}
}

StrVec & StrVec::operator=(const StrVec &rhs){
	auto data=alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements=data.first;
	first_free=data.second;
	cap=data.second;
	return *this;
}

void StrVec::reallocate(){
	auto newcapacity=size()?2*size():1;  // 新的容量 翻倍
	auto newdata=alloc.allocate(newcapacity); // 分配内存指向第一个位置
	auto dest=newdata;  // 指向第一个未分配的位置
	auto elem=elements; // 指向原来的位置用于分配内存
	
	auto last=uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), newdata);
	// for(size_t i=0; i!=size(); ++i)
	// 	alloc.construct(dest++, std::move(*elem++));  // 调用移动拷贝构造函数
	free(); // 最后销毁原来的内存
	
	// 复制新的内存
	elements=newdata;
	first_free=last;
	cap=elements+newcapacity;
	
}
