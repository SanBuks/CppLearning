#include <thread>
#include <string>
#include <iostream>
#include <format>
#include <shared_mutex>

// 饿汉式: 需要手动初始化, 手动释放对象
class SingletonHungry {
 public:

  static SingletonHungry *GetInstance() {
    return instance_;
  }

  static SingletonHungry *Init() {
    if (!instance_) {
      instance_ = new SingletonHungry;
    }
    return instance_;
  }

  void Print() {
    std::shared_lock<std::shared_mutex> lock(dmutex_);
    std::cout << std::format("object[{}]: {}", static_cast<void *>(this), str) << "\n";
  }

  SingletonHungry(const SingletonHungry &rhs) = delete;
  SingletonHungry &operator=(const SingletonHungry &rhs) = delete;
  ~SingletonHungry() { std::cout << std::format("destructed\n"); }

 private:
  SingletonHungry() = default;

  std::string str{"123"};
  mutable std::shared_mutex dmutex_;

  static SingletonHungry *instance_;
};

// 初始化操作只在主线程进行一次, 不需要加锁
SingletonHungry *SingletonHungry::instance_ = SingletonHungry::Init();

int main() {
  std::thread t1([] { auto item = SingletonHungry::GetInstance(); item->Print(); });
  std::thread t2([] { auto item = SingletonHungry::GetInstance(); item->Print(); });
  t1.join();
  t2.join();

  // 等待其他线程结束
  std::this_thread::sleep_for(std::chrono::seconds(2));
  // 手动释放对象
  delete SingletonHungry::GetInstance();

  return 0;
}