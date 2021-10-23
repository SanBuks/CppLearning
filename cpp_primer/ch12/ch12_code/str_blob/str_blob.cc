#include "str_blob.h"

#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "str_blob_error_message.h"

StrBlob::StrBlob() : data_(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il)
    : data_(std::make_shared<std::vector<std::string>>(il)) {}

const std::string &StrBlob::operator[](SizeType t) const {
  return (*data_)[t];
}
std::string &StrBlob::operator[](SizeType t) {
  return const_cast<std::string &>(static_cast<const StrBlob&>(*this)[t]);
}

void StrBlob::PushBack(const std::string &t) {
  data_->push_back(t);
}
void StrBlob::PopBack() {
  Check(0, StrBlobErrorMessage::kPopBackEmptyError);
  data_->pop_back();
}

std::string &StrBlob::Front() {
  return const_cast<std::string &>(static_cast<const StrBlob &>(*this).Front());
}
std::string &StrBlob::Back() {
  return const_cast<std::string &>(static_cast<const StrBlob &>(*this).Back());
}
const std::string &StrBlob::Front() const {
  Check(0, StrBlobErrorMessage::kFrontEmptyError);
  return data_->front();
}
const std::string &StrBlob::Back() const {
  Check(0, StrBlobErrorMessage::kBackEmptyError);
  return data_->back();
}

void StrBlob::Check(SizeType i, const std::string &msg) const {
  if (i >= data_->size()) {
    throw std::out_of_range(msg);
  }
}

//StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
//StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data_->size()); }