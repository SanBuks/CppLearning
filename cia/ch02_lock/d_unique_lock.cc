#include <mutex>
#include <iostream>
#include <format>

// unique_lock 支持对 mutex 管理

int a = 0;
int b = 1;
std::mutex m1;
std::mutex m2;

// 延迟加锁, 判断锁的状况, 可以手动解锁
void TestDeferLock() {
  std::unique_lock<std::mutex> u(m1, std::defer_lock);
  std::cout << std::format("是否用有锁: {}\n", u.owns_lock() ? "有锁" : "无锁");
  u.lock();
  std::cout << std::format("是否用有锁: {}\n", u.owns_lock() ? "有锁" : "无锁");
  u.unlock();
  std::cout << std::format("是否用有锁: {}\n", u.owns_lock() ? "有锁" : "无锁");
}

void TestAdoptLock() {
  m1.lock();
  std::unique_lock<std::mutex> u(m1, std::adopt_lock);  // 领养有锁对象
  std::cout << std::format("是否用有锁: {}\n", u.owns_lock() ? "有锁" : "无锁");
  // unique_lock 已接管了 mutex, 不能直接对 mutex 进行操作
  // m1.unlock();  // 错误
}

int main() {
  system("chcp 65001");

//  TestDeferLock();
  TestAdoptLock();
  return 0;
}