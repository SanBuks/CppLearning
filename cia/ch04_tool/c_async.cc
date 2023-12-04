#include <ctime>
#include <memory>
#include <format>
#include <thread>
#include <future>
#include <iostream>
#include <shared_mutex>

std::string get_time() {
  auto current_time = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(current_time);
  auto time_info = std::localtime(&time_t);

  auto millis = current_time.time_since_epoch().count() / 1000000 % 1000;
  char time_str[80];
  std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
  sprintf(time_str, "%s:%03d", time_str, static_cast<int>(millis));

  return {time_str};
}

std::string process(const std::string &str) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return std::format("async str: {}", str);
}

void get_test() {
  auto future = std::async(std::launch::deferred, process, "hello"); // 第一次获取结果时才执行
  std::cout << get_time() << "\n";
  std::cout << "Do other thing\n";
  std::cout << future.get() << "\n";
}

void wait_for_test() {
  auto future = std::async(std::launch::async, process, "hello");  // 立马开辟线程执行
  int max_time = 5;

  int count = 0;
  while (true) {
    if (++count > max_time) {
      std::cout << std::format("reach max time, quit\n");
      return;
    }
    // 轮询结果, 做其他事
    if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
      std::cout << std::format("final result is {}\n", future.get());
      return;
    }
    std::cout << std::format("poll time: {}", count);
  }
}

int main() {
  std::cout << get_time() << "\n";
//  get_test();
//  wait_for_test();
  return 0;
}