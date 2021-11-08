#ifndef CH07_CH07_CODE_SALES_DATA
#define CH07_CH07_CODE_SALES_DATA

#include <string>
#include <iostream>

class SalesData;

std::istream &Read(std::istream &in_stream, SalesData &rhs);
SalesData Add(const SalesData &lhs, const SalesData &rhs);
std::ostream &Print(std::ostream &out_stream, const SalesData &rhs);

class SalesData {
  friend std::istream &Read(std::istream &in_stream, SalesData &rhs);

 public:
  SalesData();
  SalesData(std::string book_no, unsigned units_sold, double revenue);
  SalesData(std::string book_no);
  // 输入格式: book_no units_sold price
  SalesData(std::istream &in_stream);

  SalesData &Combine(const SalesData &rhs);

  double AveragePrice() const {
    return (units_sold_ == 0) ? 0 : revenue_ / units_sold_;
  }
  std::string book_no() const { return book_no_; }
  double revenue() const { return revenue_; }

 private:
  std::string book_no_;      // 书目编号
  unsigned units_sold_ = 0;  // 销售数目
  double revenue_ = 0.0F;    // 销售总额
};

#endif

