#include <mutex>
#include <memory>
#include <thread>
#include <queue>
#include <iostream>
#include <format>
#include <shared_mutex>
#include <condition_variable>

template <typename T>
class TQueue {
 public:
  TQueue() = default;
  TQueue(const TQueue &rhs) {
    std::lock_guard<std::mutex> lock(rhs.mtx_);
    queue_ = rhs.queue_;
  }

  void Push(const T &data) {
    std::lock_guard<std::mutex> lock(mtx_);
    queue_.push(data);
    cv_.notify_one();
  }

  std::shared_ptr<T> WaitAndPop() {  // 会阻塞等待
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, [this](){ return !queue_.empty(); });
    auto ptr = std::make_shared<T>(queue_.front());
    queue_.pop();
    return ptr;
  }

  std::shared_ptr<T> TryPop() {  // 非阻塞等待
    std::unique_lock<std::mutex> lock(mtx_);
    if (queue_.empty()) return nullptr;
    auto ptr = std::make_shared<T>(queue_.front());
    queue_.pop();
    return ptr;
  }

  bool Empty() {
    std::unique_lock<std::mutex> lock(mtx_);
    return queue_.empty();
  }

 private:
  mutable std::mutex mtx_;
  std::condition_variable cv_;
  std::queue<T> queue_;
};

int main() {
  std::mutex print_mtx;
  TQueue<int> queue;

  bool end = false;          // 结束标志
  std::shared_mutex end_mtx; // 结束互斥量

  std::jthread producer([&](){
    for (int i = 0; i < 30; ++i) {
      queue.Push(i);
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::lock_guard lock(end_mtx);
    end = true;
  });

  std::jthread consumer1([&](){
    while (true) {
      {
        std::shared_lock<std::shared_mutex> lock(end_mtx);
        if (end && queue.Empty()) break;
      }
      auto ptr = queue.TryPop();
      if (ptr != nullptr) {
        std::lock_guard<std::mutex> lock(print_mtx);
        std::cout << std::format("consumer 1: consumed {}\n", *ptr);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  });
  std::jthread consumer2([&](){
    while (true) {
      {
        std::shared_lock<std::shared_mutex> lock(end_mtx);
        if (end && queue.Empty()) break;
      }
      auto ptr = queue.TryPop();
      if (ptr != nullptr) {
        std::lock_guard<std::mutex> lock(print_mtx);
        std::cout << std::format("consumer 2: consumed {}\n", *ptr);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  });

  return 0;
}