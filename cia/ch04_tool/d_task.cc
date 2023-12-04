#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <format>
#include <shared_mutex>
#include <condition_variable>
#include <future>

std::string process(const std::string &str) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return std::format("async str: {}", str);
}

int main() {
  // task 与 thread 分离, 方便引入线程池
  std::packaged_task<decltype(process)> task(process);
  auto future = task.get_future();
  std::thread t(std::move(task), "hello task");
  t.detach();  // 分离

  // ....

  std::cout << std::format("final result is {}\n", future.get());  // 阻塞等待
  return 0;
}
