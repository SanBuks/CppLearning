#ifndef CPP_PRIMER_CH12_CODE_STR_BLOB_H_
#define CPP_PRIMER_CH12_CODE_STR_BLOB_H_

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "str_blob_ptr.h"

// 共享数据字段的 vector<string>-like 类
class StrBlob {

  friend class StrBlobPtr;
  friend class ConstStrBlobPtr;

 public:
  typedef std::vector<std::string>::size_type SizeType;
  typedef std::vector<std::string>::size_type RankType;

  StrBlob();
  StrBlob(std::initializer_list<std::string> il);
  StrBlob(const StrBlob &rhs) = default;
  StrBlob &operator=(const StrBlob &rhs) = default;
  ~StrBlob() = default;

  bool Empty() const { return data_->empty(); }
  long UseCount() const { return data_.use_count(); }
  SizeType Size() const { return data_->size(); }

  const std::string &operator[](RankType rank) const;
  std::string &operator[](RankType rank);

  void PushBack(const std::string &t);
  void PushBack(std::string &&t);
  void PopBack();

  const std::string &Front() const;
  const std::string &Back() const;
  std::string &Front();
  std::string &Back();

  StrBlobPtr Begin();
  StrBlobPtr End();
  ConstStrBlobPtr CBegin();
  ConstStrBlobPtr CEnd();

 private:
  // 检测 即将改变的下标 是否在 [0, size) 中
  // 不返回值 用来 解耦
  void CheckDeref(RankType modified_rank, const char *msg) const;
  std::shared_ptr<std::vector<std::string>> data_;
};

#endif