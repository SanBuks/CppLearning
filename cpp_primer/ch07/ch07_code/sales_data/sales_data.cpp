#include "sales_data.h"

SalesData::SalesData(std::istream &in_stream) {
  Read(in_stream, *this);
}

/**
 * data 输入格式 : book_no units_sold price
 */
std::istream &Read(std::istream &in_stream, SalesData &rhs){
  double price;
  in_stream >> rhs.book_no_ >> rhs.units_sold_>> price;
  rhs.revenue_ = rhs.units_sold_ * price;
  return in_stream;
}

SalesData &SalesData::Combine(const SalesData &rhs) {
  units_sold_ += rhs.units_sold_;
  revenue_ += rhs.revenue_;
  return *this;
}

SalesData Add(const SalesData &lhs, const SalesData &rhs) {
  SalesData result;
  result.Combine(lhs);
  result.Combine(rhs);
  return result;
}

std::ostream &Print(std::ostream &out_stream, const SalesData &lhs) {
  out_stream << "isbn : " << lhs.book_no()
             << " overall is " << lhs.revenue() << "$ "
             << " average price is " << lhs.AveragePrice() << "$ ";
  return out_stream;
}
