#include <memory>
#include <thread>
#include <iostream>
#include <format>
#include <shared_mutex>
#include <future>

#include "../tool.h"

std::mutex omtx;

void process(std::promise<std::string> promise) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  if (random_bool()) {
    promise.set_value("finished");
  } else {
    try {
      throw std::runtime_error("exception");
    } catch (...) {
      promise.set_exception(std::current_exception());
    }
  }
}

void print(std::shared_future<std::string> &&future) {
  try {
    std::lock_guard<std::mutex> lock(omtx);
    std::cout << std::format("thread id: {}, result: {}\n", thread_id(), future.get());
  } catch (const std::exception &ex) {
    std::lock_guard<std::mutex> lock(omtx);
    std::cout << std::format("thread id: {}, result: {}\n", thread_id(), ex.what());
  }
}

int main() {
  std::promise<std::string> promise;
  std::shared_future<std::string> future = promise.get_future();
  std::jthread t(process, std::move(promise));
  std::jthread consumer1(print, future);  // 此处 future 不可移动
  std::jthread consumer2(print, future);  // 此处 future 不可移动
  return 0;
}
