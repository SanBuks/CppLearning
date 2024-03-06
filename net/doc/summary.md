# CH01
- server:
  - socket 创建 socket 对象
  - bind 绑定 IP & Port
  - listen 监听
  - accept 创建新 socket 与客户端通信
  - read, write
- client:
  - socket
  - connect 连接发起请求
  - read, write
- 多路复用: 
  - iocp
  - epoll
  - proactor 模式 
  - reactor 模式
- 创建 socket: io_context, protocol, socket, socket.open 
- 创建 acceptor: io_context, protocol, acceptor, acceptor.open 
- 绑定 acceptor: acceptor.bind
- 监听并处理: acceptor.listen, acceptor.accept(socket);

# CH02
- MutableBufferSequence 可理解为 `vector<asio::mutable_buffer> buffer`: 写服务
- ConstBufferSequence 可理解为 `vector<asio::const_buffer> buffer`: 读服务
- 每个 buffer 首个元素存储了后续字符数
- buffer() 创建 *BufferSequnce 适配器, 传递可写对象: mutable_buffers_1, 传递可读对象: const_buffers_1
- read/receive: 阻塞读取到指定字节数
- write/send: 阻塞写入指定字节数
- write_some: 非阻塞, 尽可能写入, 返回写入字节数
- read_some: 非阻塞, 尽可能读, 返回读出字节数