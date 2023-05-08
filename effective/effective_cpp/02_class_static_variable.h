#ifndef EFFECTIVE_CPP_02_CLASS_STATIC_VARIABLE_H_
#define EFFECTIVE_CPP_02_CLASS_STATIC_VARIABLE_H_
class ClassStaticVariable {
 public:
  static const int kClassStaticVariable = 3;  // 声明式
  enum { kNumberSize = 3 };
  int score_[kClassStaticVariable];           // 类内静态变量允许用于 in class 初始化
//int score_[kNumberSize ];                   // enum hack 用于 in class 初始化
};
#endif
