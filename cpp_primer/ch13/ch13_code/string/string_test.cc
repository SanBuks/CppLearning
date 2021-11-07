#include <iostream>
#include <vector>

#include "m_string.h"

void TestAppend() {
  const char *p = "123415[";
  String s(p, 7);
  std::cout << s << "\n";
  std::cout << " -- " << s.Capacity() << " " << s.Size() << "\n";

  s.Append('x');
  std::cout << " -- " << s.Capacity() << " " << s.Size() << "\n";
}

void TestPushBack() {
  // no move control
  std::vector<String> vec;
  vec.push_back(String("23134", 5));
  std::cout << "size:" << vec.size() << " capacity:" << vec.capacity() << "\n";
  vec.push_back(String("23134", 5));
  std::cout << "size:" << vec.size() << " capacity:" << vec.capacity() << "\n";
  vec.push_back(String("23134", 5));
  std::cout << "size:" << vec.size() << " capacity:" << vec.capacity() << "\n";
  vec.push_back(String("23134", 5));
  std::cout << "size:" << vec.size() << " capacity:" << vec.capacity() << "\n";
}

void TestMove() {
  // has move control
  std::vector<String> vec;
  vec.push_back(String("23134", 5));
  std::cout << "size:" << vec.size() << " capacity:" << vec.capacity() << "\n";
  vec.push_back(String("23134", 5));
  std::cout << "size:" << vec.size() << " capacity:" << vec.capacity() << "\n";
  vec.push_back(String("23134", 5));
  std::cout << "size:" << vec.size() << " capacity:" << vec.capacity() << "\n";
  vec.push_back(String("23134", 5));
  std::cout << "size:" << vec.size() << " capacity:" << vec.capacity() << "\n";
}

int main() {
  TestMove();
  return 0;
}