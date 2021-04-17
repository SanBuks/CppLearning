#pragma once
#include <string>
#include <memory>
#include <initializer_list>
class StrVec{
private :
	std::string *elements;  // 指向第一个元素
	std::string *first_free;  // 指向第一个空余空间
	std::string *cap;  // 指向尾后
	static std::allocator<std::string> alloc;  // 动态内存分配器

	void chk_n_alloc(){ if(size()==capacity()) reallocate(); }
	std::pair<std::string *, std::string *> alloc_n_copy
		(const std::string *, const std::string *);  // 分配内存并构造范围内的拷贝
	void free();  // 释放内存
	void reallocate(); // 重新分配内存

public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr){}
	~StrVec(){ free(); };
	StrVec(const StrVec &);
	StrVec(StrVec &&) noexcept;
	StrVec &operator=(const StrVec &);
	StrVec &operator=(StrVec &&) noexcept;
	StrVec &operator=(std::initializer_list<std::string>);

	std::string &operator[](size_t n){ return elements[n]; }
	const std::string &operator[](size_t n){ return elements[n]; }

	void push_back(const std::string &);  // 末尾增加元素
	void push_back(std::string &&); // 末尾增加元素 右值版本

	size_t size() const { return first_free-elements; }
	size_t capacity() const { return cap-elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }

};
