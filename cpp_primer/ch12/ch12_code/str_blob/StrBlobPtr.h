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

	StrBlobPtr& operator++();
	StrBlobPtr operator++(int);
	StrBlobPtr& operator--();
	StrBlobPtr operator--(int);

	bool operator!=(const StrBlobPtr &rhs);
	StrBlobPtr operator+(const int &);
	StrBlobPtr operator-(const int &);

	std::string & operator*() const {
		auto def=check(curr, "deref past end");
		return (*def)[curr];
	}

	std::string * operator->() const {
		return & this->operator*();
	}
	
	size_t getcurr() const { return curr; }

};
