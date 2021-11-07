#ifndef CPP_PRIMER_CH13_CODE_M_STRING_H_
#define CPP_PRIMER_CH13_CODE_M_STRING_H_

#include <memory>
#include <algorithm>
#include <iostream>

class String {

  friend std::ostream &operator<<(std::ostream &io, const String &str);
  friend void swap(String &lhs, String &rhs);

 public:
  String();
  String(const char *p, size_t n);
  String(const String &str);
  String &operator=(const String &rhs);
  String(String &&str) noexcept;
  String &operator=(String &&rhs) noexcept;
  ~String();

  std::size_t Size() const { return first_free_ - first_elem_; }
  std::size_t Capacity() const { return end_ - first_elem_; }
  char *Begin() { return first_elem_; }
  char *End() { return first_free_; }
  const char *Begin() const { return first_elem_; }
  const char *End() const { return first_free_; }
  const char *CBegin() const { return first_elem_; }
  const char *CEnd() const { return first_free_; }

  void Append(char c);

 private:
  void Reallocate();
  void Free();

  static std::allocator<char> alloc;
  static constexpr const size_t INIT_SIZE = 3;

  char *first_elem_;
  char *first_free_;
  char *end_;
};

std::allocator<char> String::alloc;

std::ostream &operator<<(std::ostream &os, const String &str) {
  std::for_each(str.CBegin(), str.CEnd(),
                [&os](const char &ch) { os << ch; });
  return os;
}

void swap(String &lhs, String &rhs) {
  using std::swap;
  swap(lhs.first_elem_, rhs.first_elem_);
  swap(lhs.first_free_, rhs.first_free_);
  swap(lhs.end_,        rhs.end_);
}

String::String()
    : first_elem_(alloc.allocate(INIT_SIZE)),
      first_free_(first_elem_), end_(first_elem_ + INIT_SIZE) {}

// 不多扩容
String::String(const char *p, size_t n)
    : first_elem_(alloc.allocate(n)),
      first_free_(first_elem_ + n), end_(first_free_) {
  std::for_each(first_elem_, first_free_,
                [&p](char &elem) { alloc.construct(&elem, *p++); });
}

// 不多扩容
String::String(const String &str) {
  size_t size = str.Size();
  first_elem_ = alloc.allocate(size);
  first_free_ = end_ = first_elem_ + size;
  std::uninitialized_copy(str.Begin(), str.End(), first_elem_);
  std::cout << "String(const String &str)\n";
}

String &String::operator=(const String &rhs) {
  if (this == &rhs) {
    return *this;
  }
  String temp(rhs);
  swap(*this, temp);
  std::cout << "String &operator=(const String &rhs)\n";
  return *this;
}

String::String(String &&str) noexcept
    : first_elem_(str.first_elem_),
      first_free_(str.first_free_),
      end_(str.end_) {
  str.first_elem_ = str.first_free_ = str.end_ = nullptr;
  std::cout << "String(String &&str)\n";
}

String &String::operator=(String &&rhs) noexcept {
  if (this == &rhs) {
    return *this;
  }
  Free();
  first_elem_=rhs.first_elem_;
  first_free_=rhs.first_free_;
  end_=rhs.end_;
  rhs.first_elem_ = rhs.first_free_ = rhs.end_ = nullptr;
  std::cout << "String &operator=(String &&rhs)\n";
  return *this;
}

String::~String() {
  Free();
}

void String::Free() {
  if (first_elem_) {
    std::for_each(first_elem_, first_free_,
                  [](char &elem) { alloc.destroy(&elem); });
    alloc.deallocate(first_elem_, end_ - first_elem_);
  }
}

void String::Reallocate() {
  auto new_capacity = Size() ? 2 * Size() : 1;
  auto first_elem_temp = alloc.allocate(new_capacity);

  auto p = first_elem_temp;
  auto q = first_elem_;
  for (size_t i = 0; i != Size(); ++i) {
    alloc.construct(p++, *q++);
  }
  auto first_free_temp = p;

  Free();

  first_elem_ = first_elem_temp;
  first_free_ = first_free_temp;
  end_ = first_elem_ + new_capacity;
}

void String::Append(char c) {
  if (first_free_ == end_) {
    Reallocate();
  }
  *first_free_++ = c;
}

#endif
