#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <format>
#include <iostream>

class TData {
 public:
  TData() = default;

  std::string Get(const std::string &key) const {
    std::unique_lock<std::recursive_mutex> lock(rmutex_);
    return Query(key) ? mp_.at(key) : "NONE";
  }

  bool Query(const std::string &key) const {
    std::unique_lock<std::recursive_mutex> lock(rmutex_);
    return mp_.contains(key);
  }

  // 调用子函数, 对递归锁重复加锁
  void Set(const std::pair<std::string, std::string> &value) {
    std::unique_lock<std::recursive_mutex> lock(rmutex_);
    if (Query(value.first))
      mp_[value.first] = value.second;
    mp_.emplace(value);
  }

  // 组合为原子操作, 避免使用递归锁
  void QueryThenSet(const std::pair<std::string, std::string> &value) {
    std::unique_lock<std::recursive_mutex> lock(rmutex_);
    if (mp_.contains(value.first))
      mp_[value.first] = value.second;
    mp_.emplace(value);
  }

 private:
  std::map<std::string, std::string> mp_;
  mutable std::recursive_mutex rmutex_;
};

int main() {
  TData data;
  data.Set({"www", "xyz"});
  std::cout << std::format("{}", data.Get("www"));
  return 0;
}