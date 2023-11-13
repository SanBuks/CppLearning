#include <iostream>
#include <thread>
#include <vector>

class jthread {
 public:
  jthread() noexcept = default;
  template<typename Callable, typename ...Args>
  explicit jthread(Callable &&callable, Args &&...args)
      : t_(std::forward<Callable>(callable), std::forward<Args>(args)...) {}

  jthread(const jthread &rhs) = delete;
  jthread &operator=(const jthread &rhs) = delete;

  jthread(jthread &&rhs) noexcept : t_(std::move(rhs.t_)) {}
  jthread &operator=(jthread &&rhs) noexcept {
    if (joinable()) join();
    t_ = std::move(rhs.t_);
    return *this;
  };

  explicit jthread(std::thread &&thread) : t_(std::move(thread)) {}
  jthread &operator=(std::thread &&rhs) noexcept {
    if (joinable()) join();
    t_ = std::move(rhs);
    return *this;
  };

  ~jthread() { if (t_.joinable()) t_.join(); }

  [[nodiscard]]
  bool joinable() const noexcept { return t_.joinable(); }
  void join() { t_.join(); }
  void detach() { t_.detach(); }

 private:
  std::thread t_;
};

int main() {
  int num = 0;
  auto lambda = [](int &item) {
    // 不加锁会发生乱序
    std::cout << ++item << "\n";
  };

  std::vector<jthread> vec;
  for (int i = 0; i < 10; ++i) {
    vec.emplace_back(lambda, std::ref(num));
  }

  return 0;
}
