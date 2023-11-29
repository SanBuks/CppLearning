#include <thread>
#include <string>
#include <format>
#include <memory>
#include <iostream>
#include <shared_mutex>
#include <mutex>

// Singleton-Template
template <typename T>
class SingletonTemplate {
 public:
  static std::shared_ptr<T> GetInstance() {
    static std::once_flag flag;
    std::call_once(flag, [](){
      instance_ = std::shared_ptr<T>(new T, [&](T *item) { std::cout << std::format("destructed by func\n"); delete item; });
    });
    return instance_;
  }

  SingletonTemplate(const SingletonTemplate<T> &rhs) = delete;
  SingletonTemplate &operator=(const SingletonTemplate<T> &rhs) = delete;
 private:
  SingletonTemplate() = default;
  ~SingletonTemplate() { std::cout << std::format("destructed\n"); }
  static std::shared_ptr<T> instance_;
};

template<typename T>
std::shared_ptr<T> SingletonTemplate<T>::instance_ = nullptr;

// 某个单例类
class System {
 public:
  friend SingletonTemplate<System>;

  void Print() {
    std::shared_lock<std::shared_mutex> lock(dmutex_);
    std::cout << std::format("object[{}]: {}", static_cast<void *>(this), str) << "\n";
  }

  System(const System &rhs) = delete;
  System &operator=(const System &rhs) = delete;
  ~System() = default;
 private:
  System() = default;

  std::string str{"123"};
  mutable std::shared_mutex dmutex_;
};

int main() {
  std::jthread t1([] { std::this_thread::sleep_for(std::chrono::seconds(1)); auto item = SingletonTemplate<System>::GetInstance(); item->Print(); });
  std::jthread t2([] { std::this_thread::sleep_for(std::chrono::seconds(1)); auto item = SingletonTemplate<System>::GetInstance(); item->Print(); });
  std::jthread t3([] { std::this_thread::sleep_for(std::chrono::seconds(1)); auto item = SingletonTemplate<System>::GetInstance(); item->Print(); });
  std::jthread t4([] { std::this_thread::sleep_for(std::chrono::seconds(1)); auto item = SingletonTemplate<System>::GetInstance(); item->Print(); });

  return 0;
}