#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <format>
#include <shared_mutex>
#include <condition_variable>
#include <future>

std::string process(const std::string &str, std::promise<std::string> promise) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  promise.set_value("one step finished");
  std::this_thread::sleep_for(std::chrono::seconds(5));
  promise.set_value("two step finished");
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return std::format("async str: {}", str);
}


int main() {
  std::promise<std::string> promise;
  std::future<std::string> future = promise.get_future();
  std::thread t(process, "hello promise", std::move(promise));

  std::string result;
  int count = 0;
  while (true) {
    if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
      auto str = future.get();
      std::cout << str << "\n";
      if (str.starts_with("async"))
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << std::format("poll time: {}\n", ++count);
  }
  t.join();
  return 0;
}
