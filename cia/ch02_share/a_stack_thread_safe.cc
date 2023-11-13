#include <stack>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <iostream>
#include <memory>

struct stack_empty : std::exception {
  const char * what() const throw();
};

template <typename T>
class TStack {
 public:
  TStack() : stack_() {}
  TStack(const TStack & rhs) {
    std::lock_guard guard(mutex_);
    stack_ = rhs.stack_;
  }
  TStack &operator=(const TStack &rhs) = delete;

  void push(T item) {
    std::lock_guard guard(mutex_);
    stack_.push(std::move(item));
  }


  // 返回 T 后会存在内存分配异常, 导致 pop 出的 elem 丢失
  // 解决问题方法: 提前配置好内存防止安全异常
  T pop_problem() {
    std::lock_guard guard(mutex_);
    if (stack_.empty())
      throw std::logic_error("empty stack!");
    auto elem = stack_.top();
    stack_.pop();
    return elem;
  }

  // 方法一: 返回智能指针
  std::shared_ptr<T> pop() {
    std::lock_guard guard(mutex_);
    if (stack_.empty())
      throw std::logic_error("empty stack!");
    auto ptr = std::make_shared<T>(stack_.top());
    stack_.pop();
    return ptr;
  }

  // 方法二: 通过引用返回
  void pop(T &item) {
    std::lock_guard guard(mutex_);
    if (stack_.empty())
      throw std::logic_error("empty stack!");
    item = stack_.top();
    stack_.pop();
  }

  // 结果不可信, empty 状态随时会被改变, 延迟调用会出现问题
  bool empty() const {
    std::lock_guard guard(mutex_);
    return stack_.empty();
  }

  // 结果不可信, size 状态随时会被改变, 延迟调用会出现问题
  size_t size() const {
    std::lock_guard guard(mutex_);
    return stack_.size();
  }

 private:
  std::stack<T> stack_;
  mutable std::mutex mutex_;
};

int main() {
  TStack<int> s;

  std::thread t1([&s](){
    for (int i = 0; i < 100; ++i) {
      s.push(i);
    }
  });
  std::thread t2([&s](){
    for (int i = 0; i < 100; ++i) {
      s.push(i);
    }
  });

  t1.join();
  t2.join();

  std::cout << s.size() << "\n";
  return 0;
}