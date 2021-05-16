#include <iostream>

class Base {
 public:
  void WrapperFunc(int a = 3); //  or can call it TemplateFunc
                               //  avoid derived different default param problem
  ~Base();
 private:
  void virtual MethodFunc(int a);
};

Base::~Base() {}

void Base::MethodFunc(int a) {
  std::cout << "Base" << a << "\n";
}

void Base::WrapperFunc(int a) {
  std::cout << "Before Doing sth\n";
  MethodFunc(a);
  std::cout << "After Doing sth\n";
}

class Derived : public Base {
 private:
  void virtual MethodFunc(int a) override ;
};

void Derived::MethodFunc(int a) {
  std::cout << "Derived" << a << "\n";
}

int main() {
  Derived d;
  d.WrapperFunc();
  d.WrapperFunc(2);
  return 0;
}