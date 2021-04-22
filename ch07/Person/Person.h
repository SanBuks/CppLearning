#include <string>
#include <iostream>

class Person{

friend std::ostream &print(std::ostream &, const Person &);
friend std::istream &read(std::istream &, Person &);

public:
    Person() = default;
    Person(const std::string &s1 = "", const std::string &s2 = "") 
        : name(""), address("") {}
    const std::string &getName() const { return name; }
    const std::string &getAddress() const { return address; }

private:
    std::string name;
    std::string address;
};

std::ostream &print(std::ostream &, const Person &);
std::istream &read(std::istream &, Person &);