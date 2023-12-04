#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <format>
#include <shared_mutex>
#include <condition_variable>
#include <future>

#include "../tool.h"

std::string process(const std::string &str) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return std::format("async str: {}", str);
}

void packaged_task_test() {
  // task 就是 function-like 的封装, 方便获取 future
  std::packaged_task<decltype(process)> task(process);
  auto future = task.get_future();
  // 主动调用 task
  task("hello");
  // 没有阻塞
  print_time();
  std::cout << std::format("final result is {}\n", future.get());
  print_time();
}

void packaged_task_thread() {
  // task 与 thread 分离, 方便引入线程池
  std::packaged_task<decltype(process)> task(process);
  auto future = task.get_future();
  std::jthread jt(std::move(task), "hello task");

  // ....

  // 可能阻塞等待
  std::cout << std::format("final result is {}\n", future.get());
}

int main() {
//  packaged_task_test();
  packaged_task_thread();
  return 0;
}
