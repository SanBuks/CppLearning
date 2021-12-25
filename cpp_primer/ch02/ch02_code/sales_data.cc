#include <iostream>
#include "sales_data.h"

using std::string;
using std::cin;
using std::cout;

int main() {
  SalesData d1, d2, d3;
  cin >> d1.book_no_ >> d1.units_sold_ >> d1.revenue_;
  cin >> d2.book_no_ >> d2.units_sold_ >> d2.revenue_;
  if (d1.book_no_ == d2.book_no_) {
    d3.book_no_ = d1.book_no_;
    d3.units_sold_ = d1.units_sold_ + d2.units_sold_;
    d3.revenue_ = d1.revenue_ + d2.revenue_;
    cout << d3.book_no_ << " " << d3.units_sold_ << " " << d3.revenue_ << "\n";
  } else {
    cout << "book_no must be same !\n";
  }
  return 0;
}