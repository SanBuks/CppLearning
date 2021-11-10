#ifndef CPP_PRIMER_CH13_CODE_STR_VEC_H_
#define CPP_PRIMER_CH13_CODE_STR_VEC_H_

#include <string>
#include <memory>
#include <initializer_list>

class StrVec;
bool operator==(const StrVec &lhs, const StrVec &rhs);
bool operator!=(const StrVec &lhs, const StrVec &rhs);
bool operator<(const StrVec &lhs, const StrVec &rhs);
class StrVec {
 public:
  typedef typename std::pair<std::string *, std::string *> Range;
  friend void swap(StrVec &lhs, StrVec &rhs);
  friend bool operator==(const StrVec &lhs, const StrVec &rhs);
  friend bool operator!=(const StrVec &lhs, const StrVec &rhs);
  friend bool operator<(const StrVec &lhs, const StrVec &rhs);

  StrVec();
  // 没有冗余空间拷贝
  StrVec(const StrVec &str_vec);
  StrVec(std::initializer_list<std::string> il);
  // 没有冗余空间赋值
  StrVec &operator=(const StrVec &rhs);
  StrVec &operator=(std::initializer_list<std::string> il);
  StrVec(StrVec &&) noexcept;
  StrVec &operator=(StrVec &&) noexcept;
  ~StrVec();


  std::string &operator[](std::size_t n) { return elements_[n]; }
  const std::string &operator[](std::size_t n) const { return elements_[n]; }

  void PushBack(const std::string &s);  // 末尾增加元素
  void PushBack(std::string &&s); // 末尾增加元素 右值版本

  std::size_t Size() const { return first_free_ - elements_; }
  std::size_t Capacity() const { return cap_ - elements_; }

  std::string *Begin() { return elements_; }
  std::string *End() { return first_free_; }
  const std::string *Begin() const { return elements_; }
  const std::string *End() const { return first_free_; }
  const std::string *CBegin() const { return elements_; }
  const std::string *CEnd() const { return first_free_; }

 private:
  // 动态内存分配器
  static std::allocator<std::string> alloc;

  // 查看是否需要额外扩充空间
  void ChkNAlloc();
  // 分配内存并构造范围内的拷贝
  Range AllocNCopy (const std::string *, const std::string *);

  void Free();
  void Reallocate();

  std::string *elements_;    // 指向第一个元素
  std::string *first_free_;  // 指向第一个空余空间
  std::string *cap_;         // 指向尾后
};

std::allocator<std::string> StrVec::alloc;
void swap(StrVec &lhs, StrVec &rhs);

#endif