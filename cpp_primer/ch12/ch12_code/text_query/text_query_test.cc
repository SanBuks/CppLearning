#include <iostream>
#include <string>

#include "text_query.h"
#include "text_query_data.h"

void RunQueries(std::ifstream &ifs) {
  TextQuery tq(ifs);
  ifs.close();
  while (true) {
    std::cout << "Enter word to look for, or q to quit : \n";
    std::string s;
    if (!(std::cin >> s) || s == "q") break;
    Print(std::cout, tq.Query(s));
  }
}

std::ifstream &LoadFiles() {
  static std::ifstream ifs;
  while (true) {
    std::cout << "Data file dir is : " << data_path::kTextQueryDataPath << "\n";
    std::cout << "Enter filename to load, or q to quit : \n";
    std::string s;
    if (std::cin >> s) {
      if (s == "q") {
        exit(1);
      }
      ifs.open(std::string(data_path::kTextQueryDataPath) + s);
      if (ifs) {
        return ifs;
      } else {
        std::cout << "load file failure!\n";
      }
    } else {
      std::cout << "read filename failure!\n";
    }
  }
}

int main() {
  while (true) {
    // exit in LoadFiles()
    auto &ifs = LoadFiles();
    RunQueries(ifs);
  }
}
