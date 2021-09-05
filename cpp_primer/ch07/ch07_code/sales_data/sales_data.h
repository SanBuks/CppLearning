#ifndef CH07_CH07_CODE_SALES_DATA
#define CH07_CH07_CODE_SALES_DATA
#include <string>
#include <iostream>

class SalesData {
  friend std::istream &Read(std::istream &in_stream, SalesData &rhs);

 public:
  SalesData() = default;
  SalesData(std::string book_no, unsigned units_sold, double revenue)
      : book_no_(book_no), units_sold_(units_sold), revenue_(revenue) {}
  /**
   * 通过 流 读入数据
   * @param in_stream
   */
  SalesData(std::istream &in_stream);
  SalesData(std::string book_no) : SalesData(book_no, 0, 0.0F) {}
  SalesData &Combine(const SalesData &rhs);

  double AveragePrice() const {
    return (units_sold_ == 0) ? 0 : revenue_ / units_sold_;
  }

  std::string book_no() const {
    return book_no_;
  }
  double revenue() const {
    return revenue_;
  }
 private:
  /**
   * 书目编号
   */
  std::string book_no_;
  /**
   * 销售数目
   */
  unsigned units_sold_ = 0;
  /**
   * 销售总额
   */
  double revenue_ = 0.0F;
};
/**
 * 从 data 中 读取数据
 * @param in_stream
 * @param rhs
 * @return
 */
std::istream &Read(std::istream &in_stream, SalesData &rhs);
SalesData Add(const SalesData &lhs, const SalesData &rhs);
std::ostream &Print(std::ostream &out_stream, const SalesData &rhs);
#endif

