#include <compare>
#include <iostream>
#include <format>
#include <optional>
#include <vector>

struct A {
  int a_{3};
  int b_{4};
  int c_[3]{1, 2, 3};
};

int main() {
  A item {
    .a_ = 100,
    .c_ = {2, 3, 4},
  };

  auto &[a, b, c] {item};
  ++a;
  ++b;
  ++c[0];
  std::cout << std::format("a_ = {}, b_ = {}, c_[0] = {}", item.a_, item.b_, item.c_[0]) << "\n";

  return 0;
}
