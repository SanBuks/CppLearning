#include <thread>
#include <string>
#include <format>
#include <memory>
#include <iostream>
#include <shared_mutex>

// 懒汉式: double check + shared_ptr, 不需要手动释放
class SingletonLazy {
 public:

  static std::shared_ptr<SingletonLazy> GetInstance() {
    if (instance_) return instance_;           // 节省加锁性能

    std::lock_guard<std::mutex> lock(mutex_);
    if (instance_) return instance_;           // 防止第一次判断期后创建对象前上锁
    auto deleter = [](SingletonLazy *item) {   // 安全释放器
      std::cout << std::format("destructed by func\n");
      delete item;
    };
    // 存在 new -> construct -> assign 编译器优化为 new -> assign -> construct
    return (instance_ = std::shared_ptr<SingletonLazy>(new SingletonLazy, deleter));
  }

  void Print() {
    std::shared_lock<std::shared_mutex> lock(dmutex_);
    std::cout << std::format("object[{}]: {}", static_cast<void *>(this), str) << "\n";
  }

  SingletonLazy(const SingletonLazy &rhs) = delete;
  SingletonLazy &operator=(const SingletonLazy &rhs) = delete;

 private:
  SingletonLazy() = default;
  ~SingletonLazy() { std::cout << std::format("destructed\n"); }  // 无法通过 shared_ptr 手动释放对象

  mutable std::shared_mutex dmutex_;
  std::string str{"123"};

  static std::mutex mutex_;
  static std::shared_ptr<SingletonLazy> instance_;
};

std::mutex SingletonLazy::mutex_;
std::shared_ptr<SingletonLazy> SingletonLazy::instance_;

int main() {
  std::jthread t1([] { auto item = SingletonLazy::GetInstance(); item->Print(); });
  std::jthread t2([] { auto item = SingletonLazy::GetInstance(); item->Print(); });
  std::jthread t3([] { auto item = SingletonLazy::GetInstance(); item->Print(); });
  std::jthread t4([] { auto item = SingletonLazy::GetInstance(); item->Print(); });

  return 0;
}