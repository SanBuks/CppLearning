#include "02_class_static_variable.h"

#include <iostream>

// 当要取类中的静态变量地址时必须定义 且 必须在 .cc 文件中定义
//const int ClassStaticVariable::kClassStaticVariable;

int main() {
  std::cout << ClassStaticVariable::kClassStaticVariable << "\n";
  std::cout << &ClassStaticVariable::kClassStaticVariable << "\n";  // wrong, 必须要有定义式
  std::cout << &ClassStaticVariable::kNumberSize << "\n";           // wrong, 无法对枚举取地址
  return 0;
}