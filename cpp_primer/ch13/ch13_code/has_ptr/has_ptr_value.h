#ifndef CPP_PRIMER_CH13_CODE_HAS_PTR_VALUE_H_
#define CPP_PRIMER_CH13_CODE_HAS_PTR_VALUE_H_

#include <string>

class HasPtrValue {
 public:
  friend void swap(HasPtrValue &lhs, HasPtrValue &rhs);

  explicit HasPtrValue(std::string s = std::string());
  HasPtrValue(const HasPtrValue &has_ptr);
  HasPtrValue &operator=(const HasPtrValue &rhs);
  ~HasPtrValue();

  bool operator<(HasPtrValue &rhs);

  const std::string &GetStr() { return *ps_; }

  void Print() const ;
 private:
  std::string *ps_;
  int i_;
};

void swap(HasPtrValue &lhs, HasPtrValue &rhs);
#endif
