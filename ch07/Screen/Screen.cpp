#include "Screen.h"
Screen &Screen::move(pos row, pos col){
    cursor = row * width + col;
    return *this;
}
Screen::pos Screen::size() const{
    return height * width;
}