#ifndef CH01_BASIC_H_
#define CH01_BASIC_H_

// 1. Asio 网络连接过程
// 2. 基础对象及使用
//     ip, port, endpoint
//     socket, acceptor, protocol
//     dns
namespace net {

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
};

}

#endif