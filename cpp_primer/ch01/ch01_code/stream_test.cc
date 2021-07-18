#include <iostream>
#include <fstream>

int main() {
  std::ifstream file("stream_test.data");
  if (file) {
    int times = 0, number;
    while(file) {
      file >> number;
      ++times;
      std::cout << times << "\n";
      std::cout << "file stream status is : \n";
      std::cout << "eof bit is " << file.eof() << "\n";
      std::cout << "fail bit is " << file.fail() << "\n";
      std::cout << "bad bit is " << file.bad() << "\n";
      std::cout << "-------------------------------\n";
    }
  }
  std::cout << "file stream status is : \n";
  std::cout << "eof bit is " << file.eof() << "\n";
  std::cout << "fail bit is " << file.fail() << "\n";
  std::cout << "bad bit is " << file.bad() << "\n";
  return 0;
}