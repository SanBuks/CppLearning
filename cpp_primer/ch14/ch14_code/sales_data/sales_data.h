#ifndef CPP_PRIMER_CH14_CODE_SALES_DATA_
#define CPP_PRIMER_CH14_CODE_SALES_DATA_

#include <string>
#include <iostream>

class SalesData {
  friend std::istream &operator>>(std::istream &is, SalesData &rhs);
  friend std::ostream &operator<<(std::ostream &os, const SalesData &rhs);
  friend bool operator==(const SalesData &lhs, const SalesData &rhs);

 public:
  SalesData() = default;
  SalesData(const SalesData &rhs) = default;
  SalesData &operator=(const SalesData &rhs) = default;
  SalesData(SalesData &&rhs) = default;
  SalesData &operator=(SalesData &&rhs) = default;
  ~SalesData() = default;

  SalesData(std::string book_no, unsigned units_sold, double revenue);
  SalesData(std::string book_no);
  SalesData(std::istream &is);  // 输入格式: book_no units_sold price

  std::string book_no() const { return book_no_; }
  double revenue() const { return revenue_; }
  double AveragePrice() const { return (units_sold_ == 0) ? 0 : revenue_ / units_sold_; }

  SalesData &operator+=(const SalesData &rhs);

  explicit operator std::string() { return book_no_; }
  // 返回值是什么存在歧义, 应该不定义该类型转换
  // explicit operator double() { return units_sold_; }

 private:
  std::string book_no_;      // 书目编号
  unsigned units_sold_ = 0;  // 销售数目
  double revenue_ = 0.0F;    // 销售总额
};

std::istream &operator>>(std::istream &is, SalesData &rhs);
std::ostream &operator<<(std::ostream &os, const SalesData &rhs);
SalesData operator+(const SalesData & lhs, const SalesData &rhs);
bool operator==(const SalesData &lhs, const SalesData &rhs);
bool operator!=(const SalesData &lhs, const SalesData &rhs);
#endif