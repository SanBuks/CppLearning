#ifndef EFFECTIVE_CPP_PIMPL_INHERITANCE_WIDGET_BASE_H_
#define EFFECTIVE_CPP_PIMPL_INHERITANCE_WIDGET_BASE_H_

#include <memory>

namespace impl{

class Widget{
 protected:
  class WidgetImpl;
 private:
  std::unique_ptr<WidgetImpl> pimpl_;
 public:
  Widget();
  virtual ~Widget();
  virtual void test();
};

}

#endif