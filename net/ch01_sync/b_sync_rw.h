#ifndef CH01_RW_H_
#define CH01_RW_H_

// const_buffer 和 mutable_buffer 结构, buffer_sequence 结构
// write_some, write/send,
// read_some, receive/read

namespace net {

struct ReadWriteLearning {

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
