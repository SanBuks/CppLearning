#include "str_vec.h"
#include <algorithm>

StrVec::StrVec() : elements_(nullptr), first_free_(nullptr), cap_(nullptr) {}
StrVec::StrVec(const StrVec &str_vec) {
  auto new_data = AllocNCopy(str_vec.Begin(), str_vec.End());
  elements_ = new_data.first;
  first_free_ = cap_ = new_data.second;
}
StrVec::StrVec(std::initializer_list<std::string> il) {
  auto new_data = AllocNCopy(il.begin(), il.end());
  elements_ = new_data.first;
  first_free_ = cap_ = new_data.second;
}
StrVec &StrVec::operator=(const StrVec &rhs) {
  using std::swap;
  if (this == &rhs) {
    return *this;
  }
  StrVec temp(rhs);
  swap(*this, temp);
  return *this;
}
StrVec &StrVec::operator=(std::initializer_list<std::string> il) {
  using std::swap;
  if (Size() == il.size() && std::equal(elements_, first_free_, il.begin())) {
    return *this;
  }
  StrVec temp(il);
  swap(*this, temp);
  return *this;
}

StrVec::StrVec(StrVec &&str_vec) noexcept
    : elements_(str_vec.elements_),
      first_free_(str_vec.first_free_),
      cap_(str_vec.cap_) {
  str_vec.elements_ = str_vec.first_free_ = str_vec.cap_ = nullptr;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
  if (this != &rhs) {
    Free();
    elements_ = rhs.elements_;
    first_free_ = rhs.first_free_;
    cap_ = rhs.cap_;
    rhs.elements_ = rhs.first_free_ = rhs.cap_ = nullptr;
  }
  return *this;
}

StrVec::~StrVec() {
  Free();
}

void StrVec::PushBack(const std::string &s) {
  // 首先检查是否满了, 满了扩容
  ChkNAlloc();
  alloc.construct(first_free_++, s);
}

void StrVec::PushBack(std::string &&s) {
  ChkNAlloc();
  alloc.construct(first_free_++, std::move(s));
}

void StrVec::ChkNAlloc() {
  if (Size() == Capacity()) {
    Reallocate();
  }
}

StrVec::Range StrVec::AllocNCopy(const std::string *b, const std::string *e) {
  // 根据迭代器范围分配内存
  auto data = alloc.allocate(e - b);
  // {elements, first_free}
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::Free() {
  if (elements_) {
    std::for_each(elements_, first_free_,
                  [](std::string &p) {alloc.destroy(&p);});
    alloc.deallocate(elements_, cap_ - elements_);
  }
}

void StrVec::Reallocate() {
  // 容量翻倍
  auto new_capacity = Size() ? 2 * Size() : 1;
  // 分配内存指向第一个位置
  auto elements_temp = alloc.allocate(new_capacity);

  // 方法 1: 拷贝原来的元素
  auto p = elements_temp;
  auto q = elements_;
  for (std::size_t i = 0; i != Size(); ++i) {
    // 调用拷贝构造函数
    // alloc.construct(p++, *q++);
    // 调用拷贝构造函数
    alloc.construct(p++, std::move(*q++));
  }
  auto first_free_temp = p;
  // 方法 2: 移动原来的元素
//  auto first_free_temp = uninitialized_copy(make_move_iterator(Begin()),
//                                            make_move_iterator(End()),
//                                            elements_temp);

  // 释放原来的内存空间
  Free();
  // 更新
  elements_ = elements_temp;
  first_free_ = first_free_temp;
  cap_ = elements_ + new_capacity;
}

void swap(StrVec &lhs, StrVec &rhs) {
  using std::swap;
  swap(lhs.cap_, rhs.cap_);
  swap(lhs.elements_, rhs.elements_);
  swap(lhs.first_free_, rhs.first_free_);
}
bool operator==(const StrVec &lhs, const StrVec &rhs) {
  return lhs.Size() == rhs.Size() &&
         std::equal(lhs.elements_, lhs.first_free_, rhs.elements_);
}
bool operator!=(const StrVec &lhs, const StrVec &rhs) {
  return !(lhs == rhs);
}
bool operator<(const StrVec &lhs, const StrVec &rhs) {
  if (lhs == rhs) { return false; }
  bool is_shorter = lhs.Size() <= rhs.Size();
  size_t min_size = is_shorter ? lhs.Size() : rhs.Size();
  for (size_t i = 0; i != min_size; ++i) {
    if (rhs[i] < lhs[i]) {
      return false;
    }
  }
  return is_shorter;
}