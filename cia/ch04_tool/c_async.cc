#include <ctime>
#include <memory>
#include <format>
#include <thread>
#include <future>
#include <iostream>
#include <shared_mutex>

#include "../tool.h"

std::string process(const std::string &str) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return std::format("async str: {}", str);
}

void defer_test() {
  // 第一次获取结果时才执行
  auto future = std::async(std::launch::deferred, process, "hello");
  print_time();
  std::cout << "Do other thing ...\n";
  std::this_thread::sleep_for(std::chrono::seconds(2));
  print_time();
  std::cout << future.get() << "\n";
  print_time();
}

void dtor_block_test() {
  print_time();
  {
    // 析构强制阻塞直到完成
    auto future = std::async(std::launch::async, process, "hello");
  }
  print_time();
}

void wait_for_test() {
  auto future = std::async(std::launch::async, process, "hello");  // 立马开辟线程执行
  int count = 0;
  print_time();
  while (true) {
    // 轮询结果, 做其他事
    if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
      std::cout << std::format("final result is {}\n", future.get());
      print_time();
      return;
    }
    std::cout << std::format("poll time: {}\n", ++count);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int main() {
//  defer_test();
//  dtor_block_test();
  wait_for_test();
  return 0;
}