#include <compare>
#include <iostream>
#include <format>
#include <optional>

std::optional<int> GetData(bool getData) {
  if (getData) return 42;
  return std::nullopt;
}

int main() {
  std::cout << GetData(true).value_or(3) << "\n";
  return 0;
}
