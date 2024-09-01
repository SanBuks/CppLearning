#ifndef CH02_BASIC_H_
#define CH02_BASIC_H_

#include <memory>
#include <queue>

#include "asio.hpp"
#include "spdlog/spdlog.h"

namespace net {

using namespace asio;

// 写会话类
class WriteSession {
 public:
  using sock_ptr = std::shared_ptr<ip::tcp::socket>;

  explicit WriteSession(sock_ptr sock);
  void Connect(const ip::tcp::endpoint &ep);

  // 异步发送数据 回调函数 (存在回调乱序问题)
  void WriteCallBackErr(const system::error_code &error_code,
                        std::size_t bytes_send,
                        std::shared_ptr<MsgNode> msg_send);
  // 异步发送数据 (存在回调乱序问题)
  void WriteSocketErr(const std::string &msg);


  // 异步发送数据 回调函数 (通过队列保持回调发送顺序)
  void WriteCallBack(const system::error_code &error_code, std::size_t bytes_send);
  // 异步发送数据 (通过队列保持回调发送顺序)
  void WriteSocket(const std::string &msg);

  // 异步发送所有数据
  void WriteAllCallBack(const system::error_code &error_code, std::size_t bytes_send);
  // 异步发送所有数据 (async_send 不能和 async_write_some 混着用)
  void WriteAllSocket(const std::string &msg);

 private:
  sock_ptr socket_;
  std::queue<std::shared_ptr<MsgNode>> msg_queue_;
  bool pending_;
};

class ReadSession {
 public:
  static constexpr const int kRecSize = 1024;

  using sock_ptr = std::shared_ptr<ip::tcp::socket>;

  explicit ReadSession(sock_ptr socket);
  void Connect(const ip::tcp::endpoint &ep);

  // 异步读取数据
  void ReadCallBack(const error_code &error_code, std::size_t bytes_read);
  // 异步读取数据
  void ReadSocket();

  // 异步读取所有数据 回调
  void ReadAllCallBack(const error_code &error_code, std::size_t bytes_read);
  // 异步读取所有数据 (async_receive 不能和 async_read_some 混着用)
  void ReadAllSocket();

 private:
  sock_ptr socket_;
  std::shared_ptr<MsgNode> msg_node_;
  bool recv_pending_;
};
}

#endif
