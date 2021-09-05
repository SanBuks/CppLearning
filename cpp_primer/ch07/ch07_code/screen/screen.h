#ifndef CH07_CH07_CODE_SCREEN_H
#define CH07_CH07_CODE_SCREEN_H

#include <iostream>
#include <string>

#include "window_mgr.h"

class Screen {
  friend void Window_mgr::clear(ScreenIndex);
  friend void Window_mgr::print(ScreenIndex);

 public:
  typedef std::string::size_type pos;

  Screen() = default;
  Screen(pos ht, pos wd, char c = ' ')
      : height(ht), width(wd), cursor(ht * wd - 1), contents(ht * wd, c) {}

  inline pos size() const {
    return height * width;
  }
  inline char get() const {
    return contents[cursor];
  }
  inline char get(pos row, pos col) const {
    return contents[row * width + col];
  }
  inline Screen &set(char c) {
    contents[cursor] = c;
    return *this;
  }
  inline Screen &set(pos row, pos col, char c) {
    contents[row * width + col] = c;
    return *this;
  }
  inline Screen &move(pos row, pos col) {
    cursor = row * width + col;
    return *this;
  }

  Screen &display(std::ostream &os);
  const Screen &display(std::ostream &os) const;
  Screen copy_display(std::ostream &os) const;

 private:
  pos height = 0, width = 0;
  pos cursor = 0;
  std::string contents;

  void do_display(std::ostream &os) const ;
};

#endif