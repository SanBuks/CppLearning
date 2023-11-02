#include <iostream>
#include <thread>

// RAII 处理子线程资源回收问题
class ThreadGuard {
 public:
  explicit ThreadGuard(std::thread &t) : t_(t) {}
  ThreadGuard(const ThreadGuard &rhs) = delete;
  ThreadGuard &operator=(const ThreadGuard &rhs) = delete;
  ~ThreadGuard() {
    if (t_.joinable()) {
      // notify
      t_.join();
    }
  }
 private:
  std::thread &t_;
};

int main() {
  const std::string str = "Hello Concurrent World!\n";
  auto func = [](const std::string &str) { std::cout << str; };
  std::thread t(func, str);
  ThreadGuard guard(t);
  std::this_thread::sleep_for(std::chrono::seconds(1));
}