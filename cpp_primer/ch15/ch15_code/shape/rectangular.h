#ifndef CPP_PRIMER_CH15_CODE_RECTANGULAR_
#define CPP_PRIMER_CH15_CODE_RECTANGULAR_

#include <utility>

#include "shape_2d.h"

class Rectangular final : public Shape2D {
 public:
  typedef std::pair<double, double> Coordinate;
  typedef std::pair<double, double> LenWidth;

  Rectangular() = default;
  Rectangular(const Rectangular &rhs) = default;
  Rectangular(Rectangular &&rhs) = default;
  Rectangular &operator=(const Rectangular &rhs) = default;
  Rectangular &operator=(Rectangular &&rhs) = default;
  ~Rectangular() override = default;

  Rectangular(std::string i, std::string n, LenWidth len_width,
              Coordinate coordinate, double angle)
      : Shape2D(std::move(i), std::move(n)),
        length_(len_width.first), width_(len_width.second),
        llx_(coordinate.first), lly_(coordinate.second), angle_(angle) {}

  double getArea() const override { return length_ * width_; };
  double getPerimeter() const override { return 2 * (length_ + width_); };
  void printInfo() const override;
  Coordinate coordinate() const { return {llx_, lly_}; }

 protected:
  double length_ = 0.0F, width_ = 0.0F;
  double llx_ = 0.0F, lly_ = 0.0F;
  double angle_ = 0.0F;
};

void Rectangular::printInfo() const {
  Shape2D::printInfo();
  std::cout << "length_: " << length_ << " width_: " << width_ << "\n";
  std::cout << "coordinate: " << llx_ << ", " << lly_ << " angle_: " << angle_ << "\n";
}

#endif