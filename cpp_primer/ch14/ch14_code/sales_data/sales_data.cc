#include "sales_data.h"

SalesData::SalesData(std::string book_no, unsigned units_sold, double revenue)
    : book_no_(std::move(book_no)), units_sold_(units_sold),
      revenue_(revenue) {}
SalesData::SalesData(std::string book_no)
    : SalesData(std::move(book_no), 0, 0.0F) {}
SalesData::SalesData(std::istream &is) : SalesData("", 0, 0.0F) { is >> *this; }

SalesData &SalesData::operator+=(const SalesData &rhs) {
  units_sold_ += rhs.units_sold_;
  revenue_ += rhs.revenue_;
  return *this;
}

std::istream &operator>>(std::istream &is, SalesData &rhs) {
  // 保证强异常安全
  decltype(rhs.revenue_) price;
  decltype(rhs.book_no_) book_no_temp;
  decltype(rhs.units_sold_) units_sold_temp;

  is >> book_no_temp >> units_sold_temp >> price;

  if (is) {
    rhs.book_no_ = book_no_temp;
    rhs.units_sold_ = units_sold_temp;
    rhs.revenue_ = rhs.units_sold_ * price;
  }
  return is;
}
std::ostream &operator<<(std::ostream &os, const SalesData &rhs) {
  os << "isbn : " << rhs.book_no_
     << " overall is " << rhs.revenue_ << "$ "
     << " average price is " << rhs.AveragePrice() << "$ ";
  return os;
}
SalesData operator+(const SalesData &lhs, const SalesData &rhs) {
  SalesData sum = lhs;  // 拷贝构造
  sum += rhs;           // 委托赋值运算符
  return sum;           // 值返回
}
bool operator==(const SalesData &lhs, const SalesData &rhs) {
  return lhs.book_no_ == rhs.book_no_ &&
         lhs.units_sold_ == rhs.units_sold_ &&
         lhs.revenue_ == rhs.revenue_;
}
bool operator!=(const SalesData &lhs, const SalesData &rhs) {
  return !(lhs == rhs);
}