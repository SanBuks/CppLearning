#include <iostream>
#include <thread>

int main() {
  const std::string str = "Hello Concurrent World!\n";
  auto func = [](const std::string &str) { std::cout << str; };
  std::thread t(func, str);
  t.join();
}