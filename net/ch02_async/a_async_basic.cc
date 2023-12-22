#include "a_async_basic.h"

#include <functional>
#include <iostream>
#include <format>

namespace net {

MsgNode::MsgNode(const char *msg, std::size_t len)
    : msg_(new char[len]{}),
      cur_len_(0),
      len_(len) {
  memcpy(msg_, msg, len);
}
MsgNode::MsgNode(std::size_t len)
    : msg_(new char[len]{}),
      cur_len_(0),
      len_(len) {}
MsgNode::~MsgNode() { delete [] msg_; }

char *MsgNode::GetMsg() const { return msg_; }
unsigned int MsgNode::GetCurLen() const { return cur_len_; }
unsigned int MsgNode::GetLen() const { return len_; }

void MsgNode::SetMsg(char *msg) { msg_ = msg; }
void MsgNode::SetCurLen(unsigned int cur_len) { cur_len_ = cur_len; }
void MsgNode::SetLen(unsigned int len) { len_ = len; }

WriteSession::WriteSession(sock_ptr sock)
    : socket_(sock),
      msg_queue_(),
      pending_(false) {}
void WriteSession::Connect(const ip::tcp::endpoint &ep) { socket_->connect(ep); }

// TCP 底层协议栈与用户态存在缓冲区不一致情况, 所以需要不断回调
// 但是 asio 封装 epoll或iocp 多路复用模型, 当写事件就绪后就发数据,
// 发送的数据按照 async_write_some 调用的顺序发送,
// 所以回调函数内调用的 async_write_some 可能并没有被及时调用
void WriteSession::WriteCallBackErr(const system::error_code &error_code,
                                    std::size_t bytes_send,
                                    std::shared_ptr<MsgNode> msg_send) {
  if (error_code.failed()) {
    std::cout << std::format("error value : {}, err message : {}", error_code.value(),  error_code.message());
    return;
  }
  // 只要小于需要发送的总长度就继续异步发送
  if (bytes_send + msg_send->GetCurLen() < msg_send->GetLen()) {
    // 更新 msg_send 长度
    msg_send->SetCurLen(bytes_send + msg_send->GetCurLen());
    // 创建新的 send_buffer 对象
    auto send_buffer = buffer(msg_send->GetMsg() + msg_send->GetCurLen(),
                              msg_send->GetLen() - msg_send->GetCurLen());
    // 绑定新的回调函数
    auto caller = bind(&WriteSession::WriteCallBackErr, this,
                       std::placeholders::_1, std::placeholders::_2, msg_send);
    // 异步发送
    socket_->async_write_some(send_buffer, caller);
  }
}

void WriteSession::WriteSocketErr(const std::string &msg) {
  auto msg_node = std::make_shared<MsgNode>(msg.c_str(), msg.size());
  auto caller = bind(&WriteSession::WriteCallBackErr, this,
                     std::placeholders::_1, std::placeholders::_2, msg_node);
  socket_->async_write_some(buffer(msg_node->GetMsg(),
                                   msg_node->GetLen()),
                            caller);
}

void WriteSession::WriteCallBack(const system::error_code &error_code, std::size_t bytes_send) {
  if (error_code.failed()) {
    std::cout << std::format("error value : {}, err message : {}", error_code.value(),  error_code.message());
    return;
  }

  // 更新当前数据
  auto &send_data = msg_queue_.front();
  send_data->SetCurLen(send_data->GetCurLen() + bytes_send);

  // 没法继续发送
  if (send_data->GetCurLen() < send_data->GetLen()) {
    auto send_buffer = buffer(send_data->GetMsg() + send_data->GetCurLen(),
                              send_data->GetLen() - send_data->GetCurLen());
    auto caller = std::bind(&WriteSession::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2);
    socket_->async_write_some(send_buffer, caller);
    return;
  }

  // 发送完取下一个消息
  msg_queue_.pop();
  if (msg_queue_.empty()) {
    pending_ = false;
    return;
  } else {
    // 发送新消息
    auto &new_send_data = msg_queue_.front();
    auto send_buffer = buffer(new_send_data->GetMsg(), new_send_data->GetLen());
    auto caller = std::bind(&WriteSession::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2);
    socket_->async_write_some(send_buffer, caller);
    return;
  }
}

void WriteSession::WriteSocket(const std::string &msg) {
  auto msg_node = std::make_shared<MsgNode>(msg.c_str(), msg.size());
  msg_queue_.push(msg_node);
  if (pending_) return;

  auto send_buffer = buffer(msg);
  auto caller = std::bind(&WriteSession::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2);
  socket_->async_write_some(send_buffer, caller);
  pending_ = true;
}

// 异步发送所有数据
void WriteSession::WriteAllCallBack(const system::error_code &error_code, std::size_t bytes_send) {
  if (error_code.failed()) {
    std::cout << std::format("error value : {}, err message : {}", error_code.value(),  error_code.message());
    return;
  }
  msg_queue_.pop();
  if (msg_queue_.empty()) {
    pending_ = false;
    return;
  }


  auto &data = msg_queue_.front();
  socket_->async_send(buffer(data->GetMsg(), data->GetLen()),
                      std::bind(&WriteSession::WriteAllCallBack, this,
                                std::placeholders::_1, std::placeholders::_2));

}
// 异步发送所有数据 (async_send 不能和 async_write_some 混着用)
void WriteSession::WriteAllSocket(const std::string &msg) {
  auto msg_node = std::make_shared<MsgNode>(msg.c_str(), msg.size());
  msg_queue_.push(msg_node);
  if (pending_) return;
  socket_->async_send(buffer(msg),
                      std::bind(&WriteSession::WriteAllCallBack, this,
                                std::placeholders::_1, std::placeholders::_2));
  pending_ = true;
}

ReadSession::ReadSession(ReadSession::sock_ptr socket)
    : socket_(socket),
      recv_pending_(false) {}

void ReadSession::Connect(const ip::tcp::endpoint &ep) {
  socket_->connect(ep);
}

void ReadSession::ReadCallBack(const system::error_code &error_code, std::size_t bytes_read) {
  if (error_code.failed()) {
    std::cout << std::format("error value : {}, err message : {}", error_code.value(),  error_code.message());
    return;
  }

  msg_node_->SetCurLen(msg_node_->GetCurLen() + bytes_read);
  if (msg_node_->GetCurLen() < msg_node_->GetLen()) {
    auto get_buffer = buffer(msg_node_->GetMsg() + msg_node_->GetCurLen(),
                             msg_node_->GetLen() - msg_node_->GetCurLen());
    auto caller = std::bind(&ReadSession::ReadCallBack, this, std::placeholders::_1, std::placeholders::_2);
    socket_->async_read_some(get_buffer, caller);
  }

  // ... 数据传输给逻辑层

  recv_pending_ = false;
  msg_node_ = nullptr;
}

void ReadSession::ReadSocket() {
  if (recv_pending_) return;
  msg_node_ = std::make_shared<MsgNode>(kRecSize);
  socket_->async_read_some(buffer(msg_node_->GetMsg(), msg_node_->GetLen()),
                           std::bind(&ReadSession::ReadCallBack, this, std::placeholders::_1, std::placeholders::_2));
  recv_pending_ = true;
}

void ReadSession::ReadAllCallBack(const system::error_code &error_code, std::size_t bytes_read) {
  if (error_code.failed()) {
    std::cout << std::format("error value : {}, err message : {}", error_code.value(),  error_code.message());
    return;
  }

  msg_node_->SetCurLen(msg_node_->GetCurLen() + bytes_read);

  // ... 数据传输给逻辑层

  recv_pending_ = false;
  msg_node_ = nullptr;
}

void ReadSession::ReadAllSocket() {
  if (recv_pending_) return;
  msg_node_ = std::make_shared<MsgNode>(kRecSize);
  socket_->async_receive(buffer(msg_node_->GetMsg(), msg_node_->GetLen()),
                         std::bind(&ReadSession::ReadCallBack, this, std::placeholders::_1, std::placeholders::_2));
  recv_pending_ = true;
}

}