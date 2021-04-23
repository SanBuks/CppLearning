#include "Screen.h"
void screenTest(){
    const Screen blank(5, 3);
    Screen myScreen(5, 3);
    myScreen.set('#').display(std::cout);
    std::cout<<"\n";
    blank.display(std::cout);
}

void windowMgrTest(){
    Window_mgr wmgr;
    wmgr.print(0);
}

int main(){
    windowMgrTest();
    return 0;
}