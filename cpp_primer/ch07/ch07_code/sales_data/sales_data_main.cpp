#include "sales_data.h"

void TestConstruct() {
  SalesData s1;
  SalesData s2("test", 2, 30);
  SalesData s3((std::cin));
  Print(std::cout, s1);
  std::cout << "\n";
  Print(std::cout, s2);
  std::cout << "\n";
  Print(std::cout, s3);
  std::cout << "\n";
}

void TestCombine() {
  SalesData total;
  if (Read(std::cin, total)) {
    SalesData trans;
    while (Read(std::cin, trans)) {
      if (total.book_no() == trans.book_no())
        total.Combine(trans);
      else {
        Print(std::cout, total);
        std::cout << "\n";
        total = trans;
      }
    }
    Print(std::cout, total);
  } else {
    std::cerr << "No data!\n";
  }
}

void TestCombineRefactor() {
  SalesData total((std::cin));
  if (std::cin) {
    SalesData trans((std::cin));
    while (std::cin) {
      if (total.book_no() == trans.book_no())
        total.Combine(trans);
      else {
        Print(std::cout, total);
        std::cout << "\n";
        total = trans;
      }
      trans = SalesData((std::cin));
    }
    Print(std::cout, total);
  } else {
    std::cerr << "No data!\n";
  }
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    switch (argv[1][0]) {
      case '1':TestConstruct();
        break;
      case '2':TestCombine();
        break;
      case '3':TestCombineRefactor();
        break;
      default:std::cout << "Wrong Options!\n";
        return 1;
    }
  } else {
    std::cout << "sales_data\n";
  }
  return 0;
}