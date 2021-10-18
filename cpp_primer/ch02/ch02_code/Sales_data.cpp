#include <iostream>
#include "Sales_data.h"
using std::string;
using std::cin;
using std::cout;
int main() {
  Sales_data d1, d2, d3;
  cin >> d1.bookNo >> d1.units_sold >> d1.revenue;
  cin >> d2.bookNo >> d2.units_sold >> d2.revenue;
  if (d1.bookNo == d2.bookNo) {
    d3.bookNo = d1.bookNo;
    d3.units_sold = d1.units_sold + d2.units_sold;
    d3.revenue = d1.revenue + d2.revenue;
    cout << d3.bookNo << " " << d3.units_sold << " " << d3.revenue << "\n";
  } else {
    cout << "bookNo must be same !\n";
  }
  return 0;
}