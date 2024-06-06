#include "a_sync_basic.h"

#include <string>
#include <iostream>

#include "spdlog/spdlog.h"
#include "asio.hpp"

namespace net {

using namespace asio;

int BasicLearning::CreateEndPoint() {
  // system::error_code 形式获取错误信息
  error_code err;

  // 解析 ip 地址
  auto ip_address = ip::address::from_string("127.0.0.1", err);
  // 解析 ip 地址 (任意) 一般用于服务器
  //auto ip_address = ip::address_v4::any();
  if (err) {
    spdlog::error("error value : {}, err message : {}", err.value(), err.message());
    return err.value();
  }

  // 创建 端点
  ip::tcp::endpoint ep(ip_address, 2333);

  // ...

  return 0;
}

int BasicLearning::CreateSocket() {
  // 创建 协议对象 TCP IPv4
  ip::tcp protocol = ip::tcp::v4();

  // 创建 IO 上下文
  io_context ioc;
  // 创建 socket 对象
  ip::tcp::socket sock(ioc);

  // 打开 socket
  error_code err;
  err = sock.open(protocol, err);
  if (err) {
    spdlog::info("error value : {}, err message : {}", err.value(), err.message());
    return err.value();
  }
  return 0;
}

int BasicLearning::CreateAcceptor() {
  ip::tcp::endpoint ep(ip::address_v4::any(), 3333);
  ip::tcp protocol = ip::tcp::v4();
  io_context ioc;
  // 创建 acceptor 对象
  ip::tcp::acceptor acceptor(ioc);
  //  创建 acceptor 并打开
//ip::tcp::acceptor acceptor(ioc, ep.protocol());
  // 可以直接通过 ep 创建 acceptor 并绑定
//ip::tcp::acceptor acceptor(ioc, ep);

  error_code err;
  // 打开 acceptor
  err = acceptor.open(protocol, err);
  if (err) {
    spdlog::error("error value : {}, err message : {}", err.value(), err.message());
    return err.value();
  }

  // 绑定 acceptor
  err = acceptor.bind(ep, err);
  if (err) {
    spdlog::error("error value : {}, err message : {}", err.value(), err.message());
    return err.value();
  }
  // ...

  return 0;
}

int BasicLearning::ConnectEndPoint() {
  std::string raw_ip = "192.168.1.124";
  unsigned short port = 3333;
  try {
    ip::tcp::endpoint ep(ip::address::from_string(raw_ip), port);
    io_context ioc;
    ip::tcp::socket sock(ioc, ep.protocol());
    // 连接 socket
    sock.connect(ep);

    // ...

    return 0;
  } catch (const system_error &err) {
    std::cout << std::format("error value : {}, err message : {}", err.code().value(), err.code().message());
    return err.code().value();
  }
}

int BasicLearning::DnsConnectEndPoint() {
  std::string host_name = "www.google.com";
  std::string port_num = "3333";
  io_context ioc;

  // 解析请求
  ip::tcp::resolver::query resolver_query(host_name, port_num, ip::tcp::resolver::numeric_service);
  // 解析器
  ip::tcp::resolver resolver(ioc);
  try {
    // 解析域名
    auto it = resolver.resolve(resolver_query);
    // 连接 socket
    ip::tcp::socket sock(ioc);
    connect(sock, it);

    // ...

  } catch (const system_error &err) {
    std::cout << std::format("error value : {}, err message : {}", err.code().value(), err.code().message());
    return err.code().value();
  }
  return 0;
}

int BasicLearning::AcceptConnection() {
  // 监听的连接个数
  const int kBlockSize = 30;
  io_context ioc;
  try {
    // 创建并绑定
    ip::tcp::acceptor acceptor(ioc, ip::tcp::endpoint(ip::address_v4::any(), 3333));
    // 监听
    acceptor.listen(kBlockSize);
    // 新连接交给 sock 处理
    ip::tcp::socket sock(ioc);
    acceptor.accept(sock);

    // ...

  } catch (const system_error &err) {
    std::cout << std::format("error value : {}, err message : {}", err.code().value(), err.code().message());
    return err.code().value();
  }
  return 0;
}

}

int main() {

  return 0;
}

