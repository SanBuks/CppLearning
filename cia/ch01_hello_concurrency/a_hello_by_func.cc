#include <iostream>
#include <thread>

// hello 是新线程的起始函数
void hello(const std::string &str) {
  std::cout << str;
}

// main 是主线程的起始函数
int main() {
  const std::string str = "Hello Concurrent World!\n";
  std::thread t(hello, str);  // 主线程 是 新线程的起始线程
  t.join();                   // 令主线程等待子线程
                              // 不 join 主线程会优化调用 t 的 terminate() 进行析构
}