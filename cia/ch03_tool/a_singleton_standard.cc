#include <thread>
#include <string>
#include <format>
#include <iostream>
#include <shared_mutex>

// C++11 及以后的标准实现方式
class SingletonStandard{
 public:
  static SingletonStandard &GetInstance() {
    // C++11 及以后 确保 局部静态变量 只会初始化一个对象
    // 程序结束后自动销毁
    static SingletonStandard singleton;
    return singleton;
  }

  void Print() {
    std::shared_lock<std::shared_mutex> lock(dmutex_);
    std::cout << std::format("object[{}]: {}", static_cast<void *>(this), str)<< "\n";
  }

  SingletonStandard(const SingletonStandard &rhs) = delete;
  SingletonStandard &operator=(const SingletonStandard &rhs) = delete;
  ~SingletonStandard() { std::cout << std::format("destructed\n"); }

 private:
  SingletonStandard() = default;
  std::string str{"123"};
  mutable std::shared_mutex dmutex_;
};

int main() {
  std::thread t1([]{ auto &item = SingletonStandard::GetInstance(); item.Print(); });
  std::thread t2([]{ auto &item = SingletonStandard::GetInstance(); item.Print(); });
  t1.join();
  t2.join();
  return 0;
}