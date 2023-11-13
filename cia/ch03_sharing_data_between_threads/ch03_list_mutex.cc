#include <list>
#include <mutex>
#include <algorithm>
#include <thread>
#include <iostream>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
  std::lock_guard<std::mutex> guard(some_mutex);
  some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find) !=
      some_list.end();
}

int main() {

  add_to_list(2);
  std::thread t(add_to_list, 3);
  for (auto &item: some_list) {
    std::cout << item << "\n";
  }
  t.join();
}