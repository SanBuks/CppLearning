#include <iostream>
#include <thread>

/**
 * 1. RAII 处理子线程资源回收问题
 * 2. RAII 处理异常抛出问题时子线程处理问题
 * 3. 三种解决子线程资源的方法:
 *   - smart pointer
 *   - join
 *   - copy
 */

class ThreadGuard {
 public:
  explicit ThreadGuard(std::thread &t) : t_(t) {}
  ThreadGuard(const ThreadGuard &rhs) = delete;
  ThreadGuard &operator=(const ThreadGuard &rhs) = delete;
  ~ThreadGuard() {
    if (t_.joinable()) {
      // ... 主动激活子线程结束
      t_.join();
    }
  }
 private:
  std::thread &t_;
};

int main() {
  const std::string str = "Hello Concurrent World!\n";
  auto func = [](const std::string &str) {
    // simulate tx
    for (int i = 0; i < 5; ++i)
      std::cout << str;
  };
  std::thread t(func, str);
  ThreadGuard guard(t);
  throw std::runtime_error("force throw exception!");
}