#include "Screen.h"
Screen &Screen::move(pos row, pos col){
    cursor = row * width + col;
    return *this;
}