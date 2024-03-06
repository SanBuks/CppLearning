#include <string>
#include <format>
#include <iostream>

#include <boost/asio.hpp>

using namespace boost;
using namespace boost::asio;

int main() {
  std::string ip = "127.0.0.1";
  unsigned int port = 2333;
  const int kBufferSize = 100;

  try {
    io_context ioc;
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    ip::tcp::socket sock(ioc, ep.protocol());
    sock.connect(ep);

    char request_buffer[kBufferSize];
    std::cout << "Enter message(no more than 100 character): \n";
    std::cin.getline(request_buffer, kBufferSize);
    auto length = strlen(request_buffer);
    if (0 == sock.send(buffer(request_buffer, length))) {
      std::cout << std::format("error code: {}, error msg: {}", 1, "socket send error");
      return 1;
    }

    char receive_buffer[kBufferSize];
    std::size_t rec_num;

    if (0 == (rec_num = sock.receive(buffer(receive_buffer, kBufferSize)))) {
      std::cout << std::format("error code: {}, error msg: {}", 1, "socket receive error");
      return 1;
    }
    std::cout << std::format("receive str: {}", std::string(receive_buffer, rec_num)) << std::endl;
    return 0;
  } catch (const system::system_error &err) {
    std::cout << std::format("error code: {}, error msg: {}", err.code().value(), err.what());
    return err.code().value();
  }
}