#include <iostream>
#include <thread>

int main() {
  int c = 0;
  auto func = [](int &i) { std::cout << ++i << "\n"; };
  std::thread t(func, std::ref(c));  // 避免传递右值
  t.join();
  std::cout << c << "\n";
}
