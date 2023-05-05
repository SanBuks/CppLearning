#include <iostream>
#include <string>
#include <memory>

class Person {
 public:
  static std::shared_ptr<Person> create(const std::string &name, 
                                        const std::string &birth_date, 
                                        const std::string &address);
  virtual ~Person();
  virtual std::string Name() const = 0;
  virtual std::string BirthDate() const = 0;
  virtual std::string Address() const = 0;
};

