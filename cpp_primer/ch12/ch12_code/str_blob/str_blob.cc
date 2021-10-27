#include "str_blob.h"

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "str_blob_error.h"

StrBlob::StrBlob() : data_(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il)
    : data_(std::make_shared<std::vector<std::string>>(il)) {}

const std::string &StrBlob::operator[](RankType rank) const {
  RankType modified_rank = rank;
  CheckDeref(modified_rank, StrBlobError::kDerefPastEndError);
  return (*data_)[rank];
}
std::string &StrBlob::operator[](RankType rank) {
  return const_cast<std::string &>(static_cast<const StrBlob&>(*this)[rank]);
}

void StrBlob::PushBack(const std::string &t) {
  data_->push_back(t);
}
void StrBlob::PopBack() {
  CheckDeref(0, StrBlobError::kPopBackEmptyError);
  data_->pop_back();
}

std::string &StrBlob::Front() {
  return const_cast<std::string &>(static_cast<const StrBlob &>(*this).Front());
}
std::string &StrBlob::Back() {
  return const_cast<std::string &>(static_cast<const StrBlob &>(*this).Back());
}
const std::string &StrBlob::Front() const {
  CheckDeref(0, StrBlobError::kFrontEmptyError);
  return data_->front();
}
const std::string &StrBlob::Back() const {
  CheckDeref(0, StrBlobError::kBackEmptyError);
  return data_->back();
}

StrBlobPtr StrBlob::Begin() {
  return {*this, 0};
}
StrBlobPtr StrBlob::End() {
  return {*this, data_->size()};
}
ConstStrBlobPtr StrBlob::CBegin() {
  return {*this, 0};
}
ConstStrBlobPtr StrBlob::CEnd() {
  return {*this, data_->size()};
}

void StrBlob::CheckDeref(RankType modified_rank, const char *msg) const {
  if (modified_rank >= data_->size()) {
    throw std::out_of_range(msg);
  }
}