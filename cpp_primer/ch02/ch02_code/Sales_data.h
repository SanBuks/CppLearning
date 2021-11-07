# ifndef SALES_DATA_H
# define SALES_DATA_H
#include <string>
struct Sales_data {
  Sales_data() = default;
  explicit Sales_data(std::string bookNo) : bookNo_(std::move(bookNo)) {};
  std::string bookNo_;
  unsigned units_sold_ = 0;
  double revenue_ = 0.0;
};
# endif