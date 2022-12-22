#include <iostream>
#include <fstream>
#include "Sales_item.h"
#include "data_config.h"

int main() {
  Sales_item sum, book;
  std::ifstream ifs(data_path::k0122DataPath);
  if (!ifs) {
    std::cout << "open file error!\n";
    return 0;
  }
  if (ifs >> sum) {
    while (ifs >> book) {
      sum += book;
    }
    std::cout << sum << "\n";
    return 0;
  } else {
    std::cerr << "no books\n";
    return 1;
  }
}
