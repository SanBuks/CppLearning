# Basic
## 通信流程
```text
server:                   client:
acceptor(socket)          socket
|                         |
| bind (ip, port)         | connect
v                         V
listen                    read/write
|
| accept
v
socket -> read/write
```

## 多路复用模式
- iocp
- epoll
- pro-actor
- reactor
 
## 编程基础
- 系统错误: `system::error_code err`, `err.failed()` 判断
- IP 地址 与 端点: 
  - `auto ip_address = ip::address::from_string("127.0.0.1", err);`
  - `auto ip_address = ip::address_v4::any();`
  - `ip::tcp::endpoint ep(ip_address, 2333);`
- Protocol: `ip::tcp protocol = ip::tcp::v4();`
- IO Context: 
  - 系统 IO 上下文, 提供异步支持
  - `auto ioc = std::make_shared<asio::io_context>();`
 
## 创建 Socket
- 创建后打开: 
  - `ip::tcp::socket sock(ioc);`
  - `sock.open(protocol, err);`
- 创建并打开: `ip::tcp::socket sock(ioc, protocol);`
- 创建打开并绑定: `ip::tcp::socket sock(ioc, ep);`

## 创建 Acceptor
- 创建后打开: 
  - `ip::tcp::acceptor acceptor(ioc);`
  - `acceptor.open(protocol, err)`
- 创建并打开: `ip::tcp::acceptor acceptor(ioc, protocol);`
- 创建打开并绑定: `ip::tcp::acceptor acceptor(ioc, ep);`
- 直接绑定端点: `acceptor.bind(ep, err);`
- 监听指定连接数: `acceptor.listen(30);`, 
- 创建新的连接: `acceptor.accept(new_sock);`;

## 连接 Socket
- 连接端点: `sock.connect(ep);`
  
## DNS 解析
- 解析请求: `ip::tcp::resolver::query resolver_query(host_name, port_num, ip::tcp::resolver::numeric_service);`
- 解析器: `ip::tcp::resolver resolver(ioc);`
- 解析域名: `auto it = resolver.resolve(resolver_query);`
- 连接: `connect(sock, it);`

# ReadWrite
## buffer 概念
- `mutable/const_buffer` 用于写/读 
- 连续的存储空间, 首元素存放元素个数
- buffer 不拥有数据生命周期, 只是表示范围
```text
const_buffer: [3][...][...][...]
mutable_buffer: [5][...][...][...][...][...]
```
- MutableBufferSequence 可理解为 `vector<asio::mutable_buffer> buffer`
- ConstBufferSequence 可理解为 `vector<asio::const_buffer> buffer`

## buffer 创建
- 只读 buffer
  - 创建 `const_buffer`, 创建 `vector<const_buffer>`
  - 函数 `buffer("plain text")` 创建 const_buffer
- 可写 buffer
  - 创建 `mutable_buffer`, 创建 `vector<mutable_buffer`
  - 函数 `buffer(array, 3);` 创建 mutable_buffer

## 读写
- sock.write_some: 非阻塞, 尽可能写入, 返回写入字节数, 需要轮询发送
- write(sock,..)/sock.send: 阻塞写入指定字节数
- read_some: 非阻塞, 尽可能读, 返回读出字节数, 可能需要轮询读取
- read(sock,..)/sock.receive: 阻塞读取到指定字节数

# SyncServer
- Server 创建 accept, 接收 socket 
- Session 通过线程处理 socket
- 获取远端地址 session sock->remote_endpoint().address()