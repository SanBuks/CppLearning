#pragma once
#include <string>
#include <memory>
class StrVec{
private :
	std::string *elements;
	std::string *first_free;
	std::string *cap;
	static std::allocator<std::string> alloc;

	void chk_n_alloc(){
		if(size()==capacity()) 
			reallocate();
	}

	std::pair<std::string *, std::string *> alloc_n_copy
		(const std::string *, const std::string *);
	void free();  // 释放内存
	void reallocate();

public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr){}
	~StrVec(){ free(); };
	StrVec(const StrVec &);
	StrVec(const Strvec &&) noexcept;
	StrVec &operator=(const StrVec &);
	StrVec &operator=(const StrVec &&) noexcept;

	void push_back(const std::string &);  // 末尾增加元素
	size_t size() const { return first_free-elements; }
	size_t capacity() const { return cap-elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }

};
