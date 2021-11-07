#include "has_ptr_pointer.h"

#include <string>
#include <iostream>

void swap(HasPtrPointer &lhs, HasPtrPointer &rhs) {
  using std::swap;
  swap(lhs.ps_, rhs.ps_);
  swap(lhs.i_, rhs.i_);
  swap(lhs.use_, rhs.use_);
}

HasPtrPointer::HasPtrPointer(std::string s)
    : ps_(new std::string(std::move(s))), i_(0), use_(new std::size_t(1)) { }

HasPtrPointer::HasPtrPointer(const HasPtrPointer &has_ptr)
    : ps_(has_ptr.ps_), i_(has_ptr.i_), use_(has_ptr.use_) {
  ++*use_;
}

//HasPtrPointer &HasPtrPointer::operator=(HasPtrPointer &&rhs)
//HasPtrPointer &HasPtrPointer::operator=(HasPtrPointer rhs) {
//  using std::swap;
//  HasPtrPointer temp(rhs);
//  swap(*this, temp);
//  return *this;
//}

HasPtrPointer &HasPtrPointer::operator=(const HasPtrPointer &rhs) {
  using std::swap;
  if (this == &rhs) {
    return *this;
  }
  HasPtrPointer temp(rhs);
  swap(*this, temp);
  return *this;
}

HasPtrPointer::HasPtrPointer(HasPtrPointer &&has_ptr) noexcept
    : ps_(has_ptr.ps_), i_(has_ptr.i_), use_(has_ptr.use_) {
  has_ptr.ps_ =  nullptr;
  has_ptr.use_ = nullptr;
}

HasPtrPointer &HasPtrPointer::operator=(HasPtrPointer &&rhs) noexcept {
  if (this == &rhs) {
    return *this;
  }
  auto ps_temp = ps_;
  auto use_temp = use_;
  ps_ = rhs.ps_;
  use_ = rhs.use_;
  i_ = rhs.i_;
  if (--*use_temp == 0) {
    delete ps_temp;
    delete use_temp;
  }
  return *this;
}

HasPtrPointer::~HasPtrPointer() {
  if(--*use_ == 0) {
    std::cout << "~HasPtrPointer\n";
    delete ps_;
    delete use_;
  }
}
