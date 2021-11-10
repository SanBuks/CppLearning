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

void TestEqual() {
  const char *p = "1234159";
  const char *q = "1234158";
  const char *m = "123415";
  String a(p, 7);
  String b(p, 7);
  String c(q, 7);
  String d(m, 6);


  std::cout << (a == b) << "\n" << (a == c) << "\n";
  std::cout << (a < c) << "\n" << (c < a) << "\n";
  std::cout << (d < a) << "\n" << (a < d) << "\n";
}

int main() {
  // TestPushBack();
  // TestMove();
  // TestAppend();
  TestEqual();
  return 0;
}