#include "date.h"
#include <map>
#include <string>
#include <iostream>
#include <exception>
#include <sstream>

Date::Date(const std::string &date_str) {
    Parse(date_str);
    if (!IsValid()) {
      throw std::runtime_error("Date::Date(std::string) :: date is not valid");
    }
}

bool Date::IsValid() {
  if (month_ == 0 || month_ > 12) {
    return false;
  }
  if (day_ == 0 || day_ > MaxDayOfMonth[month_][IsLeapYear(year_)]) {
    return false;
  }
  return true;
}

void Date::Parse(const std::string &date_str) {
  std::string month_str;
  std::string day_str;
  std::string year_str;

  // parse '1/1/1990' 
  if (date_str.find("/") != std::string::npos) {  
    auto first_pos_of_slash = date_str.find("/");
    auto second_pos_of_slash = date_str.find("/", first_pos_of_slash + 1);
    if (std::string::npos != first_pos_of_slash && 
        std::string::npos != second_pos_of_slash) {
      month_str = date_str.substr(0, first_pos_of_slash - 0);
      day_str   = date_str.substr(first_pos_of_slash + 1, 
                                  second_pos_of_slash - first_pos_of_slash - 1);
      year_str  = date_str.substr(second_pos_of_slash + 1, 
                                  date_str.size() - second_pos_of_slash - 1);
      try {
        month_ = std::stoi(month_str);
        day_ = std::stoi(day_str);
        year_ = std::stoi(year_str);
      } catch (const std::exception &ex) {
        throw std::runtime_error("DATE::Parse(std::string)"
                                 ":: Can't pasrse '1/1/1990' type!");
      }
    } else {
      throw std::runtime_error("DATE::Parse(std::string)"
                               ":: Can't pasrse '1/1/1990' type!");
    }
  // parse 'Jan 1 1900', 'January 1, 1900'
  } else {  
    std::stringstream ss(date_str); 
    ss >> month_str;
    auto month_iterator = MonthValue.find(month_str);
    if ( month_iterator != MonthValue.end()) {
      month_ = month_iterator->second;
      ss >> day_str;
      ss >> year_str;
      try {
        day_ = std::stoi(day_str);
        year_ = std::stoi(year_str);
      } catch (std::exception &ex) {
        throw std::runtime_error("DATE::Parse(std::string)"
                                 "Can't parse 'Jan 1 1900' type!");
      }
    } else {
      throw std::runtime_error("DATE::Parse(std::string)"
                               "Can't parse 'Jan 1 1900' type!");
    }
  }
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
  os << date.year() << "-" << date.month() << "-" << date.day();
  return os;
}

int main(){ 
  // 'January 1, 1900', '1/1/1990', 'Jan 1 1900'
  try {
    Date my_date1("January 1, 1900");
    Date my_date2("1/1/1990");
    Date my_date3("Feb 28 2009");
    std::cout << my_date1 << "\n";
    std::cout << my_date2 << "\n";
    std::cout << my_date3 << "\n";
  } catch (std::exception &ex) {
    std::cout << ex.what();
  }
  return EXIT_SUCCESS;
}