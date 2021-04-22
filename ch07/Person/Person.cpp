#include "Person.h"

std::ostream &print(std::ostream &os, const Person &rhs){
    os << "Person's name : " << rhs.name 
       << "\t Person's address : " << rhs.address << "\n";
    return os;
}

std::istream &read(std::istream &is, Person &rhs){
    is >> rhs.name >> rhs.address ;
    return is;
}