#include "widget_base_impl.h"

impl::Widget::WidgetImpl::~WidgetImpl(){ }

void impl::Widget::test() { 
  pimpl_->test(); 
}

impl::Widget::~Widget() { }
impl::Widget::Widget() : pimpl_(new WidgetImpl()) { }