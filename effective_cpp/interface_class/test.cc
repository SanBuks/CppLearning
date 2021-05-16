#include <iostream>

#include "interface_class.h"

int main() {
  std::shared_ptr<Person> pp(Person::create("name", "birth_date", "address"));
  std::cout << pp->Name();
  return 0;
}