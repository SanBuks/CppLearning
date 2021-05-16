#ifndef EFFECTIVE_CPP_PIMPL_INHERITANCE_WIDGET_DERIVED_H_
#define EFFECTIVE_CPP_PIMPL_INHERITANCE_WIDGET_DERIVED_H_

#include "widget_base.h"

namespace impl{

class WidgetDerived final : public Widget {
 private:
  class WidgetDerivedImpl;
  std::unique_ptr<WidgetDerivedImpl> pimpl_;
 public:
  WidgetDerived();
  ~WidgetDerived();
  void test() override;
};

}

#endif