#include <iostream>
#include <thread>

int main() {
  const std::string str = "Hello Concurrent World!\n";
  auto func = [](const std::string &str) { std::cout << str; };
  std::thread t(func, str);

  try {
    // ...
    // notify 通知子线程结束
    std::this_thread::sleep_for(std::chrono::seconds(1));
  } catch (std::exception &ex) {
    t.join();  // 必须处理子线程
    throw;
  }

}