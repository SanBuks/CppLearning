#include <iostream>
#include <fstream>
#include <map>
#include "Sales_item.h"
#include "data_config.h"

int main() {
  Sales_item cur;
  Sales_item val;
  std::map<std::string, Sales_item> result;

  std::ifstream ifs(data_path::k0123DataPath);
  if (!ifs) {
    std::cout << "open file error!\n";
    return 0;
  }

  while(ifs >> val)
    result[val.isbn()] += val;
  for (const auto &w: result) {
    std::cout << "the book id is " << w.first;
    std::cout << " average price is " << w.second.avg_price() << '\n';
  }
  return 0;
}
