#include "Screen.h"

Window_mgr::ScreenIndex 
Window_mgr::addScreen(const Screen &s){
    screens.push_back(s);
    return screens.size() - 1;
}

Window_mgr::Window_mgr(){
    screens.push_back(Screen(24, 80, '*'));
}

void Window_mgr::print(ScreenIndex index){
    screens[index].display(std::cout);
}

void Window_mgr::clear(ScreenIndex index){
    Screen &s = screens[index];
    s.contents = std::string(s.height * s.width, ' ');
}