#include <memory>
#include <thread>
#include <iostream>
#include <format>
#include <shared_mutex>
#include <future>

// 简要区别:
// async -> future: thread 与 task 耦合, 简洁方便
// packaged_task -> future: thread 与 task 解耦
// promise -> future: 在执行过程中返回值

// 此处 promise 形参为副本形式 或者 为智能指针
void process(std::string &str, std::promise<std::string> promise) {
  std::cout << "default str: " << str << "\n";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  if (str == "uncall") {
    promise.set_value("only one step finished");  // 只能 set 一次, set 多次会出错 std::future_error: Broken promise
  } else {
    try {
      throw std::runtime_error("not uncall error");
    } catch (...) {
      promise.set_exception(std::current_exception());  // 设置异常
    }
  }
  str = "result returned";
}

int main() {
  std::promise<std::string> promise;
  std::future<std::string> future = promise.get_future();
  std::string restr = "uncall";
//  std::string restr = "call";
  std::thread t(process, std::ref(restr), std::move(promise));

  std::string result;
  int count = 0;
  while (true) {
    if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
      try {
        auto str = future.get();  // 对可能抛出异常的 get 必须用 try-catch 捕获
                                  // 此时必须保证 promise 对象没有释放, 可以使用智能指针维持生命周期
        std::cout << str << "\n";
        std::cout << restr << "\n";
      } catch (const std::exception &ex) {
        std::cout << ex.what() << "\n";
      }
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << std::format("poll time: {}\n", ++count);
  }
  t.join();
  return 0;
}
