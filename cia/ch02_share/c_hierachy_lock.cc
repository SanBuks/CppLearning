#include <mutex>
#include <stdexcept>
#include <thread>

class HierarchyMutex {
 public:
  using ull = unsigned long long;
 public:
  explicit HierarchyMutex(ull ch_value) : mutex_(), ch_value_(ch_value), ph_value_(0) {}

  HierarchyMutex(const HierarchyMutex &rhs) = delete;
  HierarchyMutex &operator=(const HierarchyMutex &rhs) = delete;

  void lock() {
    check_set_hierarchy_violation();
    mutex_.lock();
    update_hierarchy_violation();
  }

  void unlock() {
    if (thread_value_ != ch_value_)  // 不是原来的锁
      throw std::logic_error("hierarchy value of unlock violate!");
    mutex_.unlock();
    thread_value_ = ph_value_;
  }

 private:
  void check_set_hierarchy_violation() const {
    if (thread_value_ <= ch_value_)
      throw std::logic_error("hierarchy value of lock violate!");
  }

  void update_hierarchy_violation() {
    ph_value_ = thread_value_;
    thread_value_ = ch_value_;
  }

  mutable std::mutex mutex_;              // 锁
  ull ch_value_;                          // 加锁层级
  ull ph_value_;                          // 前层级
  static thread_local ull thread_value_;  // 记录层级 层级值是严格递减
};

thread_local HierarchyMutex::ull HierarchyMutex::thread_value_ = std::numeric_limits<HierarchyMutex::ull>::max();

int main() {

  HierarchyMutex mutex1(1000);
  HierarchyMutex mutex2(500);

  std::jthread t1([&mutex1, &mutex2]() {
    mutex1.lock();         // max(p) 1000(c)
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mutex2.lock();         // max 1000(p) 500(c)
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mutex2.unlock();       // max(p) 1000(c)
    mutex1.unlock();       // max(c)
  });

  std::jthread t2([&mutex1, &mutex2]() {
    mutex2.lock();         // max(p) 500(c)
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mutex1.lock();         // max 500(p) 1000(c) violation ! 如果不是层级锁, 不按照顺序加索可能导致出现死锁
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mutex1.unlock();
    mutex2.unlock();
  });

  return 0;
}
