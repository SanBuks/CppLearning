#ifndef CH01_BASIC_H_
#define CH01_BASIC_H_

#include <boost/asio.hpp>

// 1. Asio 网络连接过程
// 2. 基础接口使用
// 3. const_buffer 和 mutable_buffer 结构, buffer_sequence 结构
// 4. write_some, write/send, read_some, receive/read
namespace net {

using namespace boost;
using namespace boost::asio;

struct BasicLearning {
  // 创建 端点 示例
  static int CreateEndPoint();
  // 创建 socket 示例
  static int CreateSocket();
  // 创建 acceptor 并绑定 端点 示例
  static int CreateAcceptor();
  // 客户端 IP 直接连接 端点 示例
  static int ConnectEndPoint();
  // 客户端 DNS 解析连接 端点 示例
  static int DnsConnectEndPoint();
  // 服务端 接收 连接 示例
  static int AcceptConnection();

  // 创建 ConstBufferSequence 两种方法
  static int CreateConstBuffer();
  // 创建 MutableBufferSequence 两种方法
  static int CreateMutableBufferByFunc();

  // 同步 轮询调用 write_some 发送所有数据
  static int SyncByWriteSome();
  // 同步 调用 socket.send / write(socket) 发送所有数据
  static int SyncBySendOrWrite();

  // 同步 轮询调用 read_some 读取所有数据
  static int SyncByReadSome();
  // 同步 调用 socket.receive / read(socket) 读取所有数据
  static int SyncByReceiveOrRead();
};

}

#endif