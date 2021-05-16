#include "widget_derived_impl.h"

impl::WidgetDerived::WidgetDerivedImpl::~WidgetDerivedImpl() {}

impl::WidgetDerived::WidgetDerived() : 
    Widget(), pimpl_(new WidgetDerivedImpl()) {
}
impl::WidgetDerived::~WidgetDerived() { }
void impl::WidgetDerived::test() { 
  Widget::test();
  pimpl_->test();
}