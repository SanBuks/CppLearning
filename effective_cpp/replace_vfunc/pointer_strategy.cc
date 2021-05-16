#include <iostream>

class Base {
 public:
  using PMethod = void (*)(int a);
  Base(PMethod p);

  void WrapperFunc();  // or can call it TemplateFunc

 private:
  PMethod p_;  // pointer to Method 可以被替换成 function 或 strategi 类指针
};

Base::Base(PMethod p) : p_(p) {}

void Base::WrapperFunc() {
  (*p_)(2);
}

class Derived : public Base {
 public:
  Derived(PMethod p);
};

Derived::Derived(PMethod p) : Base(p){
}

void method1(int a) {
  std::cout << 2 * a << "\n";
}

int main() {
  Derived d(method1);
  d.WrapperFunc();
  return 0;
}