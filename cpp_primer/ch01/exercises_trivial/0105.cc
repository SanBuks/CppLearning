#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << " Please Enter two number! \n";
  int v1, v2;
  v1 = v2 = 0;
  std::cin >> v1 >> v2;
  std::cout << "The product is : ";
  std::cout << v1 * v2;
  std::cout << "\n";
  return 0;
}
