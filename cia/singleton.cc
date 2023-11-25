#include <thread>
#include <string>
#include <iostream>
#include <shared_mutex>

// C++11 及以后的标准实现方式
class SingletonStandard {
 public:
  static SingletonStandard &GetInstance() {
    // C++11 及以后 确保 局部静态变量 只会初始化一个对象
    static SingletonStandard singleton;
    return singleton;
  }

  void Print() {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    std::cout << str << "\n";
  }

  SingletonStandard(const SingletonStandard &rhs) = delete;
  SingletonStandard &operator=(const SingletonStandard &rhs) = delete;

 private:
  SingletonStandard() = default;
  std::string str{"123"};
  mutable std::shared_mutex mutex_;
};

// C++11


int main() {
  std::thread t1([]{ auto &item = SingletonStandard::GetInstance(); item.Print(); });
  std::thread t2([]{ auto &item = SingletonStandard::GetInstance(); item.Print(); });
  t1.join();
  t2.join();
  return 0;
}