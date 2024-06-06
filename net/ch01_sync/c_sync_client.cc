#include <string>
#include <format>
#include <iostream>

#include "spdlog/spdlog.h"
#include "asio.hpp"
#include "iconv.h"

using namespace asio;

std::optional<std::string> GBK2Utf8(const char *ibytes, size_t isize) {
  iconv_t cd = iconv_open("UTF-8", "GBK");
  if (cd == (iconv_t) - 1) return std::nullopt;

  size_t osize = isize * 2;
  auto obuffer = std::make_unique_for_overwrite<char[]>(osize);
  for (int i = 0; i < osize; ++i) { obuffer[i] = '\0'; }
  auto obytes = obuffer.get();


  if (iconv(cd, const_cast<char**>(&ibytes), &isize, &obytes, &osize) == (size_t) -1) {
    iconv_close(cd);
    return std::nullopt;
  }
  iconv_close(cd);
  return {std::string(obuffer.get())};
}

int main() {
  system("chcp 65001");
  std::string ip = "127.0.0.1";
  unsigned int port = 233;
  const int kBufferSize = 100;
  try {
    io_context ioc;
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip), port);
    ip::tcp::socket sock(ioc, ep.protocol());
    spdlog::info("socket begin connect!");
    sock.connect(ep);
    spdlog::info("socket connected!");

    char request_buffer[kBufferSize] = ":MEAS? Urms1, Urms2\r\n";
    auto length = strlen(request_buffer);
    if (0 == sock.send(buffer(request_buffer, length))) {
      spdlog::error("error code: {}, error msg: {}", 1, "socket send error");
      return 1;
    }

    char receive_buffer[kBufferSize];
    std::size_t rec_num;

    if (0 == (rec_num = sock.receive(buffer(receive_buffer, kBufferSize)))) {
      spdlog::error("error code: {}, error msg: {}", 1, "socket receive error");
      return 1;
    }
    spdlog::info("receive str: {}", std::string(receive_buffer, rec_num));
    return 0;
  } catch (const system_error &err) {
    const auto &msg = GBK2Utf8(err.what(), strlen(err.what())).value_or("");
    spdlog::error("error code: {}, error msg: {}", err.code().value(), msg);
    return err.code().value();
  }
}