#ifndef EFFECTIVE_CPP_04_SINGLTON_H_
#define EFFECTIVE_CPP_04_SINGLTON_H_

#include <mutex>
#include <iostream>

// C++11 后采用 static 对象
class Singleton {
 public:
  static Singleton &Get();                          // C++11 后简便实现方式
  Singleton(const Singleton &) = delete;            // 防止不必要的拷贝
  Singleton &operator=(const Singleton &) = delete; // 防止不必要的拷贝
  void print();                                     // 打印相关信息
 private:
  Singleton();                                      // 防止对象被构造
};

// Double-Checked Locking 方法
class SingletonDoubleCheck {
 public:
  static SingletonDoubleCheck &Get();
  SingletonDoubleCheck(const SingletonDoubleCheck &) = delete;
  SingletonDoubleCheck &operator=(const SingletonDoubleCheck &) = delete;
  void print();
 private:
  SingletonDoubleCheck();

  static SingletonDoubleCheck *singleton_double_check_;
  static std::mutex mutex_;
};

#endif