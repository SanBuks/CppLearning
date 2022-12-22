#include <iostream>
#include <fstream>
#include "Sales_item.h"
#include "data_config.h"

int main() {
  Sales_item a, b;
  std::ifstream ifs(data_path::k0121DataPath);
  if (!ifs) {
    std::cout << "open file error!\n";
    return 0;
  }
  ifs >> a >> b;
  if (a.isbn() == b.isbn()) {
    std::cout << a + b << "\n";
    return 0;
  } else {
    std::cerr << "no same books\n";
    return 1;
  }
}