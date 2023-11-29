#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <format>
#include <iostream>
#include <shared_mutex>

// 共享锁 -> 共享互斥量, 读写锁
class DNSServer {
 public:
  DNSServer() = default;
  std::string Get(const std::string &key) const {
    std::shared_lock<std::shared_mutex> lock(smutex_);
    return mp_.contains(key) ? mp_.at(key) : "NONE";
  }

  void Set(const std::pair<std::string, std::string> &value) {
    std::unique_lock<std::shared_mutex> lock(smutex_);  // 获取共享锁
//    smutex_.lock_shared();
//    smutex_.unlock_shared();
//    if (stmutex_.try_lock_shared_for(std::chrono::seconds(1))) // for time
//    if (stmutex_.try_lock_shared_until(timeout)                // until timeout (std::chrono::steady_clock::now() + std::chrono::seconds(3))
    if (!mp_.contains(value.first)) mp_.emplace(value);
    mp_[value.first] = value.second;
  }

 private:
  std::map<std::string, std::string> mp_;
  mutable std::shared_mutex smutex_;
  mutable std::shared_timed_mutex stmutex_;
};

int main() {
  DNSServer server;
  server.Set({"www.address.com", "123.123.123.123"});
  std::cout << std::format("{}", server.Get("www.address.com"));
  return 0;
}