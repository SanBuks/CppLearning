#pragma once
#include <vector>
#include <string>
class Screen;
class Window_mgr{
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
    void print(ScreenIndex);
    ScreenIndex addScreen(const Screen &); 
    Window_mgr();
private:
    std::vector<Screen> screens{};
};