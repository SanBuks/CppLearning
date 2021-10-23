#ifndef CPP_PRIMER_CH12_CODE_STR_BLOB_H_
#define CPP_PRIMER_CH12_CODE_STR_BLOB_H_

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

// #include "str_blob_ptr.h"


// 共享数据字段的 vector<string>-like 类
class StrBlob {
  // friend class StrBlobPtr;
 public:
  typedef std::vector<std::string>::size_type SizeType;
  typedef std::vector<std::string>::size_type RankType;

 public:
  StrBlob();
  StrBlob(std::initializer_list<std::string> il);
  StrBlob(const StrBlob &rhs) = default;
  StrBlob &operator=(const StrBlob &rhs) = default;
  ~StrBlob() = default;

  bool Empty() const { return data_->empty(); }
  long UseCount() const { return data_.use_count(); }
  SizeType Size() const { return data_->size(); }

  const std::string &operator[](SizeType t) const;
  std::string &operator[](SizeType t);

  void PushBack(const std::string &t);
  void PopBack();

  const std::string &Front() const;
  const std::string &Back() const;
  std::string &Front();
  std::string &Back();

  // StrBlobPtr begin();
  // StrBlobPtr end();

 private:
  void Check(SizeType i, const std::string &msg) const;
  std::shared_ptr<std::vector<std::string>> data_;
};

#endif