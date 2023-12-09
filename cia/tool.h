#ifndef TOOL_H_
#define TOOL_H_

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <thread>

std::string get_time() {
  auto current_time = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(current_time);
  auto time_info = std::localtime(&time_t);

  auto ticks = current_time.time_since_epoch().count();
  auto millis = ticks / 1000000 % 1000;
  auto micros = ticks / 1000 % 1000;
  char time_str[80];
  std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
  sprintf(time_str, "%s:%03d:%03d", time_str, static_cast<int>(millis), static_cast<int>(micros));
  return {time_str};
}

void print_time() {
  std::cout << get_time() << "\n";
}

bool random_bool() {
  static std::mt19937 gen(std::random_device{}());
  static std::uniform_int_distribution<int> dis(0, 1);
  return dis(gen);
}

size_t thread_id() {
  return std::hash<std::thread::id>()(std::this_thread::get_id());
}
#endif
