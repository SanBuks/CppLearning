#include <string>
#include <set>
#include <format>
#include <iostream>
#include <memory>
#include <thread>

#include <boost/asio.hpp>

// 特点
// 1. read_some 存在阻塞
// 2. 一个新连接创建一个新线程
// 3. 应答非全双工
// 4. 适合简单需求

using namespace boost;
using namespace boost::asio;

using sock_ptr = std::shared_ptr<ip::tcp::socket>;   // socket 对象指针
std::set<std::shared_ptr<std::jthread>> thread_set;  // 处理会话的线程池
const int kMaxLength = 1024;

void Session(sock_ptr sock) {
  try {
    while (true) {
      char data[kMaxLength] = {};
      system::error_code error;
      // auto num_rec = sock->receive(buffer(data, kMaxLength));  // 阻塞到 读完 kMaxLength 为止, 不推荐
      auto size = sock->read_some(buffer(data, kMaxLength), error);

      if (error == error::eof) {   // 断开连接异常
        std::cout << std::format("connection {} closed!", sock->remote_endpoint().address().to_string()) << std::endl;
        break;
      } else if (error.failed()) { // 其他异常
        throw system::system_error(error);
      }
      std::cout << std::format("receive from {} ", sock->remote_endpoint().address().to_string()) << std::endl;
      std::cout << std::format("receive message: {}", std::string(data, size)) << std::endl;

      sock->send(buffer(data, size));
    }
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
  }
}

[[noreturn]]
void Server(io_context &ioc, unsigned int port) {
  // 创建 acceptor, open, bind
  ip::tcp::acceptor acc(ioc, ip::tcp::endpoint(ip::address_v4::any(), port));
  while (true) {
    // 创建 socket 并监听
    auto sock = std::make_shared<ip::tcp::socket>(ioc);
    acc.accept(*sock);
    // 创建线程处理会话
    auto th = std::make_shared<std::jthread>(Session, sock);
    thread_set.insert(th);
  }
}

int main() {
  io_context ioc;
  unsigned int port = 2333;

  try {
    Server(ioc, port);
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}