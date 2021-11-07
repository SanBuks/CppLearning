#include "has_ptr_value.h"

#include <string>
#include <iostream>

void swap(HasPtrValue &lhs, HasPtrValue &rhs) {
  using std::swap;
  std::cout << "swap(HasPtrValue &lhs, HasPtrValue &rhs) \n";
  swap(lhs.ps_, rhs.ps_);
  swap(lhs.i_, rhs.i_);
}

HasPtrValue::HasPtrValue(std::string s)
    : ps_(new std::string(std::move(s))), i_(0) {}
HasPtrValue::HasPtrValue(const HasPtrValue &has_ptr)
    : ps_(new std::string(*has_ptr.ps_)), i_(has_ptr.i_) {}
HasPtrValue &HasPtrValue::operator=(const HasPtrValue &rhs) {
  using std::swap;

  if (this == &rhs) {
    return *this;
  }
  HasPtrValue temp(rhs);
  swap(*this, temp);
  return *this;
}
HasPtrValue::~HasPtrValue() {
  delete ps_;
}

bool HasPtrValue::operator<(HasPtrValue &rhs) {
  return *ps_ < *rhs.ps_;
}

void HasPtrValue::Print() const {
  std::cout << *ps_;
}