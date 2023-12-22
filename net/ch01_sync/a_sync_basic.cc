#include "a_sync_basic.h"

#include <string>
#include <format>
#include <iostream>
#include <memory>

namespace net {

int BasicLearning::CreateClientEndPoint() {
  // system::error_code 形式获取错误信息
  system::error_code err;
  // 解析 ip 地址
  auto ip_address = ip::address::from_string("127.0.0.1", err);
  if (err.failed()) {
    std::cout << std::format("error value : {}, err message : {}", err.value(), err.message());
    return err.value();
  }
  // 创建 端点
  ip::tcp::endpoint ep(ip_address, 2333);

  // ...

  return 0;
}

int BasicLearning::CreateServerEndPoint() {
  // 使用任意 ipv4 地址
  ip::tcp::endpoint(ip::address_v4::any(), 3333);

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

  system::error_code err;
  // 打开 socket
  sock.open(protocol, err);
  if (err.failed()) {
    std::cout << std::format("error value : {}, err message : {}", err.value(), err.message());
    return err.value();
  }
  return 0;
}

int BasicLearning::CreateAcceptor() {
  io_context ioc;
  // 创建 acceptor 对象
  ip::tcp::acceptor acceptor(ioc);

  ip::tcp protocol = ip::tcp::v4();
  system::error_code err;
  // 打开 acceptor
  acceptor.open(protocol, err);
  if (err.failed()) {
    std::cout << std::format("error value : {}, err message : {}", err.value(), err.message());
    return err.value();
  }

  // ...

  return 0;
}

int BasicLearning::BindAcceptor() {
  ip::tcp::endpoint ep(ip::address_v4::any(), 3333);

  io_context ioc;
  ip::tcp::acceptor acceptor(ioc, ep.protocol());


  system::error_code err;
  acceptor.bind(ep, err);
  if (err.failed()) {
    std::cout << std::format("error value : {}, err message : {}", err.value(), err.message());
    return err.value();
  }

  // ...

  return 0;
}

int BasicLearning::CreateBindAcceptor() {
  io_context ioc;
  ip::tcp::acceptor acceptor(ioc, ip::tcp::endpoint(ip::address_v4::any(), 3333));

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
  } catch (const system::system_error &err) {
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

  } catch (const system::system_error &err) {
    std::cout << std::format("error value : {}, err message : {}", err.code().value(), err.code().message());
    return err.code().value();
  }
  return 0;
}

int BasicLearning::AcceptConnection() {
  // 监听的连接个数
  const int kBlockSize = 30;
  ip::tcp::endpoint ep(ip::address_v4::any(), 3333);
  io_context ioc;
  ip::tcp::acceptor acceptor(ioc, ep.protocol());

  try {
    // 绑定
    acceptor.bind(ep);
    // 监听
    acceptor.listen(kBlockSize);
    // 新连接交给 sock 处理
    ip::tcp::socket sock(ioc);
    acceptor.accept(sock);

    // ...

  } catch (const system::system_error &err) {
    std::cout << std::format("error value : {}, err message : {}", err.code().value(), err.code().message());
    return err.code().value();
  }
  return 0;
}

int BasicLearning::CreateConstBufferByVector() {
  std::string str = "hello world";
  const_buffer const_buf(str.c_str(), str.size());
  std::vector<const_buffer> const_buffer_seq{const_buf};

  // ...

  return 0;
}

int BasicLearning::CreateConstBufferByFunc() {
  const_buffers_1 const_buffer_seq_adaptor = buffer("hello world");
  // ...

  return 0;
}

int BasicLearning::CreateMutableBufferByFunc() {
  const int kBufferSize = 20;
  auto buf = std::make_unique<char[]>(kBufferSize);
  auto buffer = asio::buffer(static_cast<void *>(buf.get()), kBufferSize);

  // ...

  return 0;
}

int BasicLearning::AsyncSendByWriteSome() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  std::string msg = "hello world!";
  try {
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    io_context ioc;
    ip::tcp::socket sock(ioc, ep.protocol());
    sock.connect(ep);

    // 记录发送的字节数量
    size_t num_send = 0;
    // 同步发送需要轮询，因为内核态缓存区不与用户态缓存区同步
    while (num_send != msg.size()) {
      // write_some 实际发送的个数可能比要发送的短
      num_send += sock.write_some(buffer(msg.c_str() + num_send, msg.size() - num_send));
    }

    // ...

    return 0;
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.code().message());
    return err.code().value();
  }
}

int BasicLearning::AsyncSendBySend() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  std::string msg = "hello world!";
  try {
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    io_context ioc;
    ip::tcp::socket sock(ioc, ep);

    // 发送并一直阻塞
    if (0 == sock.send(buffer(ip.c_str(), ip.size()))) {
      std::cout << std::format("error code: {}, error msg: {}", 1, "socket error");
      return 1;
    }
    return 0;
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}

int BasicLearning::AsyncSendByWrite() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  std::string msg = "hello world!";
  try {
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    io_context ioc;
    ip::tcp::socket sock(ioc, ep);

    // 发送并一直阻塞
    if (0 == write(sock, buffer(ip.c_str(), ip.size()))) {
      std::cout << std::format("error code: {}, error msg: {}", 1, "socket error");
      return 1;
    }
    return 0;
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}

int BasicLearning::AsyncReadByReadSome() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  const int kBlockSize = 7;
  char buf[kBlockSize];
  try {
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    io_context ioc;
    ip::tcp::socket sock(ioc, ep);

    // 记录读取的字节数量
    int num_read = 0;
    // 读取并一直阻塞
    while (num_read != kBlockSize) {
      num_read += sock.read_some(buffer(buf + num_read, kBlockSize - num_read));
    }
    std::cout << std::string(buf, kBlockSize);
    return 0;
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}

int BasicLearning::AsyncReadByReceive() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  const int kBlockSize = 7;
  char buf[kBlockSize];
  try {
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    io_context ioc;
    ip::tcp::socket sock(ioc, ep);

    // 发送并一直阻塞
    if (0 == sock.receive(buffer(buf, kBlockSize))) {
      std::cout << std::format("error code: {}, error msg: {}", 1, "socket error");
      return 1;
    }
    std::cout << std::string(buf, kBlockSize);
    return 0;
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}

int BasicLearning::AsyncSendByRead() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  const int kBlockSize = 7;
  char buf[kBlockSize];
  try {
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    io_context ioc;
    ip::tcp::socket sock(ioc, ep);

    // 发送并一直阻塞
    if (0 == read(sock, buffer(buf, kBlockSize))) {
      std::cout << std::format("error code: {}, error msg: {}", 1, "socket error");
      return 1;
    }
    std::cout << std::string(buf, kBlockSize);
    return 0;
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}

}

int main() {
  return 0;
}

