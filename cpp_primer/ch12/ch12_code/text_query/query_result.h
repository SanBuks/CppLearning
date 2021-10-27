#ifndef CPP_PRIMER_CH12_CODE_QUERY_RESULT_H_
#define CPP_PRIMER_CH12_CODE_QUERY_RESULT_H_

#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <utility>

#include "str_blob.h"

class QueryResult {
  friend std::ostream &Print(std::ostream &os, const QueryResult &qr);
 public:
  QueryResult(std::string s, std::shared_ptr<std::set<size_t>> p,
              std::shared_ptr<StrBlob> f)
      : word_search_(std::move(s)), lines_(std::move(p)), files_(std::move(f)) {}

  std::shared_ptr<StrBlob> GetFiles() { return files_; }
  std::set<size_t>::iterator Begin() { return lines_->begin(); }
  std::set<size_t>::iterator End() { return lines_->end(); }

 private:
  std::string word_search_;
  std::shared_ptr<std::set<size_t>> lines_;
  std::shared_ptr<StrBlob> files_;
};

std::ostream &Print(std::ostream &os, const QueryResult &qr) {
  os << qr.word_search_ << " occurring times : " << qr.lines_->size() << "\n";
  for (auto it: *qr.lines_)
    os << "\t (line " << it + 1 << ")" << (*qr.files_)[it] << "\n";
  return os;
}

#endif