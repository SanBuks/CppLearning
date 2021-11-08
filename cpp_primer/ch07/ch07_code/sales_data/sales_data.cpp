#include "sales_data.h"

SalesData::SalesData() = default;
SalesData::SalesData(std::string book_no, unsigned units_sold, double revenue)
    : book_no_(book_no), units_sold_(units_sold), revenue_(revenue) { }
SalesData::SalesData(std::string book_no) : SalesData(book_no, 0, 0.0F) { }
SalesData::SalesData(std::istream &in_stream) { Read(in_stream, *this); }

SalesData &SalesData::Combine(const SalesData &rhs) {
  units_sold_ += rhs.units_sold_;
  revenue_ += rhs.revenue_;
  return *this;
}

std::istream &Read(std::istream &in_stream, SalesData &rhs) {
  double price;
  in_stream >> rhs.book_no_ >> rhs.units_sold_ >> price;
  rhs.revenue_ = rhs.units_sold_ * price;
  return in_stream;
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
