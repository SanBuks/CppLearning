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

	StrBlob(const StrBlob &);

	bool empty() const { return data->empty(); }
	size_type size() const { return data->size(); }
	std::string &operator[](size_type t){ return (*data)[t]; };

	void push_back(const std::string &t){ data->push_back(t); }
	void pop_back();
	std::string &front();
	std::string &back();
	const std::string &front() const;
	const std::string &back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
};
