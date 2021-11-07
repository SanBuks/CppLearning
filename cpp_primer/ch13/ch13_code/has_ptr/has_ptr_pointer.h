#ifndef CPP_PRIMER_CH13_CODE_HAS_PTR_POINTER_H_
#define CPP_PRIMER_CH13_CODE_HAS_PTR_POINTER_H_

#include <string>

class HasPtrPointer {
 public:
  friend void swap(HasPtrPointer &lhs, HasPtrPointer &rhs);
  explicit HasPtrPointer(std::string s = std::string());
  HasPtrPointer(const HasPtrPointer &has_ptr);
  HasPtrPointer &operator=(const HasPtrPointer &rhs);
// 与 HasPtrPointer &operator=(const HasPtrPointer &rhs) 产生歧义
// HasPtrPointer &operator=(HasPtrPointer rhs);
  HasPtrPointer(HasPtrPointer &&has_ptr) noexcept;
  HasPtrPointer &operator=(HasPtrPointer &&rhs) noexcept;
  ~HasPtrPointer();

  const std::string &GetStr() { return *ps_; }
 private:
  std::string *ps_;
  int i_;
  std::size_t *use_;
};

#endif
