#include <iostream>
#include <fstream>
#include "Sales_item.h"
#include "data_config.h"

int main() {
  Sales_item cur;
  std::ifstream ifs(data_path::k0124DataPath);
  if (!ifs) {
    std::cout << "open file error!\n";
    return 0;
  }

  if (ifs >> cur) {
    Sales_item val;
    while (ifs >> val) {
      if (cur.isbn() == val.isbn())
        cur += val;
      else {
        std::cout << "the book's id is " << cur.isbn()
                  << " average price is " << cur.avg_price() << "\n";
        cur = val;
      }
    }
    std::cout << "the book's id is " << cur.isbn()
              << "average price is " << cur.avg_price() << "\n";
    return 0;
  }
  std::cerr << "no books!\n";
  return -1;
}
