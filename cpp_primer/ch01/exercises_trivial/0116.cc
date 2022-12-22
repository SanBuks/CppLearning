#include <iostream>

int main() {
  long long sum = 0;
  int n;
  while (std::cin >> n) sum += n;
  std::cout << sum;
  return 0;
}