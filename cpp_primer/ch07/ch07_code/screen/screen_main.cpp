#include "screen.h"

void screenTest() {
  const Screen blank(5, 3, ' ');
  Screen myScreen(5, 3, '*');
  myScreen.set('#').display(std::cout);
  blank.display(std::cout);
}

void windowMgrTest() {
  Window_mgr wmgr;
  wmgr.print(0);
  wmgr.clear(0);
  wmgr.print(0);
}

void testReturnLeftValue(){
  Screen myScreen1(5, 3, '*');
  myScreen1.display(std::cout).set('#');
  myScreen1.display(std::cout);

  std::cout<<"\n";

  Screen myScreen2(5, 3, '*');
  myScreen2.copy_display(std::cout).set('#');
  myScreen2.copy_display(std::cout);

  // 显示 :
  // *****************************#
  // ******************************
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    switch (argv[1][0]) {
      case '1':
        windowMgrTest();
        break;
      case '2':
        screenTest();
        break;
      case '3':
        testReturnLeftValue();
        break;
      default:
        std::cout << "Wrong Options!\n";
        return 1;
    }
  } else {
    std::cout << "screen_mgr\n";
  }
  return 0;
}