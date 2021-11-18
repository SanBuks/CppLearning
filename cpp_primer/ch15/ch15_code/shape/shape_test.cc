#include "rectangular.h"

int main() {
  Rectangular r1;
  Rectangular r2("00001", "rectangular", {10.0, 20.0}, {-20.0, 20.0}, 90.0);
  r1.printInfo();
  std::cout << "\n";
  r2.printInfo();
  std::cout << "\n";
  return 0;
}