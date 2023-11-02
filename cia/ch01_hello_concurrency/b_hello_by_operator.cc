#include <iostream>
#include <thread>

class Hello {
 public:
  explicit Hello(int &i) : i(i) {}
  void operator()(const std::string &str) {
    std::cout << str;
    for (int j = 0; j < 3; ++j)
      std::cout << i << "\n";
  }
 private:
  int &i;
};

int main() {
  int local = 3;
  const std::string str = "Hello Concurrent World!\n";
  std::thread t(Hello{local}, str);  // 调用仿函数, {} 防止整个表达式解释成函数指针
//  t.join();
  t.detach();                        // detach 会产生资源释放问题
  std::this_thread::sleep_for(std::chrono::seconds(1));  // 防止主线程结束 -> 主进程结束 -> 回收资源
}