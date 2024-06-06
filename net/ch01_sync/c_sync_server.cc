#include <string>
#include <set>
#include <format>
#include <iostream>
#include <memory>
#include <thread>

#include "asio.hpp"
#include "spdlog/spdlog.h"

// 特点
// 1. read_some 存在阻塞
// 2. 一个新连接创建一个新线程
// 3. 应答非全双工
// 4. 适合简单需求

using namespace asio;

using sock_ptr = std::unique_ptr<ip::tcp::socket>;   // socket 对象指针
std::set<std::shared_ptr<std::jthread>> thread_set;  // 处理会话的线程池
const int kMaxLength = 1024;

void Session(sock_ptr sock) {
  try {
    while (true) {
      char data[kMaxLength] = {};
      error_code error;
      // auto num_rec = sock->receive(buffer(data, kMaxLength));  // 阻塞到 读完 kMaxLength 为止, 不推荐
      auto size = sock->read_some(buffer(data, kMaxLength), error);

      if (error == error::eof) {   // 断开连接异常
        spdlog::info("connection {} closed!", sock->remote_endpoint().address().to_string());
        break;
      } else if (error) {          // 其他异常
        throw system_error(error);
      }
      spdlog::info("receive from {} ", sock->remote_endpoint().address().to_string());
      spdlog::info("receive message: {}", std::string(data, size));
      sock->send(buffer(data, size));
    }
  } catch (const system_error &err) {
    spdlog::error("error code: {}, error msg: {}", err.code().value(), err.what());
  }
}

[[noreturn]]
void Server(std::unique_ptr<io_context> pioc, unsigned int port) {
  ip::tcp::endpoint ep(ip::address_v4::any(), port);
  // 创建 acceptor, open, bind
  ip::tcp::acceptor acc(*pioc, ep);
  acc.listen(30);
  while (true) {
    // 创建 socket 并监听
    auto sock = std::make_unique<ip::tcp::socket>(*pioc);
    acc.accept(*sock);
    // 创建线程处理会话
    auto th = std::make_shared<std::jthread>(Session, std::move(sock));
    thread_set.insert(th);
  }
}

int main() {
  auto pioc = std::make_unique<io_context>();
  unsigned int port = 2333;

  try {
    Server(std::move(pioc), port);
  } catch (const system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}