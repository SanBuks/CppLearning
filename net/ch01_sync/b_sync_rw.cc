#include "b_sync_rw.h"

#include <iostream>
#include <format>

#include "asio.hpp"
#include "spdlog/spdlog.h"

namespace net {

using namespace asio;

int ReadWriteLearning::CreateConstBuffer() {
  // method 1
  // 使用 const_buffer & vector 手动创建
  std::string str = "hello world";
  const_buffer const_buf(str.c_str(), str.size());
  std::vector<const_buffer> const_buffer_seq{const_buf};

  // method 2
  // 使用 buffer() 创建 const_buffers_1 适配器
  const_buffer const_buffer_seq_adaptor = buffer("hello world");

  return 0;
}

int ReadWriteLearning::CreateMutableBufferByFunc() {
  const int kBufferSize = 20;

  // method 1
  // 使用 mutable_buffer & vector 手动创建
  auto buf = std::make_unique<char[]>(kBufferSize);
  mutable_buffer mutable_buf(buf.get(), kBufferSize);
  std::vector<mutable_buffer> mutable_buffer_seq{mutable_buf};

  // method 2
  // 使用 buffer 创建 mutable_buffers_1

  auto buf2 = std::make_unique<char[]>(kBufferSize);
  mutable_buffer buffer = asio::buffer(static_cast<void *>(buf2.get()), kBufferSize);

  return 0;
}

int ReadWriteLearning::SyncByWriteSome() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  std::string msg = "hello world!";
  try {
    io_context ioc;
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port) ;
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
  } catch (const system_error &err) {

    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.code().message());
    return err.code().value();
  }
}

int ReadWriteLearning::SyncBySendOrWrite() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  std::string msg = "hello world!";
  try {
    io_context ioc;
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    ip::tcp::socket sock(ioc, ep.protocol());
    sock.connect(ep);
    // 发送并一直阻塞
    if (0 == sock.send(buffer(msg.c_str(), msg.size()))) {
//  if (0 == write(sock, buffer(ip.c_str(), ip.size()))) {
      std::cout << std::format("error code: {}, error msg: {}", 1, "socket error");
      return 1;
    }
    return 0;
  } catch (const system_error &err) {
    spdlog::error("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}

int ReadWriteLearning::SyncByReadSome() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  const int kBlockSize = 7;
  char buf[kBlockSize];
  try {
    io_context ioc;
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    ip::tcp::socket sock(ioc, ep.protocol());
    sock.connect(ep);

    // 记录读取的字节数量
    size_t num_read = 0;
    // 读取并一直阻塞
    while (num_read != kBlockSize) {
      num_read += sock.read_some(buffer(buf + num_read, kBlockSize - num_read));
    }
    std::cout << std::string(buf, kBlockSize);
    return 0;
  } catch (const system_error &err) {
    spdlog::error("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}

int ReadWriteLearning::SyncByReceiveOrRead() {
  std::string ip = "192.168.1.106";
  unsigned int port = 23;
  const int kBlockSize = 1024;
  char buf[kBlockSize];
  try {
    io_context ioc;
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    ip::tcp::socket sock(ioc, ep.protocol());
    sock.connect(ep);

    // 发送并一直阻塞
    if (0 == sock.receive(buffer(buf, kBlockSize))) {
//  if (0 == read(sock, buffer(buf, kBlockSize))) {
      std::cout << std::format("error code: {}, error msg: {}", 1, "socket error");
      return 1;
    }
    std::cout << std::string(buf, kBlockSize);
    return 0;
  } catch (const system_error &err) {
    spdlog::error("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}

}