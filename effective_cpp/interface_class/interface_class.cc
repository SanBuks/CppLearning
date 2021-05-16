#include "interface_class.h"

#include <memory>
#include <string>

class RealPerson: public Person {
 public:
  RealPerson(const std::string &name, 
             const std::string &birth_date,
             const std::string &address);
  virtual ~RealPerson();
  std::string Name() const override;
  std::string BirthDate() const override; 
  std::string Address() const override;

 private:
  std::string the_name_;
  std::string birth_date_;
  std::string the_address_;
};

RealPerson::RealPerson(const std::string &name, 
                       const std::string &birth_date,
                       const std::string &address) 
    : the_name_(name), birth_date_(birth_date), the_address_(address) { }

RealPerson::~RealPerson(){}

std::string RealPerson::Name() const {
  return the_name_;
}

std::string RealPerson::BirthDate() const {
  return birth_date_;
} 

std::string RealPerson::Address() const {
  return the_address_;
}

std::shared_ptr<Person> Person::create(const std::string &name, 
                                       const std::string &birth_date, 
                                       const std::string &address) {
  return std::shared_ptr<Person>(new RealPerson(name, birth_date, address)); 
}

Person::~Person(){ }