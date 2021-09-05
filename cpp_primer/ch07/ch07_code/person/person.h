#ifndef CH07_CH07_CODE_PERSON
#define CH07_CH07_CODE_PERSON
#include <string>
#include <iostream>

class Person{

friend std::ostream &print(std::ostream &, const Person &);
friend std::istream &read(std::istream &, Person &);

public:
    Person() = default;
    Person(const std::string &_name = "", const std::string &_address = "") 
        : name(_name), address(_address) {}
    explicit Person(std::istream &is){ read(is, *this); }
    const std::string &getName() const { return name; }
    const std::string &getAddress() const { return address; }

private:
    std::string name;
    std::string address;
};

std::ostream &print(std::ostream &, const Person &);
std::istream &read(std::istream &, Person &);
#endif