#ifndef EFFECTIVE_CPP_PIMPL_INHERITANCE_WIDGET_DERIVED_IMPL_H_
#define EFFECTIVE_CPP_PIMPL_INHERITANCE_WIDGET_DERIVED_IMPL_H_

#include "widget_base_impl.h"
#include "widget_derived.h"

class impl::WidgetDerived::WidgetDerivedImpl : 
    public impl::WidgetDerived::WidgetImpl{
 public:
  void test() override { std::cout << "Derived\n"; } 
  ~WidgetDerivedImpl();
};


#endif