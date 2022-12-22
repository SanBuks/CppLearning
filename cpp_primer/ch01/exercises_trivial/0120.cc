#include <iostream>
#include <fstream>
#include "Sales_item.h"
#include "data_config.h"

int main() {
  Sales_item curr;
  std::ifstream ifs(data_path::k0120DataPath);
  if (!ifs) {
    std::cout << "open file error!\n";
    return 0;
  }
  while (ifs >> curr) {
    std::cout << curr << "\n";
  }
  return 0;
}