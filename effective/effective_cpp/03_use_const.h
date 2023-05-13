#ifndef EFFECTIVE_CPP_03_USE_CONST_H_
#define EFFECTIVE_CPP_03_USE_CONST_H_

class Rational {
 public:
  explicit Rational(bool inner_status = false, int num = 3);
  void StateChange() const;
  int &operator[](int index);               // 注意返回 左值引用
  const int &operator[](int index) const ;  // 注意返回 const 左值引用
 private:
  // 追求逻辑上的 const, 即用户感受不出来的数据改变可以设为 mutable,
  // 方便在 const 函数中调用
  mutable bool inner_status_;
  int num_;
};

#endif
