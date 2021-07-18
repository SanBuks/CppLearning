#include <iostream>
#include <string>

int main() {
  std::string number = "1234567890";
  char char_array[11] = "1234567890";
  std::string copy_string0(char_array, 1);
  std::string copy_string1(number, 2);
  std::string copy_string2(number, 3, 4);

  std::cout << copy_string0 << std::endl;


  return 0;
}