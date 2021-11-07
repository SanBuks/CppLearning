#include "has_ptr_value.h"
#include "has_ptr_pointer.h"

#include <iostream>
#include <vector>
#include <algorithm>

void TestHasPtrValue() {
  HasPtrValue ptr(std::string("test"));
  HasPtrValue ptr_c(ptr);
  std::cout << ptr.GetStr() << "\n";
  std::cout << ptr_c.GetStr() << "\n";

  HasPtrPointer ptr_pointer(std::string("test"));
  HasPtrPointer& ptr_pointer_c(ptr_pointer);
}
void TestHasPtrValueSwap() {

  std::vector<HasPtrValue> vec;
  vec.emplace_back(std::string("3"));
  vec.emplace_back(std::string("2"));
  vec.emplace_back(std::string("4"));
  vec.emplace_back(std::string("1"));

  for (const auto &item : vec) {
    item.Print();
    std::cout << "\n";
  }

  std::sort(vec.begin(), vec.end());

  for (const auto &item : vec) {
    item.Print();
    std::cout << "\n";
  }
}

void TestHasPtrPointerAmbiguous() {
  HasPtrPointer ptr(std::string("test"));
  HasPtrPointer ptr_c(ptr);
  // HasPtrPointer::HasPtrPointer(HasPtrPointer &&has_ptr) 产生歧义
  ptr = HasPtrPointer();
}

int main() {
//  TestHasPtrValue();
//  TestHasPtrValueSwap();
  TestHasPtrPointerAmbiguous();
  return 0;
}