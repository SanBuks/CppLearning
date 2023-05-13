#include "03_use_const.h"
#include <iostream>

Rational::Rational(bool inner_status, int num)
    : inner_status_(inner_status),
      num_(num) {}

void Rational::StateChange() const {
  inner_status_ = true;
  std::cout << "state changed !\n";
}

// 语义上 不改变 任何用户感知的数据 和 返回的数据
const int &Rational::operator[](int index) const {
  std::cout << "operator [] const \n";
  // ...
  // 繁杂的检验流程
  // ...
  return num_;
}

// 语义上 所有数据都有可能被改变, 可委托 const 函数
int &Rational::operator[](int index) {
  std::cout << "operator []\n";
  num_ = 4;  // 存在
  return const_cast<int &>(
      (static_cast<const Rational &>(*this)[index])
  );  // 反过来委托则不行, 因为此函数会改变用户感知的属性属性
}

int main() {
  Rational rational{};
  const Rational kRational{};
  rational.StateChange();
  std::cout << "-----------\n";
  std::cout << rational[4] << "\n";
  std::cout << "-----------\n";
  std::cout << kRational[4] << "\n";
}