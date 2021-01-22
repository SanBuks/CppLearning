#pragma once
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
