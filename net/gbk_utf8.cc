#include <iostream>
#include <format>
#include <stdexcept>
#include <codecvt>
#include <optional>

#include <iconv.h>
#include <boost/asio.hpp>

using namespace boost;

std::pair<bool, std::string> GBK2Utf8(char *ibytes, size_t isize) {
  iconv_t cd = iconv_open("UTF-8", "GBK");
  if (cd == (iconv_t) -1) return {false, std::format("初始化 GBK 转换 UTF-8 器失败!")};

  size_t osize = isize * 2;
  auto obuffer = std::make_unique_for_overwrite<char[]>(osize);
  auto obytes = obuffer.get();

  if (iconv(cd, &ibytes, &isize, &obytes, &osize) == (size_t) -1) {
    iconv_close(cd);
    return {false, std::format("GBK 转换 UTF-8 失败!")};
  }
  iconv_close(cd);
  return {true, std::string(obuffer.get())};
}

int main() {
  ::system("chcp 65001");
  std::cout << std::format("你好\n");
  try {
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::from_string("127.0.0.1"), 23);
    asio::io_context ioc;
    asio::ip::tcp::socket socket(ioc, ep.protocol());
    socket.connect(ep);
  } catch (const std::exception &ex) {
    auto raw = ex.what();
    auto res = GBK2Utf8((char*) raw, strlen(raw));
    if (res.first) {
      std::cout << res.second << "\n";
    } else {
      std::cout << raw << "\n";
    }
  }
  return 0;
}
