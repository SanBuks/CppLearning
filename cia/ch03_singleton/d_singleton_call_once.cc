#include <thread>
#include <string>
#include <format>
#include <memory>
#include <iostream>
#include <shared_mutex>
#include <mutex>

// C++11 call_once 确保指针形式单例正确性
class SingletonCallOnce {
 public:

  static std::shared_ptr<SingletonCallOnce> GetInstance() {
    static std::once_flag flag;  // 只会初始化一次
    std::call_once(flag, [](){   // 多个线程只会调用一次
      instance_ = std::shared_ptr<SingletonCallOnce>(new SingletonCallOnce,
                                                     [&](SingletonCallOnce *item) { std::cout << std::format("destructed by func\n"); delete item; });
    });
    return instance_;
  }

  void Print() {
    std::shared_lock<std::shared_mutex> lock(dmutex_);
    std::cout << std::format("object[{}]: {}", static_cast<void *>(this), str) << "\n";
  }

  SingletonCallOnce(const SingletonCallOnce &rhs) = delete;
  SingletonCallOnce &operator=(const SingletonCallOnce &rhs) = delete;

 private:
  SingletonCallOnce() = default;
  ~SingletonCallOnce() { std::cout << std::format("destructed\n"); }  // 无法通过 shared_ptr 手动释放对象

  mutable std::shared_mutex dmutex_;
  std::string str{"123"};

  static std::mutex mutex_;
  static std::shared_ptr<SingletonCallOnce> instance_;
};

std::mutex SingletonCallOnce::mutex_{};
std::shared_ptr<SingletonCallOnce> SingletonCallOnce::instance_ = nullptr;

int main() {
  std::jthread t1([] { std::this_thread::sleep_for(std::chrono::seconds(1)); auto item = SingletonCallOnce::GetInstance(); item->Print(); });
  std::jthread t2([] { std::this_thread::sleep_for(std::chrono::seconds(1)); auto item = SingletonCallOnce::GetInstance(); item->Print(); });
  std::jthread t3([] { std::this_thread::sleep_for(std::chrono::seconds(1)); auto item = SingletonCallOnce::GetInstance(); item->Print(); });
  std::jthread t4([] { std::this_thread::sleep_for(std::chrono::seconds(1)); auto item = SingletonCallOnce::GetInstance(); item->Print(); });
  return 0;
}