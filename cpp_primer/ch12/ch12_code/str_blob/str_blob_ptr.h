#ifndef CPP_PRIMER_CH12_CODE_STR_BLOB_PTR_H_
#define CPP_PRIMER_CH12_CODE_STR_BLOB_PTR_H_

#include <memory>
#include <vector>

class StrBlob;

// 类 随机迭代器类
class StrBlobPtr {
 public:
  typedef std::vector<std::string>::size_type RankType;

  StrBlobPtr() : curr_(0), wptr_() {};
  StrBlobPtr(StrBlob &a, RankType rank);
  StrBlobPtr(const StrBlobPtr &rhs) = default;
  StrBlobPtr &operator=(const StrBlobPtr &rhs) = default;
  ~StrBlobPtr() = default;

  RankType curr() const { return curr_; }

  StrBlobPtr &operator++();
  StrBlobPtr operator++(int) &;
  StrBlobPtr &operator--();
  StrBlobPtr operator--(int) &;
  StrBlobPtr operator+(const int &n);
  StrBlobPtr operator-(const int &n);

  bool operator!=(const StrBlobPtr &rhs);

  std::string &operator*() const;
  std::string *operator->() const;

 private:
  // 检测 即将改变的下标 是否在 [0, size] 中
  void Check(RankType modified_rank, const char *msg) const;
  // 检测 即将改变的下标 是否在 [0, size) 中
  void CheckDeref(RankType modified_rank, const char *msg) const;

  RankType curr_;
  std::weak_ptr<std::vector<std::string>> wptr_;
};

class ConstStrBlobPtr {
 public:
  typedef std::vector<std::string>::size_type RankType;

  ConstStrBlobPtr() : curr_(0), wptr_() {};
  ConstStrBlobPtr(StrBlob &a, RankType rank);
  ConstStrBlobPtr(const ConstStrBlobPtr &rhs) = default;
  ConstStrBlobPtr &operator=(const ConstStrBlobPtr &rhs) = default;
  ~ConstStrBlobPtr() = default;

  RankType curr() const { return curr_; }

  ConstStrBlobPtr &operator++();
  ConstStrBlobPtr operator++(int) &;
  ConstStrBlobPtr &operator--();
  ConstStrBlobPtr operator--(int) &;
  ConstStrBlobPtr operator+(const int &n);
  ConstStrBlobPtr operator-(const int &n);

  bool operator!=(const ConstStrBlobPtr &rhs);

  const std::string &operator*() const;
  const std::string *operator->() const;

 private:
  // 检测 即将改变的下标 是否在 [0, size] 中
  void Check(RankType modified_rank, const char *msg) const;
  // 检测 即将改变的下标 是否在 [0, size) 中
  void CheckDeref(RankType modified_rank, const char *msg) const;

  RankType curr_;
  std::weak_ptr<std::vector<std::string>> wptr_;
};
#endif