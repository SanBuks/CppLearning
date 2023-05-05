#include <iostream>

#include "widget_base.h"
#include "widget_derived.h"

int main() {
  impl::WidgetDerived d;
  d.test();
  return 0;
}