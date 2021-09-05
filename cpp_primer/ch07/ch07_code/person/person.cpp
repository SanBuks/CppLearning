#include "person.h"

std::ostream &print(std::ostream &os, const Person &rhs){
    os << "person's name : " << rhs.name
       << "\t person's address : " << rhs.address << "\n";
    return os;
}

std::istream &read(std::istream &is, Person &rhs){
    is >> rhs.name >> rhs.address ;
    return is;
}