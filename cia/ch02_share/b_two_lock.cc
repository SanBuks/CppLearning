#include <stack>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <vector>
#include <format>

// no thread safe
class BigData {
 public:
  BigData() : vec_() {}
  BigData(const std::vector<int> &vec) : vec_(vec) {}
  BigData(const BigData &rhs) : vec_(rhs.vec_) {}
  BigData &operator=(const BigData &rhs) {
    if (&rhs == this) return *this;
    vec_ = rhs.vec_;
    return *this;
  }
  BigData(BigData &&rhs)  noexcept : vec_(std::move(rhs.vec_)) {}
  BigData &operator=(BigData &&rhs) noexcept {
    if (&rhs == this) return *this;
    vec_ = std::move(rhs.vec_);
    return *this;
  }

  friend void swap(BigData &lhs, BigData & rhs) {
    BigData temp(std::move(lhs));
    lhs = std::move(rhs);
    rhs = std::move(temp);
  }

  friend std::ostream& operator<<(std::ostream &os, const BigData &data) {
    for (const auto &item : data.vec_) {
      os << item << " ";
    }
    return os;
  }

 private:
  std::vector<int> vec_;
};

void swap(BigData &lhs, BigData & rhs);
std::ostream& operator<<(std::ostream &os, const BigData &data);

class Manager {
 public:
  explicit Manager(const std::vector<int> &data) : data_(data) {}

  void print() {
    std::cout << data_;
  }

  friend void danger_swap(Manager &lhs, Manager &rhs);
  friend void safe_swap(Manager &lhs, Manager &rhs);
 private:
  BigData data_;
  mutable std::mutex mutex_;
};

void danger_swap(Manager &lhs, Manager &rhs) {
  if (&lhs == &rhs) return;
  std::cout << "thread id:" << std::this_thread::get_id() << "\n";
  std::lock_guard lhs_m(lhs.mutex_);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::lock_guard rhs_m(rhs.mutex_);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  swap(lhs.data_, rhs.data_);
}

void safe_swap(Manager &lhs, Manager &rhs) {
  if (&lhs == &rhs) return;
  std::cout << "thread id:" << std::this_thread::get_id() << "\n";

// scoped lock 同时加锁
  std::scoped_lock lock(lhs.mutex_, rhs.mutex_);

// 同时加锁, 采用领养锁
//  std::lock(lhs.mutex_, rhs.mutex_);    // 必须加锁后领养, 否则 lock_guard 析构解锁时会报错
//  std::lock_guard lg1(lhs.mutex_, std::adopt_lock);
//  std::this_thread::sleep_for(std::chrono::seconds(1));
//  std::lock_guard lg2(rhs.mutex_, std::adopt_lock);
//  std::this_thread::sleep_for(std::chrono::seconds(1));

  swap(lhs.data_, rhs.data_);
}

void test_danger_swap() {
  Manager m1(std::vector<int>(100, 20));
  Manager m2(std::vector<int>(100, 22));
  std::thread t1(danger_swap, std::ref(m1), std::ref(m2));
  std::thread t2(danger_swap, std::ref(m2), std::ref(m1));
  t1.join();
  t2.join();
//  m1.print();
//  m2.print();
}

void test_safe_swap() {
  Manager m1(std::vector<int>(100, 20));
  Manager m2(std::vector<int>(100, 22));
  std::thread t1(safe_swap, std::ref(m1), std::ref(m2));
  std::thread t2(safe_swap, std::ref(m2), std::ref(m1));
  t1.join();
  t2.join();
  m1.print();
  std::cout << "\n";
  m2.print();
}

int main() {
//  test_danger_swap();
  test_safe_swap();
  return 0;
}