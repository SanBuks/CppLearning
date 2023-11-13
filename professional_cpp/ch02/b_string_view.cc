#include <string>
#include <iostream>

int main() {
  using namespace std::literals::string_view_literals;
  std::string_view stv = "123"sv;
  stv.remove_prefix(1);
  stv.remove_suffix(1);
  std::cout << std::string(stv) << "\n";
  return 0;
}
