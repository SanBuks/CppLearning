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
  while (true) {
    future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
    }
  }

  t.join();
  return 0;
}
