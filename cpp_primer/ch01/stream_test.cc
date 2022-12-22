#include <iostream>
#include <fstream>

#include "stream_test_data_config.h"

// 显示 cin 读取时状态位变化
// eof(), bad() 可以等价显示对应状态位, 而 fail() 等价
// ifs.rdstate() & (std::fstream::failbit | std::fstream::badbit)
bool inline GetFailBit(std::iostream &s) {
  return s.rdstate() & std::iostream::failbit;
}

void PrintIOStreamState(std::iostream &file) {
  std::cout << "eof bit is " << file.eof() << "\n";
  std::cout << "bad bit is " << file.bad() << "\n";
  std::cout << "fail bit is " << GetFailBit(file) << "\n";
  std::cout << "fail() is " << file.fail() << "\n";
}

int main() {
  std::fstream file((data_path::kStreamTestDataPath));
  if (file) {
    int times = 0, number;
    while (file) {
      file >> number;
      ++times;
      std::cout << times << "\n";
      std::cout << "file stream status is : \n";
      PrintIOStreamState(file);
      std::cout << "-------------------------------\n";
    }
    std::cout << "final file stream status is : \n";
    PrintIOStreamState(file);
  } else {
    std::cout << "can't open data file!\n";
    exit(1);
  }
  return 0;
}