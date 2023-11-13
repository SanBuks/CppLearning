#include <string>
#include <charconv>
#include <iostream>

int main() {
  using namespace std::string_literals;

  std::string literal = "literal suffix"s;
  std::string raw_literal = R"(raw literal "string")";
  std::cout << literal << "\n";
  std::cout << raw_literal << "\n";

  std::cout << std::to_string(3.14) << "\n";
  std::cout << std::stol("0xAF", nullptr, 16) << "\n";


  std::string intstr(50, ' ');
  auto [ptr, interr] = std::to_chars(intstr.data(), intstr.data() + intstr.size(), 1234567);
  if (interr != std::errc::value_too_large) {
    std::cout << intstr << "\n";
  }

  std::string doublestr(50, ' ');
  auto [ptr1, doubleerr] = std::to_chars(doublestr.data(), doublestr.data() + doublestr.size(), 0.3212234);
  if (doubleerr != std::errc::value_too_large) {
    std::cout << doublestr << "\n";
  }

  double value;
  auto [ptr2, valueerr] = std::from_chars(doublestr.data(), doublestr.data() + doublestr.size(), value, std::chars_format::fixed);
  if (valueerr != std::errc::result_out_of_range) {
    std::cout << value << "\n";
  }

  return 0;
}