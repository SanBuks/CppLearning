#ifndef CH01_BASIC_H_
#define CH01_BASIC_H_

#include <boost/asio.hpp>

// 1. Asio 网络连接过程
// 2. const_buffer 和 mutable_buffer 结构, buffer_sequence 结构
// 3. 基础接口使用
namespace net {

using namespace boost;
using namespace boost::asio;

struct BasicLearning {
  // 创建 客户端 端点 示例
  static int CreateClientEndPoint();
  // 创建 服务端 端点 示例
  static int CreateServerEndPoint();


  // 创建 客户端 socket 示例
  static int CreateSocket();
  // 创建 服务端 acceptor 示例
  static int CreateAcceptor();
  // 绑定 服务端 acceptor 示例
  static int BindAcceptor();
  // 创建并绑定 服务端 acceptor 示例
  static int CreateBindAcceptor();


  // 客户端 IP 直接连接 端点 示例
  static int ConnectEndPoint();
  // 客户端 DNS 解析连接 端点 示例
  static int DnsConnectEndPoint();
  // 服务端 接收 连接 示例
  static int AcceptConnection();

  // 通过 buffer_sequence 创建 const_buffer
  static int CreateConstBufferByVector();
  // 使用 buffer 函数 创建 const_buffers_1 适配器
  static int CreateConstBufferByFunc();
  // 通过 buffer 函数 创建 mutable_buffers_1 适配器
  static int CreateMutableBufferByFunc();

  // 同步 轮询调用 write_some 发送所有数据
  static int AsyncSendByWriteSome();
  // 同步 调用 send 发送所有数据
  static int AsyncSendBySend();
  // 同步 调用 write 发送所有数据
  static int AsyncSendByWrite();

  // 同步 轮询调用 read_some 读取所有数据
  static int AsyncReadByReadSome();
  // 同步 调用 receive 读取所有数据
  static int AsyncReadByReceive();
  // 同步 调用 read 读取所有数据
  static int AsyncSendByRead();
};


}

#endif