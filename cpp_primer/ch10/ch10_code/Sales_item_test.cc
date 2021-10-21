#include "Sales_item.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>


int main() {
  std::ifstream file("../ch10_data/data_10_32");
  std::vector<Sales_item> vec;
  if (!file) {
    std::cout << "Open file failed! \n";
    return 1;
  }

  std::istream_iterator<Sales_item> is_eit;
  std::istream_iterator<Sales_item> is(file);
  while (is != is_eit) {
    vec.push_back(*is++);
  }
  std::sort(vec.begin(), vec.end(), compareIsbn);
  auto itb = vec.begin();
  while (itb != vec.end()) {
    const std::string &isbn = itb->isbn();
    auto ite = std::find_if_not(itb, vec.end(),
                                [&isbn](const Sales_item &item) {
                                  return item.isbn() == isbn;
                                });
    Sales_item sum(itb->isbn());
    std::cout << std::accumulate(itb, ite, sum) << "\n";
    itb = ite;
  }

  return 0;
}