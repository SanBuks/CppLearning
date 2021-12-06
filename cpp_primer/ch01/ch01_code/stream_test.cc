#include <iostream>
#include <fstream>

#include "stream_test_data_config.h"

int main() {
  std::ifstream file(data_path::kStreamTestDataPath);
  if (file) {
    int times = 0, number;
    while (file) {
      file >> number;
      ++times;
      std::cout << times << "\n";
      std::cout << "file stream status is : \n";
      std::cout << "eof bit is " << file.eof() << "\n";
      std::cout << "fail bit is " << file.fail() << "\n";
      std::cout << "bad bit is " << file.bad() << "\n";
      std::cout << "-------------------------------\n";
    }
    std::cout << "file stream status is : \n";
    std::cout << "eof bit is " << file.eof() << "\n";
    std::cout << "fail bit is " << file.fail() << "\n";
    std::cout << "bad bit is " << file.bad() << "\n";
  } else {
    std::cout << "can't open data file!\n";
  }
  return 0;
}
