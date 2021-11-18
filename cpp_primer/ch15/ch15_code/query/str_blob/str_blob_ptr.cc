#include "str_blob_ptr.h"

#include <stdexcept>

#include "str_blob_ptr_error.h"
#include "str_blob.h"

StrBlobPtr::StrBlobPtr(StrBlob &a, RankType rank)
  : curr_(rank), wptr_(a.data_) {}

StrBlobPtr &StrBlobPtr::operator++() {
  // 保证异常安全, 先检测改变后的状态
  RankType modified_rank = curr_ + 1;
  Check(modified_rank, StrBlobPtrError::kIncrefPastEnd);

  ++curr_;
  return *this;
}
StrBlobPtr StrBlobPtr::operator++(int) & {
  auto ret = *this;
  this->operator++();
  return ret;
}
StrBlobPtr &StrBlobPtr::operator--() {
  RankType modified_rank = curr_ - 1;
  Check(modified_rank, StrBlobPtrError::kDecrefPastBegin);

  --curr_;
  return *this;
}
StrBlobPtr StrBlobPtr::operator--(int) & {
  auto ret = *this;
  this->operator--();
  return ret;
}
StrBlobPtr StrBlobPtr::operator+(const int &n) {
  RankType modified_rank = curr_ + n;
  Check(modified_rank, StrBlobPtrError::kIncrefPastEnd);

  auto ret = *this;
  ret.curr_ += n;
  return ret;
}
StrBlobPtr StrBlobPtr::operator-(const int &n) {
  RankType modified_rank = curr_ - n;
  Check(modified_rank, StrBlobPtrError::kDecrefPastBegin);

  auto ret = *this;
  ret.curr_ -= n;
  return ret;
}

std::string &StrBlobPtr::operator*() {
  RankType modified_rank = curr_;
  CheckDeref(modified_rank, StrBlobPtrError::kDerefPastEnd);
  auto def = wptr_.lock();
  return (*def)[curr_];
}
std::string *StrBlobPtr::operator->() {
  return &this->operator*();
}

void StrBlobPtr::Check(RankType modified_rank, const char *msg) const {
  auto ret = wptr_.lock();
  if (!ret) {
    throw std::runtime_error(StrBlobPtrError::kUnBoundError);
  }
  if (modified_rank > ret->size()) {
    throw std::out_of_range(msg);
  }
}
void StrBlobPtr::CheckDeref(RankType modified_rank, const char *msg) const {
  auto ret = wptr_.lock();
  if (!ret) {
    throw std::runtime_error(StrBlobPtrError::kUnBoundError);
  }
  if (modified_rank >= ret->size()) {
    throw std::out_of_range(msg);
  }
}


ConstStrBlobPtr::ConstStrBlobPtr(StrBlob &a, RankType rank)
    : curr_(rank), wptr_(a.data_) {}

ConstStrBlobPtr &ConstStrBlobPtr::operator++() {
  // 保证异常安全, 先检测改变后的状态
  RankType modified_rank = curr_ + 1;
  Check(modified_rank, StrBlobPtrError::kIncrefPastEnd);

  ++curr_;
  return *this;
}
ConstStrBlobPtr ConstStrBlobPtr::operator++(int) & {
  auto ret = *this;
  this->operator++();
  return ret;
}
ConstStrBlobPtr &ConstStrBlobPtr::operator--() {
  RankType modified_rank = curr_ - 1;
  Check(modified_rank, StrBlobPtrError::kDecrefPastBegin);

  --curr_;
  return *this;
}
ConstStrBlobPtr ConstStrBlobPtr::operator--(int) & {
  auto ret = *this;
  this->operator--();
  return ret;
}
ConstStrBlobPtr ConstStrBlobPtr::operator+(const int &n) {
  RankType modified_rank = curr_ + n;
  Check(modified_rank, StrBlobPtrError::kIncrefPastEnd);

  auto ret = *this;
  ret.curr_ += n;
  return ret;
}
ConstStrBlobPtr ConstStrBlobPtr::operator-(const int &n) {
  RankType modified_rank = curr_ - n;
  Check(modified_rank, StrBlobPtrError::kDecrefPastBegin);

  auto ret = *this;
  ret.curr_ -= n;
  return ret;
}

bool ConstStrBlobPtr::operator!=(const ConstStrBlobPtr &rhs) {
  auto lsp = wptr_.lock();
  auto rsp = rhs.wptr_.lock();
  if (!lsp || !rsp) {
    throw std::runtime_error(StrBlobPtrError::kUnBoundError);
  }
  return (lsp == rsp) && (curr_ != rhs.curr_);
}

const std::string &ConstStrBlobPtr::operator*() {
  RankType modified_rank = curr_;
  CheckDeref(modified_rank, StrBlobPtrError::kDerefPastEnd);
  auto def = wptr_.lock();
  return (*def)[curr_];
}
const std::string *ConstStrBlobPtr::operator->() {
  return &this->operator*();
}

void ConstStrBlobPtr::Check(RankType modified_rank, const char *msg) const {
  auto ret = wptr_.lock();
  if (!ret) {
    throw std::runtime_error(StrBlobPtrError::kUnBoundError);
  }
  if (modified_rank > ret->size()) {
    throw std::out_of_range(msg);
  }
}
void ConstStrBlobPtr::CheckDeref(RankType modified_rank, const char *msg) const {
  auto ret = wptr_.lock();
  if (!ret) {
    throw std::runtime_error(StrBlobPtrError::kUnBoundError);
  }
  if (modified_rank >= ret->size()) {
    throw std::out_of_range(msg);
  }
}

bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  auto lsp = lhs.wptr_.lock();
  auto rsp = rhs.wptr_.lock();
  if (!lsp || !rsp) {
    throw std::runtime_error(StrBlobPtrError::kUnBoundError);
  }
  return (lsp == rsp) && (lhs.curr_ == rhs.curr_);
}

bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  return !(lhs == rhs);
}
bool operator<(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  auto lsp = lhs.wptr_.lock();
  auto rsp = rhs.wptr_.lock();
  if (!lsp || !rsp) {
    throw std::runtime_error(StrBlobPtrError::kUnBoundError);
  }
  if (lsp != rsp) {
    throw std::runtime_error(StrBlobPtrError::kNotSameStrBlob);
  }
  return lhs.curr_ < rhs.curr_;
}