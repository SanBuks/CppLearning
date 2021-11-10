#include <iostream>
#include <fstream>
#include <functional>
#include <string>

#include "sales_data.h"
#include "sales_data_config.h"

void TestPlus() {
  SalesData t1, t2;
  std::fstream fs(data_path::kSalesDataPath);
  if (fs) {
    fs >> t1 >> t2;
    SalesData result = t1 + t2;
    std::cout << result << std::endl;
  } else {
    std::cout << "open file failure!\n";
  }
}

//void Test() {
//  SalesData t;
//  std::cin >> t;
//  std::string str = static_cast<std::string>(t);
//  std::cout << str;
//}

int TestInt(int a, int b) { return 2; }
int main() {
//  TestPlus();

  return 0;
}
