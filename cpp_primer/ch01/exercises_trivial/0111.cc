#include <iostream>
#include <utility>

int main(int argc, char *argv[]) {
  int lo, hi;
  std::cout << "Please Enter two number: \n";
  std::cin >> lo >> hi;
  if (lo > hi) {
    std::swap(lo, hi);
  }
  for (; lo <= hi; ++lo) {
    std::cout << lo << " ";
  }
  return 0;
}
