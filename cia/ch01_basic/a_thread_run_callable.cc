#include <format>
#include <iostream>
#include <thread>

/**
 * 1. 三种函数对象调用方式
 * 2. 子线程需要汇合或分离
 * 3. 注意仿函数的歧义性
 */

class Foo {
 public:
  void func_callable(const std::string &str) {
    std::cout << std::format("{} This is {}.\n", str_, str);
  }
 private:
  std::string str_ = "Hello, Class Member Func!";
};

class Boo {
 public:
  explicit Boo(int &i) : i(i) {}
  void operator()(const std::string &str) const {
    for (int j = 0; j < 3; ++j)
      std::cout << i << " ";
    std::cout << str << "\n";
  }
 private:
  int &i;
};

int main() {
  const std::string str = "Mike";
  int i = 3;

  Foo foo;
  auto lambda = [](const std::string &str) { std::cout << str; };

  std::thread func(&Foo::func_callable, &foo, str);  // 调用 成员函数需要额外对象地址
  std::thread func_obj(Boo{i}, str);                 // 调用 仿函数, 统一初始化形式防止歧义误认为函数指针
  std::thread func_lambda(lambda, str);              // 调用 lambda

  func.detach();       // 令线程从主线程中分离等待子线程(主进程结束仍然会回收子线程)
  func_obj.join();     // 令主线程等待子线程
  func_lambda.join();  // 不 join 或 detach, 主线程结束, thread 析构会调用 terminate 中止

  std::this_thread::sleep_for(std::chrono::seconds(1));  // 防止进程过快结束
}