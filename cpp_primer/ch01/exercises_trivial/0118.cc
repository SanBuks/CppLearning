#include <iostream>

int main() {
  int currVal = 0, val = 0;
  if (std::cin >> currVal) {  // 第一个数判断
    int cnt = 1;
    while (std::cin >> val) {
      if (val == currVal) cnt++;
      else {
        std::cout << " Value : " << currVal
                  << " occurs " << cnt << " times\n";
        currVal = val;
        cnt = 1;
      }
    }
    std::cout << " Value : " << currVal  // 输出最后一个数
              << " occurs " << cnt << " times\n";
  }
  return 0;
}
