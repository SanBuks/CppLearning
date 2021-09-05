#include "screen.h"

void Screen::do_display(std::ostream &os) const {
  for (std::size_t i = 0; i != height; ++i) {
    os << contents.substr(i * width, width) << "\n";
  }
}

Screen &Screen::display(std::ostream &os) {
  return const_cast<Screen&>(
      static_cast<const Screen&>(*this).display(os)
  );
}

const Screen &Screen::display(std::ostream &os) const {
  do_display(os);
  return *this;
}

Screen Screen::copy_display(std::ostream &os) const {
  do_display(os);
  return *this;
}