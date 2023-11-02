#include <iostream>
#include <thread>

int main() {
  char buff[100] = "Hello Concurrent World!\n";
  auto func = [](const std::string &str) { std::cout << str; };

  // 即使资源以 值形式传递, 仍然会存在错误

//std::thread t(func, str);  // 仍然存在资源被释放的危险, 因为线程空间中只保留 char *,  只在调用函数时才隐式转化
  std::thread t(func, std::string(buff));  // 显示防止隐式转化
  std::this_thread::sleep_for(std::chrono::seconds(1));
}