#ifndef CPP_PRIMER_CH15_CODE_SHAPE_2D_
#define CPP_PRIMER_CH15_CODE_SHAPE_2D_

#include <utility>
#include <string>
#include <iostream>

class Shape2D {
 public:
  Shape2D() : id_("00000"), name_("Default Name") {}
  Shape2D(const Shape2D &rhs) = default;
  Shape2D(Shape2D &&rhs) = default;
  Shape2D &operator=(const Shape2D &rhs) = default;
  Shape2D &operator=(Shape2D &&rhs) = default;
  virtual ~Shape2D() = default;

  Shape2D(std::string i, std::string n)
      : id_(std::move(i)), name_(std::move(n)) {}

  virtual double getArea() const = 0;
  virtual double getPerimeter() const = 0;
  virtual void printInfo() const;

 protected:
  std::string id_;
  std::string name_;
};

void Shape2D::printInfo() const {
  std::cout << "id_: " << id_ << " name_: " << name_ << "\n";
}

#endif