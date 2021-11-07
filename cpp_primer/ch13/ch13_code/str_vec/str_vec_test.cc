#include "str_vec.h"

#include <iostream>

int main() {
  StrVec sv;
  sv.PushBack("123");
  sv.PushBack("456");
  sv.PushBack("789");
  for (auto it = sv.CBegin(); it != sv.CEnd(); ++it) {
    std::cout << *it << " ";
  }

  std::cout << "\n";

  StrVec svv(sv);
  svv = {"123", "654", "789", "101112"};
  for (auto it = svv.CBegin(); it != svv.CEnd(); ++it) {
    std::cout << *it << " ";
  }

  return 0;
}
