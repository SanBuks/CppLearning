#include "Screen.h"

int main(){
    Screen myScreen(5, 3);
    const Screen blank(5, 3);
    myScreen.set('#').display(std::cout);
    std::cout<<"\n";
    blank.display(std::cout);
    return 0;
}