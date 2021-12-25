#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
struct SalesData {
  SalesData() = default;
  explicit SalesData(std::string book_no) : book_no_(std::move(book_no)) {};

  std::string book_no_;
  unsigned int units_sold_ = 0;
  double revenue_ = 0.0;
};

# endif