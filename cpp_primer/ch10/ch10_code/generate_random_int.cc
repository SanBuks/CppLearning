#include <chrono>
#include <random>
#include <fstream>
#include <iostream>

int main() {

  unsigned long seeds =
      std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine e(seeds);
  std::uniform_int_distribution<int> u(0, std::numeric_limits<int>::max());

  std::ofstream ofs("data_10_33");
  if (!ofs) {
    std::cout << "Open file failed!" << "\n";
    return 1;
  }
  for (size_t i = 0; i != 100; ++i) {
    ofs << u(e) << "\n";
  }
  return 0;
}