#include <thread>
#include <mutex>
#include <format>
#include <iostream>
#include <condition_variable>

int main() {
  system("chcp 65001");

  static std::mutex mtx;
  std::condition_variable ca;
  std::condition_variable cb;
  int num = 2;
  int all = 3;


  std::jthread t1([&]() {
    int times = all;
    while(times--) {
      std::unique_lock<std::mutex> lock(mtx);

      ca.wait(lock, [&](){  // 条件变量不满足则 解锁lock, 后阻塞, 直到满足后自动加锁执行
        return num == 2;
      });

      std::cout << std::format("t1 print {}\n\n", num);
      --num;

      lock.unlock();  // unlock 再换新其他条件变量
      cb.notify_one();
    }
  });

  std::jthread t2([&]() {
    int times = all;
    while (times--) {
      std::unique_lock<std::mutex> lock(mtx);

      while (num != 1) {  // while 防止虚假唤醒
        cb.wait(lock);
      }

      std::cout << std::format("t2 print {}\n\n", num);
      ++num;
      lock.unlock();
      ca.notify_one();
    }
  });

  return 0;
}