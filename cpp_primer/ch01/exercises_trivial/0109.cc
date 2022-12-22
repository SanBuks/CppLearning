#include <iostream>

int main(int argc, char *argv[]) {
  int sum = 0, n = 50;
  while (n != 101) {
    sum += n++;
  }
  std::cout << sum;  // 3825
  return 0;
}