#pragma once
#include <iostream>
#include <string>
#include "Window_mgr.h"

class Screen{
    friend void Window_mgr::clear(ScreenIndex);
    friend void Window_mgr::print(ScreenIndex);
public:
    typedef std::string::size_type pos;

    Screen() = default;
    Screen(pos ht, pos wd, char c = ' ') : 
        height(ht), width(wd), contents(ht * wd, c){ 
        cursor = ht * wd - 1;
    }

    pos size() const;

    char get() const { return contents[cursor]; }
    inline 
    char get(pos row, pos col) const; 

    inline 
    Screen &set(char c);
    inline
    Screen &set(pos row, pos col, char c);

    Screen &move(pos row, pos col);

    Screen &display(std::ostream &os){
        do_display(os); return *this;
    }

    const Screen &display(std::ostream &os) const {
        do_display(os); return *this;
    }

private:
    void do_display(std::ostream &os) const { os<< contents; }
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};

inline
Screen &Screen::set(char c){
    contents[cursor] = c;
    return *this;
}

inline
Screen &Screen::set(pos row, pos col, char c){
    contents[row * width + col] = c;
    return *this;
}

inline
char Screen::get(pos row, pos col) const {
    return contents[row * width + col];
} 