#include <string>
#include <cstdio>
#include <memory>

namespace cpp_primer {

/**
 * 将多个参数 args 按 `format` 格式生成一个 string
 * from iFreilicht 
 * https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
 */
template<typename ... Args>
std::string string_format(const std::string& format, Args ... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
  if (size_s <= 0) {
    throw std::runtime_error("[string_format] : Error During Formatting!");
  }
  auto size = static_cast<size_t>(size_s);
  auto buf = std::unique_ptr<char []>(new char[size]);
  std::snprintf(buf.get(), size, format.c_str(), args ... );
  return std::string(buf.get(), buf.get() + size - 1);
}

}