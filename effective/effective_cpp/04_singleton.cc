#include "04_singleton.h"

Singleton::Singleton() = default;
Singleton &Singleton::Get() {
  // 懒汉模式: 第一次调用时初始化
  // 线程安全: C++11 保证 多个控制流如果在变量初始化过程中存在竞争, 则必须等待初始化完成
  //         本质采用 Double-Checked Locking
  // 析构安全: 不涉及到内存泄露
  static Singleton singleton;
  return singleton;
}
void Singleton::print() {
  std::cout << "singleton !\n";
}

SingletonDoubleCheck *SingletonDoubleCheck::singleton_double_check_ = nullptr;
std::mutex SingletonDoubleCheck::mutex_;
SingletonDoubleCheck::SingletonDoubleCheck() = default;
SingletonDoubleCheck &SingletonDoubleCheck::Get() {
  // 懒汉模式: 第一次调用时初始化
  // 线程安全: 采用 Double-Checked Locking 保证 (C++11 后保证 new 过程是线程安全的)
  // 析构安全: 注册静态析构函数, 程序结束时，将自动调用该静态析构函数销毁单例对象, 只析构一次
  if (!singleton_double_check_) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!singleton_double_check_) {
      singleton_double_check_ = new SingletonDoubleCheck;
      std::atexit([]{ delete singleton_double_check_; });
    }
  }
  return (*singleton_double_check_);
}
void SingletonDoubleCheck::print() {
  std::cout << "singleton double check!\n";
}

int main() {
  Singleton &singleton = Singleton::Get();
  singleton.print();

  SingletonDoubleCheck &singleton_double_check = SingletonDoubleCheck::Get();
  singleton_double_check.print();
  return 0;
}