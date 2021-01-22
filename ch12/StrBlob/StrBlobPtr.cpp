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
