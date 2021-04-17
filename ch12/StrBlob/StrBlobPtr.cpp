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

StrBlobPtr & StrBlobPtr::operator++(){
	curr++; // 存在尾后迭代器, 特殊处理
	auto ret=wptr.lock();
	if(!ret) throw std::runtime_error("unbound StrBlobPtr");
	if(curr>ret->size()) throw std::out_of_range("increment pase end of StrBlobPtr");
	return *this;
}
StrBlobPtr StrBlobPtr::operator++(int){
	auto ret=*this;
	++*this;
	return ret;
}

StrBlobPtr& StrBlobPtr::operator--(){
	curr--;
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}
StrBlobPtr StrBlobPtr::operator--(int){
	auto ret=*this;
	--*this;
	return ret;
}

StrBlobPtr StrBlobPtr::operator+(const int &n){
	check(curr+n, n+" increment past end of StrBlobPtr");
	auto ret=*this;
	ret.curr+=n;
	return ret;
}
StrBlobPtr StrBlobPtr::operator-(const int &n){
	check(curr+n, n+" decrement past end of StrBlobPtr");
	auto ret=*this;
	ret.curr-=n;
	return ret;
}

bool StrBlobPtr::operator!=(const StrBlobPtr &rhs){
	auto lsp=wptr.lock();
	auto rsp=rhs.wptr.lock();
	if(!lsp || !rsp) throw std::runtime_error("StrBlobPtr nullptr!");
	return (lsp==rsp)&&(curr!=rhs.curr); // 前提指向同一个sp, 然后判断位置
}
