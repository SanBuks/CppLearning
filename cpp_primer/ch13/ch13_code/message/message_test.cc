#include <iostream>
#include <string>
#include "message.h"
#include "folder.h"

void TestMessage() {
  Folder f1("folder");
  Message m1(std::string("message1"));
  Message m2(std::string("message2"));

  m1.AddFolderConnection(&f1);
  m2.AddFolderConnection(&f1);
  f1.Print();
  m1.Print();
  m2.Print();

  std::cout << "\n";

  Message m3(m1);
  m3.set_contents("3234234");
  f1.Print();

  std::cout << "\n";

  m3 = m1;
  f1.Print();

  std::cout << "\n";

  f1.RemoveMessageConnection(&m3);
  f1.Print();

  std::cout << "\n";

  f1.RemoveAllMessageConnections();
  f1.Print();
  m1.Print();
  m2.Print();

  std::cout << "\n";
}

void TestFolder() {
  Folder f1("folder");
  Message m1(std::string("message1"));
  Message m2(std::string("message2"));
  f1.AddMessageConnection(&m1);
  f1.AddMessageConnection(&m2);

  Folder f2(f1);
  f2.set_folder_name("f2");
  f2.Print();
  m1.Print();
  m2.Print();

  std::cout << "\n";

  f1 = f2;
  f1.set_folder_name("f1");
  f1.Print();

  std::cout << "\n";

  f1.RemoveMessageConnection(&m1);
  f1.Print();

  std::cout << "\n";
}

void TestMessageMove() {
  Folder f1("folder");
  Message m1(std::string("message1"));
  Message m2(std::string("message2"));
  f1.AddMessageConnection(&m1);
  f1.AddMessageConnection(&m2);

  Message m3 = std::move(m1);
  m3.Print();
  std::cout << "\n";

  m3 = std::move(m2);
  m3.Print();
  std::cout << "\n";
}

int main() {
//  TestMessage();
//  TestFolder();
  TestMessageMove();

}
