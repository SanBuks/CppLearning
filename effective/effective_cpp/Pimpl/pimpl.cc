#include "pimpl.h"
#include <iostream>
class Widget::WidgetImpl{
 public:
  explicit WidgetImpl(int number);
  ~WidgetImpl();
  WidgetImpl(const WidgetImpl &rhs) = delete;
  WidgetImpl(WidgetImpl &&rhs) = delete;
  WidgetImpl &operator =(const WidgetImpl &rhs) = delete;
  WidgetImpl &operator =(WidgetImpl &&rhs) = delete;

  void show();
 private:
  int number_;
};

Widget::WidgetImpl::WidgetImpl(int number) : number_(number) {}
Widget::WidgetImpl::~WidgetImpl() { 
  std::cout << "Dtor : " << number_ << "\n"; 
}
void Widget::WidgetImpl::show() {
  std::cout << number_ << "\n";
}

Widget::Widget(int number) : pimpl_(new WidgetImpl(number)) { }
Widget::~Widget() = default;
Widget::Widget(Widget &&rhs) : pimpl_(std::move(rhs.pimpl_)){ }
Widget &Widget::operator =(Widget &&rhs) { 
  pimpl_  = std::move(rhs.pimpl_); 
  return *this;
}
void Widget::show() { pimpl_->show(); }


int main() {
  Widget w(3);
  Widget s(2);
  w.show();
  s.show();
  w = std::move(s);
  w.show();
}