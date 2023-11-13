#include <compare>
#include <iostream>
#include <format>

int main() {
  int a{11};
  int b{13};

  std::strong_ordering result{a <=> b};
  if (result == std::strong_ordering::equal)
    std::cout << std::format("{} == {}", a, b);
  else if (result == std::strong_ordering::less)
    std::cout << std::format("{} < {}", a, b);
  else if (result == std::strong_ordering::greater)
    std::cout << std::format("{} > {}", a, b);

  std::cout << "\n";

  double c{3.13};
  double d{3.14};
  std::partial_ordering relation{c <=> d};
  if (std::is_eq(relation))
    std::cout << std::format("{} == {}", c, d);
  else if (std::is_lt(relation))
    std::cout << std::format("{} < {}", c, d);
  else if (std::is_gt(relation))
    std::cout << std::format("{} > {}", c, d);
  else if (relation == std::partial_ordering::unordered)
    std::cout << std::format("{} ? {}", c, d);
  return 0;
}