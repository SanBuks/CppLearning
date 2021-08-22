#ifndef CH09_DATE_DATE_H
#define CH09_DATE_DATE_H

#include <map>
#include <string>
#include <iostream>
#include <exception>
#include <sstream>
#include <vector>

class Date {
 public:
  // store  month abbreviation -> month (int) int
  static const std::map<std::string, int> MonthValue;
  // store max day of month
  static const std::vector<std::vector<unsigned int>> MaxDayOfMonth;
  bool static IsLeapYear(unsigned int year) {
    return (!(year % 4) && (year % 100)) || !(year % 400);
  }

  Date(const std::string &date_str);
  std::iostream &operator<<(std::iostream &os);
  unsigned int year() const { return year_; }
  unsigned int month() const { return month_; }
  unsigned int day() const { return day_; }
 private:
  // is able to parse `date_str` such as 
  // 'January 1, 1900', '1/1/1990', 'Jan 1 1900'
  // if not throws an exception
  void Parse(const std::string &date_str);
  // judges whether date is validated
  bool IsValid();
  // date
  unsigned int year_;
  unsigned int month_;
  unsigned int day_;
};

const std::map<std::string, int> Date::MonthValue{
  {"Jan", 1}, {"Feb", 2}, {"Mar", 3},  {"Apr", 4},  {"May", 5},  {"Jun", 6},
  {"Jul", 7}, {"Aug", 8}, {"Sept", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12},

  {"January", 1},   {"February", 2}, {"March", 3},     {"April", 4}, 
  {"May", 5},       {"June", 6},     {"July", 7},      {"August", 8}, 
  {"September", 9}, {"October", 10}, {"November", 11}, {"December", 12}
};

const std::vector<std::vector<unsigned int>> Date::MaxDayOfMonth{
  {0, 0}, 
  {31, 31}, {28, 29}, {31, 31}, {30, 30}, {31, 31}, {30, 30}, 
  {31, 31}, {31, 31}, {30, 30}, {31, 31}, {30, 30}, {31, 31} 
};

#endif