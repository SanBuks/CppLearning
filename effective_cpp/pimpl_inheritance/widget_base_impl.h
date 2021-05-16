#ifndef EFFECTIVE_CPP_PIMPL_INHERITANCE_WIDGET_BASE_IMPL_H_
#define EFFECTIVE_CPP_PIMPL_INHERITANCE_WIDGET_BASE_IMPL_H_

#include "widget_base.h"
#include <iostream>

class impl::Widget::WidgetImpl{
 public:
  void virtual test() { std::cout << "Base\n"; }
  virtual ~WidgetImpl();
};


#endif